#include "IRenderer3D.hpp"

#include "../../Engine.hpp"
#include "../../Texture/ITexture.hpp"
#include "../../BlendState/IBlendState.hpp"
#include "../../SamplerState/ISamplerState.hpp"
#include "../../RasterizerState/IRasterizerState.hpp"
#include "../../DepthStencilState/IDepthStencilState.hpp"
#include "../../ConstantBuffer/IConstantBuffer.hpp"
#include "../../VertexShader/IVertexShader.hpp"
#include "../../PixelShader/IPixelShader.hpp"
#include "../../RenderTarget/IRenderTarget.hpp"
#include "../../Renderer/Renderer2D/IRenderer2D.hpp"
#include "../../Model/IModel.hpp"
#include "../../Misc.hpp"

#include "../../../Include/System.hpp"
#include "../../../Include/VertexShader.hpp"
#include "../../../Include/PixelShader.hpp"
#include "../../../Include/BlendState.hpp"
#include "../../../Include/SamplerState.hpp"
#include "../../../Include/RasterizerState.hpp"
#include "../../../Include/DepthStencilState.hpp"
#include "../../../Include/ConstantBuffer.hpp"
#include "../../../Include/Texture.hpp"
#include "../../../Include/RenderTarget.hpp"
#include "../../../Include/Model.hpp"
#include "../../../Include/Camera.hpp"

#include "../../../Include/Constants.hpp"

namespace
{
  hdx::VertexShader CurrentVertexShader;
  hdx::PixelShader CurrentPixelShader;
  hdx::BlendState CurrentBlendState = hdx::BlendState::Default;
  hdx::RasterizerState CurrentRasterizerState = hdx::RasterizerState::Default3D;
  hdx::DepthStencilState CurrentDepthStencilState = hdx::DepthStencilState::Default3D;
  hdx::RenderTarget CurrentRenderTarget;

  hdx::SamplerState CurrentSamplerStatus[hdx::SamplerStateMaxNum];
  hdx::Texture CurrentTextures[hdx::TextureMaxNum - 1];

  hdx::ConstantBuffer ConstantBuffer;

  hdx::Camera Camera;
  hdx::Matrix ViewMatrix;
  hdx::Matrix ProjectionMatrix;

  inline void CalcView()
  {
    ViewMatrix = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(Camera.Pos.X, Camera.Pos.Y, Camera.Pos.Z, 1.0f),
      DirectX::XMVectorSet(Camera.Target.X, Camera.Target.Y, Camera.Target.Z, 1.0f),
      DirectX::XMVectorSet(Camera.Up.X, Camera.Up.Y, Camera.Up.Z, 0.0f));
  }
}

IRenderer3D::IRenderer3D()
{
  TIMER_START("Renderer3D");

  CurrentSamplerStatus[0] = hdx::SamplerState::Default3D;

  ConstantBuffer.Data_.LightDirection = { 0.0f, 0.0f, 1.0f, 0.0f };

  TIMER_END("Renderer3D");
}

void IRenderer3D::Initialize()
{
  CurrentVertexShader = Engine::Get<IVertexShader>()->CreateDefault3D();
  CurrentPixelShader = Engine::Get<IPixelShader>()->CreateDefault3D();

  CalcView();
}

void IRenderer3D::Draw(const hdx::Model& _Model, const hdx::Matrix& _WorldMatrix, const hdx::ColorF& _Color)
{
  Engine::Get<IRenderer2D>()->End();

  const ModelData& ModelData = Engine::Get<IModel>()->GetModelData(_Model.GetID());

  IRenderer::SetVertexShader(Engine::Get<IVertexShader>()->GetVertexShader(CurrentVertexShader));
  IRenderer::SetInputLayout(Engine::Get<IVertexShader>()->GetInputLayout(CurrentVertexShader));
  IRenderer::SetPixelShader(Engine::Get<IPixelShader>()->GetPixeShader(CurrentPixelShader));
  IRenderer::SetBlendState(Engine::Get<IBlendState>()->GetBlendState(CurrentBlendState));
  for (int i = 0; i < hdx::SamplerStateMaxNum; ++i)
  {
    IRenderer::SetSamplersState(Engine::Get<ISamplerState>()->GetSamplerState(CurrentSamplerStatus[i]), i);
  }
  IRenderer::SetRasterizerState(Engine::Get<IRasterizerState>()->GetRasterizerState(CurrentRasterizerState));
  IRenderer::SetDepthStencilState(Engine::Get<IDepthStencilState>()->GetDepthStencilState(CurrentDepthStencilState));
  for (int i = 1; i < hdx::TextureMaxNum - 1; ++i)
  {
    const int ID = CurrentTextures[i - 1].GetID();
    if (ID < 0)continue;

    IRenderer::SetShaderResouceView(Engine::Get<ITexture>()->GetShaderResourceView(CurrentTextures[i].GetID()), i);
  }
  IRenderer::SetRenderTarget(Engine::Get<IRenderTarget>()->GetRenderTargetView(CurrentRenderTarget), Engine::Get<IRenderTarget>()->GetDepthStencilView(CurrentRenderTarget));

  ConstantBuffer.Data_.LightDirection = { 0.0f, 0.0f, 1.0f, 0.0f };

  UINT Strides = sizeof(Vertex);
  for (auto& Mesh : ModelData.Meshes)
  {
    IRenderer::SetVertexBuffer(Mesh.pVertexBuffer.GetAddressOf(), Strides);
    IRenderer::SetIndexBuffer(Mesh.pIndexBuffer.Get());

    const hdx::Matrix GlobalTransform = DirectX::XMLoadFloat4x4(&Mesh.GlobalTransform);

    DirectX::XMStoreFloat4x4(&ConstantBuffer.Data_.WorldViewProjection, GlobalTransform * _WorldMatrix*ViewMatrix*ProjectionMatrix);
    DirectX::XMStoreFloat4x4(&ConstantBuffer.Data_.World, GlobalTransform * _WorldMatrix);

    for (auto& Subset : Mesh.Subsets)
    {
      ConstantBuffer.Data_.MaterialColor = {
        Subset.Diffuse.Color.R*_Color.R,
        Subset.Diffuse.Color.G*_Color.G,
        Subset.Diffuse.Color.B*_Color.B,
        Subset.Diffuse.Color.A*_Color.A };
      auto pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size);
      IRenderer::UpdateSubresource(pConstantBuffer, &ConstantBuffer.Data_);
      IRenderer::SetConstatBuffer(&pConstantBuffer, 0);

      IRenderer::SetShaderResouceView(Engine::Get<ITexture>()->GetShaderResourceView(Subset.Diffuse.TextureID), 0);

      IRenderer::DrawIndexed(Subset.IndexCount, Subset.IndexStart, 0);
    }
  }
}

void IRenderer3D::CalcProjection()
{
  if (Camera.isPerspective)
  {
    const float Aspect = static_cast<float>(hdx::System::GetWindowWidth()) / hdx::System::GetWindowHeight();

    ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(hdx::Radian(Camera.Fov).GetValue(), Aspect, Camera.Near, Camera.Far);
  }
  else
  {
    constexpr float Width = 16.0f / 2.0f;
    constexpr float Height = 9.0f / 2.0f;

    ProjectionMatrix = DirectX::XMMatrixOrthographicLH(Width, Height, Camera.Near, Camera.Far);
  }
}

void IRenderer3D::SetVertexShader(const hdx::VertexShader& _VertexShader)
{
  if (CurrentVertexShader == _VertexShader)return;

  CurrentVertexShader = _VertexShader;
}

void IRenderer3D::SetPixelShader(const hdx::PixelShader& _PixelShader)
{
  if (CurrentPixelShader == _PixelShader)return;

  CurrentPixelShader = _PixelShader;
}

void IRenderer3D::SetBlendState(const hdx::BlendState& _BlendState)
{
  if (CurrentBlendState == _BlendState)return;

  CurrentBlendState = _BlendState;
}

void IRenderer3D::SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot)
{
  hdx::SamplerState& CurrentSamplerState = CurrentSamplerStatus[_Slot];
  if (CurrentSamplerState == _SamplerState)return;

  CurrentSamplerState = _SamplerState;
}

void IRenderer3D::SetRasterizerState(const hdx::RasterizerState& _RasterizerState)
{
  if (CurrentRasterizerState == _RasterizerState)return;

  CurrentRasterizerState = _RasterizerState;
}

void IRenderer3D::SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
{
  if (CurrentDepthStencilState == _DepthStencilState)return;

  CurrentDepthStencilState = _DepthStencilState;
}

void IRenderer3D::SetTexture(const hdx::Texture& _Texture, UINT _Slot)
{
  hdx::Texture& CurrentTexture = CurrentTextures[_Slot];
  if (CurrentTexture == _Texture)return;

  CurrentTexture = _Texture;
}

inline void CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  Engine::Get<ITexture>()->SetShaderResouceView(_RenderTarget, Engine::Get<IRenderTarget>()->GetShaderResourceView(_RenderTarget));
}

void IRenderer3D::RestoreRenderTarget()
{
  if (CurrentRenderTarget.GetSize() == hdx::int2())return;

  CreateTextureFromRenderTarget(CurrentRenderTarget);
  CurrentRenderTarget = hdx::RenderTarget();
}

void IRenderer3D::SetRenderTarget(const hdx::RenderTarget& _RenderTarger)
{
  if (CurrentRenderTarget == _RenderTarger)return;

  if (CurrentRenderTarget.GetSize() != hdx::int2())
  {
    CreateTextureFromRenderTarget(CurrentRenderTarget);
  }
  CurrentRenderTarget = _RenderTarger;
}

void IRenderer3D::SetCamera(const hdx::Camera& _Camera)
{
  Camera = _Camera;

  CalcProjection();
  CalcView();
}

void IRenderer3D::SetLightDirection(const hdx::float3& _LightDirection)
{
  ConstantBuffer.Data_.LightDirection.x = _LightDirection.X;
  ConstantBuffer.Data_.LightDirection.y = _LightDirection.Y;
  ConstantBuffer.Data_.LightDirection.z = _LightDirection.Z;
}

void IRenderer3D::FreeCamera()
{

}
