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

#include "../../../Include/Color.hpp"
#include "../../../Include/Constants.hpp"

namespace
{
  struct CommonConstantBuffer
  {
    DirectX::XMFLOAT4X4 WorldViewProjection;  //  ワールド・ビュー・プロジェクション合成行列
    DirectX::XMFLOAT4X4 World;                //  ワールド変換行列
    hdx::ColorF MaterialColor;                     //  材質色
    DirectX::XMFLOAT4 LightDirection;         //  ライト進行方向
    DirectX::XMFLOAT4X4 BoneTransforms[hdx::Constants::MaxBoneInfluences];
  };

  struct ConstantBufferData
  {
    UINT Size = 0;
    void* pData;
  public:
    ConstantBufferData() = default;
    ConstantBufferData(UINT _Size, void* _pData)
      : Size(_Size), pData(_pData)
    {

    }
  };

  hdx::VertexShader CurrentVertexShader;
  hdx::PixelShader CurrentPixelShader;
  hdx::BlendState CurrentBlendState = hdx::BlendState::Default;
  hdx::RasterizerState CurrentRasterizerState = hdx::RasterizerState::Default3D;
  hdx::DepthStencilState CurrentDepthStencilState = hdx::DepthStencilState::Default3D;
  hdx::RenderTarget CurrentRenderTarget;

  hdx::SamplerState CurrentSamplerStatus[hdx::Constants::SamplerStateMaxNum];
  hdx::Texture CurrentTextures[hdx::Constants::TextureMaxNum - 1];

  hdx::Camera Camera;
  hdx::Matrix ViewMatrix;
  hdx::Matrix ProjectionMatrix;

  hdx::ConstantBuffer<CommonConstantBuffer> ConstantBuffer;
  ConstantBufferData VertexStageConstantBuffers[hdx::Constants::ConstantBufferMaxNum - 1];
  ConstantBufferData PixelStageConstantBuffers[hdx::Constants::ConstantBufferMaxNum - 1];

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
  ConstantBuffer.Get().LightDirection = { 0.0f, 0.0f, 1.0f, 0.0f };

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
  for (int i = 0; i < hdx::Constants::SamplerStateMaxNum; ++i)
  {
    IRenderer::SetSamplersState(Engine::Get<ISamplerState>()->GetSamplerState(CurrentSamplerStatus[i]), i);
  }
  IRenderer::SetRasterizerState(Engine::Get<IRasterizerState>()->GetRasterizerState(CurrentRasterizerState));
  IRenderer::SetDepthStencilState(Engine::Get<IDepthStencilState>()->GetDepthStencilState(CurrentDepthStencilState));
  for (int i = 1; i < hdx::Constants::TextureMaxNum; ++i)
  {
    IRenderer::SetShaderResouceView(Engine::Get<ITexture>()->GetShaderResourceView(CurrentTextures[i - 1].GetID()), i);
  }
  IRenderer::SetRenderTarget(Engine::Get<IRenderTarget>()->GetRenderTargetView(CurrentRenderTarget), Engine::Get<IRenderTarget>()->GetDepthStencilView(CurrentRenderTarget));
  IRenderer::SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  for (int i = 1; i < hdx::Constants::ConstantBufferMaxNum; ++i)
  {
    ConstantBufferData& ConstantBuffer = PixelStageConstantBuffers[i - 1];

    if (ConstantBuffer.Size == 0)continue;

    ID3D11Buffer* pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size);
    IRenderer::UpdateSubresource(pConstantBuffer, ConstantBuffer.pData);
    IRenderer::SetConstatBufferVS(&pConstantBuffer, i);
  }
  for (int i = 1; i < hdx::Constants::ConstantBufferMaxNum; ++i)
  {
    ConstantBufferData& ConstantBuffer = PixelStageConstantBuffers[i - 1];

    if (ConstantBuffer.Size == 0)continue;

    ID3D11Buffer* pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size);
    IRenderer::UpdateSubresource(pConstantBuffer, ConstantBuffer.pData);
    IRenderer::SetConstatBufferPS(&pConstantBuffer, i);
  }

  UINT Strides = sizeof(Vertex);
  for (auto& Mesh : ModelData.Meshes)
  {
    IRenderer::SetVertexBuffer(Mesh.pVertexBuffer.GetAddressOf(), Strides);
    IRenderer::SetIndexBuffer(Mesh.pIndexBuffer.Get());

    const hdx::Matrix GlobalTransform = DirectX::XMLoadFloat4x4(&Mesh.GlobalTransform);

    DirectX::XMStoreFloat4x4(&ConstantBuffer.Get().WorldViewProjection, GlobalTransform * _WorldMatrix*ViewMatrix*ProjectionMatrix);
    DirectX::XMStoreFloat4x4(&ConstantBuffer.Get().World, GlobalTransform * _WorldMatrix);

    for (auto& Subset : Mesh.Subsets)
    {
      ConstantBuffer.Get().MaterialColor = {
        Subset.Diffuse.Color.R*_Color.R,
        Subset.Diffuse.Color.G*_Color.G,
        Subset.Diffuse.Color.B*_Color.B,
        Subset.Diffuse.Color.A*_Color.A };

      ID3D11Buffer* pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size);
      IRenderer::UpdateSubresource(pConstantBuffer, &ConstantBuffer.Get());
      IRenderer::SetConstatBufferVS(&pConstantBuffer, 0);
      IRenderer::SetConstatBufferPS(&pConstantBuffer, 0);

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
  IRenderer::SetViewPort(hdx::System::GetWindowSize());
}

void IRenderer3D::SetRenderTarget(const hdx::RenderTarget& _RenderTarger)
{
  if (CurrentRenderTarget == _RenderTarger)return;

  if (CurrentRenderTarget.GetSize() != hdx::int2())
  {
    CreateTextureFromRenderTarget(CurrentRenderTarget);
    IRenderer::SetViewPort(CurrentRenderTarget.GetSize());
  }
  CurrentRenderTarget = _RenderTarger;
}

void IRenderer3D::SetCamera(const hdx::Camera& _Camera)
{
  Camera = _Camera;

  CalcProjection();
  CalcView();
}

void IRenderer3D::SetConstantBuffer(hdx::ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot)
{
  switch (_Stage)
  {
  case hdx::ShaderStage::Vertex:
    VertexStageConstantBuffers[_Slot - 1] = ConstantBufferData(_Size, const_cast<void*>(_pData));
    break;
  case hdx::ShaderStage::Pixel:
    PixelStageConstantBuffers[_Slot - 1] = { _Size , const_cast<void*>(_pData) };
    break;
  default: assert(false);
  }
}

void IRenderer3D::SetLightDirection(const hdx::float3& _LightDirection)
{
  ConstantBuffer.Get().LightDirection.x = _LightDirection.X;
  ConstantBuffer.Get().LightDirection.y = _LightDirection.Y;
  ConstantBuffer.Get().LightDirection.z = _LightDirection.Z;
}

void IRenderer3D::FreeCamera()
{

}
