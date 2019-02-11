#include "CRenderer3D.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Model/IModel.hpp"
#include "Src/Renderer/Renderer2D/IRenderer2D.hpp"
#include "Src/BlendState/IBlendState.hpp"
#include "Src/ConstantBuffer/IConstantBuffer.hpp"
#include "Src/RasterizerState/IRasterizerState.hpp"
#include "Src/DepthStencilState/IDepthStencilState.hpp"
#include "Src/RenderTarget/IRenderTarget.hpp"
#include "Src/SamplerState/ISamplerState.hpp"
#include "Src/Texture/ITexture.hpp"
#include "Src/VertexShader/IVertexShader.hpp"
#include "Src/PixelShader/IPixelShader.hpp"
#include "Src/Misc.hpp"

void CRenderer3D::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
{
  pImmediateContext_ = _pImmediateContext;
  ppRenderTargetView_ = _ppRenderTargetView;
  pDepthStencilView_ = _pDepthStencilView;

  ConstantBuffer_.Get().LightDirection = { 0.0f, 0.0f, 1.0f, 0.0f };

  DirectX::XMStoreFloat4x4(&BoneNothingMatrix_, DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f));

  VertexShader_ = Engine::Get<IVertexShader>()->CreateDefault3D(pInputLayout_.GetAddressOf());
  PixelShader_ = Engine::Get<IPixelShader>()->CreateDefault3D();

  //  エラーチェック用
  HRESULT hr = S_OK;

  //  インスタンスバッファを作成
  {
    Instances_ = new Instance[kModelBatchMaxNum];

    D3D11_BUFFER_DESC BufferDesc{};
    {
      BufferDesc.ByteWidth = sizeof(Instance) * kModelBatchMaxNum;
      BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
      BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      BufferDesc.MiscFlags = 0;
      BufferDesc.StructureByteStride = 0;
    }

    D3D11_SUBRESOURCE_DATA InitialData{};
    {
      InitialData.pSysMem = Instances_;
      InitialData.SysMemPitch = 0;
      InitialData.SysMemSlicePitch = 0;
    }

    hr = _pDevice->CreateBuffer(&BufferDesc, &InitialData, pInstanceBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    delete[] Instances_;
    Instances_ = nullptr;
  }

  CalcView();
}

void CRenderer3D::Draw(const hdx::Model& _Model, const hdx::Matrix& _WorldMatrix, const hdx::MotionData& _MotionData, const hdx::ColorF& _Color)
{
  if (!Instances_ || Model_ != _Model)
  {
    MotionData_ = _MotionData;

    Engine::Get<IRenderer2D>()->Flush();
    Flush();
    Model_ = _Model;
    Begin();
  }

  Instance& Instance = Instances_[Count_];
  DirectX::XMStoreFloat4x4(&Instance.World, _WorldMatrix);
  Instance.MaterialColor = _Color;

  if (++Count_ >= kModelBatchMaxNum || _MotionData.Number != 0 || _MotionData.Frame != 0.0f)
  {
    Flush();

    Model_ = _Model;
    Begin();
  }
}

void CRenderer3D::Begin()
{
  DirectX::XMStoreFloat4x4(&ConstantBuffer_.Get().ViewProjectionMatrix, DirectX::XMLoadFloat4x4(&ViewMatrix_)*DirectX::XMLoadFloat4x4(&ProjectionMatrix_));

  pImmediateContext_->OMSetBlendState(Engine::Get<IBlendState>()->GetBlendState(BlendState_), nullptr, 0xFFFFFFFF);
  pImmediateContext_->OMSetDepthStencilState(Engine::Get<IDepthStencilState>()->GetDepthStencilState(DepthStencilState_), 1);
  pImmediateContext_->RSSetState(Engine::Get<IRasterizerState>()->GetRasterizerState(RasterizerState_));
  pImmediateContext_->VSSetShader(Engine::Get<IVertexShader>()->GetVertexShader(VertexShader_), nullptr, 0);
  pImmediateContext_->PSSetShader(Engine::Get<IPixelShader>()->GetPixeShader(PixelShader_), nullptr, 0);
  pImmediateContext_->IASetInputLayout(pInputLayout_.Get());
  pImmediateContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  //  IASetVertexBuffers
  {
    UINT Stride = sizeof(Instance);
    UINT Offset = 0;

    pImmediateContext_->IASetVertexBuffers(1, 1, pInstanceBuffer_.GetAddressOf(), &Stride, &Offset);
  }

  //  VSSetConstantBuffers
  {
    ID3D11Buffer* pConstantBuffers[kConstantBufferMaxNum - 1];

    ID3D11Buffer* NullObject = nullptr;
    for (int i = 0; i < kConstantBufferMaxNum - 1; ++i)
    {
      ConstantBufferData& ConstantBuffer = VertexStageConstantBuffers_[i];
      if (ConstantBuffer.Size == 0)
      {
        pConstantBuffers[i] = NullObject;
      }
      else
      {
        pImmediateContext_->UpdateSubresource(pConstantBuffers[i] = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size), 0, 0, ConstantBuffer.pData, 0, 0);
      }
    }

    pImmediateContext_->VSSetConstantBuffers(1, kConstantBufferMaxNum - 1, pConstantBuffers);
  }

  //  PSSetConstantBuffers
  {
    ID3D11Buffer* pConstantBuffers[kConstantBufferMaxNum - 1];

    ID3D11Buffer* NullObject = nullptr;
    for (int i = 0; i < kConstantBufferMaxNum - 1; ++i)
    {
      ConstantBufferData& ConstantBuffer = PixelStageConstantBuffers_[i];

      if (ConstantBuffer.Size == 0)
      {
        pConstantBuffers[i] = NullObject;
      }
      else
      {
        pImmediateContext_->UpdateSubresource(pConstantBuffers[i] = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size), 0, 0, ConstantBuffer.pData, 0, 0);
      }
    }

    pImmediateContext_->PSSetConstantBuffers(1, kConstantBufferMaxNum - 1, pConstantBuffers);
  }

  //  PSSetSamplers
  {
    ID3D11SamplerState* pSamplerStatus[kSamplerStateMaxNum];

    for (int i = 0; i < kSamplerStateMaxNum; ++i)
    {
      pSamplerStatus[i] = Engine::Get<ISamplerState>()->GetSamplerState(SamplerStatus_[i]);
    }

    pImmediateContext_->PSSetSamplers(0, kSamplerStateMaxNum, pSamplerStatus);
  }

  //  PSSetShaderResources
  {
    ID3D11ShaderResourceView* pShaderResourceViews[kTextureMaxNum - 1];

    for (int i = 0; i < kTextureMaxNum - 1; ++i)
    {
      pShaderResourceViews[i] = Engine::Get<ITexture>()->GetShaderResourceView(Textures_[i].GetID());
    }

    pImmediateContext_->PSSetShaderResources(1, kTextureMaxNum - 1, pShaderResourceViews);
  }

  //  OMSetRenderTargets
  {
    ID3D11RenderTargetView** ppRenderTargetView = Engine::Get<IRenderTarget>()->GetRenderTargetView(RenderTarget_);
    ID3D11DepthStencilView* pDepthStencilView = Engine::Get<IRenderTarget>()->GetDepthStencilView(RenderTarget_);

    if (ppRenderTargetView == nullptr && pDepthStencilView == nullptr)
    {
      pImmediateContext_->OMSetRenderTargets(1, ppRenderTargetView_, pDepthStencilView_);
    }
    else
    {
      pImmediateContext_->OMSetRenderTargets(1, ppRenderTargetView, pDepthStencilView);
    }
  }

  //  頂点バッファオブジェクトを書き換え
  D3D11_MAPPED_SUBRESOURCE MappedSubresorce;
  pImmediateContext_->Map(pInstanceBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedSubresorce);
  Instances_ = static_cast<Instance*>(MappedSubresorce.pData);
}

void CRenderer3D::Flush()
{
  if (!Instances_)return;

  pImmediateContext_->Unmap(pInstanceBuffer_.Get(), 0);

  const ModelData& ModelData = Engine::Get<IModel>()->GetModelData(Model_.GetID());
  ID3D11Buffer* pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer_.Size);

  UINT Stride = sizeof(Vertex);
  UINT Offset = 0;
  for (auto& Mesh : ModelData.Meshes)
  {
    pImmediateContext_->IASetVertexBuffers(0, 1, Mesh.pVertexBuffer.GetAddressOf(), &Stride, &Offset);
    pImmediateContext_->IASetIndexBuffer(Mesh.pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    ConstantBuffer_.Get().GlobalTransform = Mesh.GlobalTransform;

    //  ボーンアニメーション
    {
      const int SkeletalAnimationNum = (Mesh.SkeletalAnimations.size() > 0) ? Mesh.SkeletalAnimations[MotionData_.Number].size() : 0;

      if (SkeletalAnimationNum > 0)
      {
        const Skeletal& Skeletal = Mesh.SkeletalAnimations[MotionData_.Number].at(static_cast<size_t>(MotionData_.Frame / Mesh.SamplingTime));

        const int NumberOfBones = Skeletal.size();
        _ASSERT_EXPR_A(NumberOfBones < kModelBoneMaxNum, "'the NumberOfBones' exceeds kModelBoneMaxNum");

        for (int i = 0; i < NumberOfBones; ++i)
        {
          DirectX::XMStoreFloat4x4(&ConstantBuffer_.Get().BoneTransforms[i], DirectX::XMLoadFloat4x4(&Skeletal.at(i).Transform));
        }
      }
      else
      {
        for (int i = 0; i < kModelBoneMaxNum; ++i)
        {
          ConstantBuffer_.Get().BoneTransforms[i] = BoneNothingMatrix_;
        }
      }
    }

    for (auto& Subset : Mesh.Subsets)
    {
      ConstantBuffer_.Get().DiffuseColor = Subset.Diffuse.Color;

      pImmediateContext_->UpdateSubresource(pConstantBuffer, 0, 0, ConstantBuffer_.GetPtr(), 0, 0);
      pImmediateContext_->VSSetConstantBuffers(0, 1, &pConstantBuffer);
      pImmediateContext_->PSSetConstantBuffers(0, 1, &pConstantBuffer);

      ID3D11ShaderResourceView* pShaderResourceView = Engine::Get<ITexture>()->GetShaderResourceView(Subset.Diffuse.TextureID);
      pImmediateContext_->PSSetShaderResources(0, 1, &pShaderResourceView);

      pImmediateContext_->DrawIndexedInstanced(Subset.IndexCount - Subset.IndexStart, Count_, Subset.IndexStart, 0, 0);
    }
  }

  Model_ = hdx::Model();
  MotionData_ = hdx::MotionData();
  Count_ = 0;

  Instances_ = nullptr;
}

void CRenderer3D::CalcProjection()
{
  if (Camera_.isPerspective)
  {
    const hdx::float2 WindowSize = Engine::Get<ISystem>()->GetWindowSize();

    const float Aspect = WindowSize.x / WindowSize.y;

    DirectX::XMStoreFloat4x4(&ProjectionMatrix_, DirectX::XMMatrixPerspectiveFovLH(hdx::Radian(Camera_.Fov).GetValue(), Aspect, Camera_.Near, Camera_.Far));
  }
  else
  {
    constexpr float Width = 16.0f / 2.0f;
    constexpr float Height = 9.0f / 2.0f;

    DirectX::XMStoreFloat4x4(&ProjectionMatrix_, DirectX::XMMatrixOrthographicLH(Width, Height, Camera_.Near, Camera_.Far));
  }
}

void CRenderer3D::SetVertexShader(const hdx::VertexShader& _VertexShader)
{
  if (VertexShader_ == _VertexShader)return;

  VertexShader_ = _VertexShader;
}

void CRenderer3D::SetPixelShader(const hdx::PixelShader& _PixelShader)
{
  if (PixelShader_ == _PixelShader)return;

  PixelShader_ = _PixelShader;
}

void CRenderer3D::SetBlendState(const hdx::BlendState& _BlendState)
{
  if (BlendState_ == _BlendState)return;

  BlendState_ = _BlendState;
}

void CRenderer3D::SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot)
{
  hdx::SamplerState& SamplerState = SamplerStatus_[_Slot];
  if (SamplerState == _SamplerState)return;

  SamplerState = _SamplerState;
}

void CRenderer3D::SetRasterizerState(const hdx::RasterizerState& _RasterizerState)
{
  if (RasterizerState_ == _RasterizerState)return;

  RasterizerState_ = _RasterizerState;
}

void CRenderer3D::SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
{
  if (DepthStencilState_ == _DepthStencilState)return;

  DepthStencilState_ = _DepthStencilState;
}

void CRenderer3D::SetTexture(const hdx::Texture& _Texture, UINT _Slot)
{
  hdx::Texture& Texture = Textures_[_Slot];
  if (Texture == _Texture)return;

  Texture = _Texture;
}

void CRenderer3D::CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  Engine::Get<ITexture>()->SetShaderResouceView(_RenderTarget, Engine::Get<IRenderTarget>()->GetShaderResourceView(_RenderTarget));
  Textures_[0] = _RenderTarget;
}

void CRenderer3D::RestoreRenderTarget()
{
  if (RenderTarget_.GetSize() == hdx::int2())return;

  Flush();

  ID3D11ShaderResourceView* NullObject = nullptr;
  pImmediateContext_->PSSetShaderResources(0, 1, &NullObject);

  CreateTextureFromRenderTarget(RenderTarget_);
  RenderTarget_ = hdx::RenderTarget();
  SetViewPort(Engine::Get<ISystem>()->GetWindowSize());
}

void CRenderer3D::SetRenderTarget(const hdx::RenderTarget& _RenderTarger)
{
  if (RenderTarget_ == _RenderTarger)return;

  Flush();

  ID3D11ShaderResourceView* NullObject = nullptr;
  pImmediateContext_->PSSetShaderResources(0, 1, &NullObject);

  if (RenderTarget_.GetSize() != hdx::int2())
  {
    CreateTextureFromRenderTarget(RenderTarget_);
    SetViewPort(RenderTarget_.GetSize());
  }
  RenderTarget_ = _RenderTarger;
}

void CRenderer3D::SetCamera(const hdx::Camera& _Camera)
{
  Camera_ = _Camera;

  CalcProjection();
  CalcView();
}

void CRenderer3D::SetConstantBuffer(hdx::ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot)
{
  switch (_Stage)
  {
  case hdx::ShaderStage::Vertex:
    VertexStageConstantBuffers_[_Slot - 1] = ConstantBufferData(_Size, const_cast<void*>(_pData));
    break;
  case hdx::ShaderStage::Pixel:
    PixelStageConstantBuffers_[_Slot - 1] = ConstantBufferData(_Size, const_cast<void*>(_pData));
    break;
  default: assert(false);
  }
}

void CRenderer3D::SetLightDirection(const hdx::float3& _LightDirection)
{
  ConstantBuffer_.Get().LightDirection.x = _LightDirection.x;
  ConstantBuffer_.Get().LightDirection.y = _LightDirection.y;
  ConstantBuffer_.Get().LightDirection.z = _LightDirection.z;
}

void CRenderer3D::FreeCamera()
{

}

void CRenderer3D::CalcView()
{
  DirectX::XMStoreFloat4x4(&ViewMatrix_, DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(Camera_.Pos.x, Camera_.Pos.y, Camera_.Pos.z, 1.0f),
    DirectX::XMVectorSet(Camera_.Target.x, Camera_.Target.y, Camera_.Target.z, 1.0f),
    DirectX::XMVectorSet(Camera_.Up.x, Camera_.Up.y, Camera_.Up.z, 0.0f)));
}

hdx::Matrix CRenderer3D::GetProjectionMatrix()const
{
  return DirectX::XMLoadFloat4x4(&ProjectionMatrix_);
}

hdx::Matrix CRenderer3D::GetViewMatrix()const
{
  return DirectX::XMLoadFloat4x4(&ViewMatrix_);
}

void CRenderer3D::SetViewPort(const hdx::float2& _Size)
{
  D3D11_VIEWPORT ViewPort;
  UINT ViewPortNum = 1;

  //  現在のデータを取得
  pImmediateContext_->RSGetViewports(&ViewPortNum, &ViewPort);

  ViewPort.Width = _Size.x;
  ViewPort.Height = _Size.y;

  //  設定を反映
  pImmediateContext_->RSSetViewports(1, &ViewPort);
}
