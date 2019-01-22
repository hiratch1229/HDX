#include "Src/Renderer/Renderer3D/IRenderer3D.hpp"

#include "Src/Engine.hpp"
#include "Src/Texture/ITexture.hpp"
#include "Src/BlendState/IBlendState.hpp"
#include "Src/SamplerState/ISamplerState.hpp"
#include "Src/RasterizerState/IRasterizerState.hpp"
#include "Src/DepthStencilState/IDepthStencilState.hpp"
#include "Src/ConstantBuffer/IConstantBuffer.hpp"
#include "Src/VertexShader/IVertexShader.hpp"
#include "Src/PixelShader/IPixelShader.hpp"
#include "Src/RenderTarget/IRenderTarget.hpp"
#include "Src/Renderer/Renderer2D/IRenderer2D.hpp"
#include "Src/Model/IModel.hpp"
#include "Src/Misc.hpp"

#include "Include/System.hpp"
#include "Include/VertexShader.hpp"
#include "Include/PixelShader.hpp"
#include "Include/BlendState.hpp"
#include "Include/SamplerState.hpp"
#include "Include/RasterizerState.hpp"
#include "Include/DepthStencilState.hpp"
#include "Include/ConstantBuffer.hpp"
#include "Include/Texture.hpp"
#include "Include/RenderTarget.hpp"
#include "Include/Model.hpp"
#include "Include/Camera.hpp"

#include "Include/Color.hpp"
#include "Include/Constants.hpp"

namespace
{
  struct CommonConstantBuffer
  {
    DirectX::XMFLOAT4X4 ViewProjectionMatrix;
    DirectX::XMFLOAT4X4 GlobalTransform;
    DirectX::XMFLOAT4 LightDirection;     //  ライト進行方向
    hdx::ColorF DiffuseColor;

    DirectX::XMFLOAT4X4 BoneTransforms[hdx::Constants::MaxBoneNum];
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

  struct Instance
  {
    DirectX::XMFLOAT4X4 World;                //  ワールド変換行列
    hdx::ColorF MaterialColor;                //  材質色
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

  Microsoft::WRL::ComPtr<ID3D11Buffer> pInstanceBuffer;

  Instance* Instances = nullptr;
  int Count = 0;
  hdx::Model CurrentModel;
  hdx::MotionData CurrentMotionData;

  DirectX::XMFLOAT4X4 BoneNothingMatrix;

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

  DirectX::XMStoreFloat4x4(&BoneNothingMatrix, DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f));

  TIMER_END("Renderer3D");
}

void IRenderer3D::Initialize(ID3D11Device* _pDevice)
{
  CurrentVertexShader = Engine::Get<IVertexShader>()->CreateDefault3D();
  CurrentPixelShader = Engine::Get<IPixelShader>()->CreateDefault3D();

  //  エラーチェック用
  HRESULT hr = S_OK;

  //  インスタンスバッファを作成
  {
    Instances = new Instance[hdx::Constants::ModelBatchMaxNum];

    D3D11_BUFFER_DESC BufferDesc{};
    {
      BufferDesc.ByteWidth = sizeof(Instance) * hdx::Constants::SpriteBatchMaxNum;
      BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
      BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      BufferDesc.MiscFlags = 0;
      BufferDesc.StructureByteStride = 0;
    }

    D3D11_SUBRESOURCE_DATA InitialData{};
    {
      InitialData.pSysMem = Instances;
      InitialData.SysMemPitch = 0;
      InitialData.SysMemSlicePitch = 0;
    }

    hr = _pDevice->CreateBuffer(&BufferDesc, &InitialData, pInstanceBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    delete[] Instances;
    Instances = nullptr;
  }

  CalcView();
}

void IRenderer3D::Draw(const hdx::Model& _Model, const hdx::Matrix& _WorldMatrix, const hdx::MotionData& _MotionData, const hdx::ColorF& _Color)
{
  if (!Instances || CurrentModel != _Model)
  {
    CurrentMotionData = _MotionData;

    Engine::Get<IRenderer2D>()->End();
    End();
    Begin(_Model);
  }

  Instance& Instance = Instances[Count];
  DirectX::XMStoreFloat4x4(&Instance.World, _WorldMatrix);
  Instance.MaterialColor = _Color;

  if (++Count >= hdx::Constants::ModelBatchMaxNum || _MotionData.Number != 0 || _MotionData.Frame != 0.0f)
  {
    End();
    Begin(_Model);
  }
}

void IRenderer3D::Begin(const hdx::Model& _Model)
{
  CurrentModel = _Model;

  //  GPUにセット
  {
    DirectX::XMStoreFloat4x4(&ConstantBuffer.Get().ViewProjectionMatrix, ViewMatrix*ProjectionMatrix);

    IRenderer::SetVertexBuffer(pInstanceBuffer.GetAddressOf(), sizeof(Instance), 1);

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
      ConstantBufferData& ConstantBuffer = VertexStageConstantBuffers[i - 1];

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
  }

  //  頂点バッファオブジェクトを書き換え
  D3D11_MAPPED_SUBRESOURCE MappedSubresorce;
  IRenderer::Map(pInstanceBuffer.Get(), &MappedSubresorce);
  Instances = static_cast<Instance*>(MappedSubresorce.pData);
}

void IRenderer3D::End()
{
  if (!Instances)return;

  IRenderer::Unmap(pInstanceBuffer.Get());

  const ModelData& ModelData = Engine::Get<IModel>()->GetModelData(CurrentModel.GetID());
  ID3D11Buffer* pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size);

  UINT Strides = sizeof(Vertex);
  for (auto& Mesh : ModelData.Meshes)
  {
    IRenderer::SetVertexBuffer(Mesh.pVertexBuffer.GetAddressOf(), Strides, 0);
    IRenderer::SetIndexBuffer(Mesh.pIndexBuffer.Get());

    ConstantBuffer.Get().GlobalTransform = Mesh.GlobalTransform;

    //  ボーンアニメーション
    {
      const int SkeletalAnimationNum = (Mesh.SkeletalAnimations.size() > 0) ? Mesh.SkeletalAnimations[CurrentMotionData.Number].size() : 0;

      if (SkeletalAnimationNum > 0)
      {
        const Skeletal& Skeletal = Mesh.SkeletalAnimations[CurrentMotionData.Number].at(static_cast<size_t>(CurrentMotionData.Frame / Mesh.SamplingTime));

        const int NumberOfBones = Skeletal.size();
        _ASSERT_EXPR(NumberOfBones < hdx::Constants::MaxBoneNum, L"'the NumberOfBones' exceeds hdx::Constants::MaxBoneNum");

        for (int i = 0; i < NumberOfBones; ++i)
        {
          DirectX::XMStoreFloat4x4(&ConstantBuffer.Get().BoneTransforms[i], DirectX::XMLoadFloat4x4(&Skeletal.at(i).Transform));
        }
      }
      else
      {
        for (int i = 0; i < hdx::Constants::MaxBoneNum; ++i)
        {
          ConstantBuffer.Get().BoneTransforms[i] = BoneNothingMatrix;
        }
      }
    }

    for (auto& Subset : Mesh.Subsets)
    {
      ConstantBuffer.Get().DiffuseColor = Subset.Diffuse.Color;

      IRenderer::UpdateSubresource(pConstantBuffer, &ConstantBuffer.Get());
      IRenderer::SetConstatBufferVS(&pConstantBuffer, 0);
      IRenderer::SetConstatBufferPS(&pConstantBuffer, 0);

      IRenderer::SetShaderResouceView(Engine::Get<ITexture>()->GetShaderResourceView(Subset.Diffuse.TextureID), 0);

      IRenderer::DrawIndexedInstanced(Subset.IndexCount - Subset.IndexStart, Count, Subset.IndexStart, 0, 0);
    }
  }

  CurrentModel = hdx::Model();
  CurrentMotionData = hdx::MotionData();
  Count = 0;

  Instances = nullptr;
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
  CurrentTextures[0] = _RenderTarget;
}

void IRenderer3D::RestoreRenderTarget()
{
  if (CurrentRenderTarget.GetSize() == hdx::int2())return;

  End();

  ID3D11ShaderResourceView* NullObject = nullptr;
  IRenderer::SetShaderResouceView(&NullObject, 0);

  CreateTextureFromRenderTarget(CurrentRenderTarget);
  CurrentRenderTarget = hdx::RenderTarget();
  IRenderer::SetViewPort(hdx::System::GetWindowSize());
}

void IRenderer3D::SetRenderTarget(const hdx::RenderTarget& _RenderTarger)
{
  if (CurrentRenderTarget == _RenderTarger)return;

  End();
  ID3D11ShaderResourceView* NullObject = nullptr;
  IRenderer::SetShaderResouceView(&NullObject, 0);

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

const hdx::Matrix& IRenderer3D::GetProjectionMatrix()const
{
  return ProjectionMatrix;
}

const hdx::Matrix& IRenderer3D::GetViewMatrix()const
{
  return ViewMatrix;
}
