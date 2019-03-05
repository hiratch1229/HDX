#include "CRenderer2D.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Renderer/Renderer3D/IRenderer3D.hpp"
#include "Src/Graphics/BlendState/IBlendState.hpp"
#include "Src/Graphics/ConstantBuffer/IConstantBuffer.hpp"
#include "Src/Graphics/RasterizerState/IRasterizerState.hpp"
#include "Src/Graphics/DepthStencilState/IDepthStencilState.hpp"
#include "Src/Graphics/RenderTarget/IRenderTarget.hpp"
#include "Src/Graphics/SamplerState/ISamplerState.hpp"
#include "Src/Texture/ITexture.hpp"
#include "Src/Shaders/VertexShader/IVertexShader.hpp"
#include "Src/Shaders/PixelShader/IPixelShader.hpp"
#include "Src/Misc.hpp"

void CRenderer2D::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
{
  pImmediateContext_ = _pImmediateContext;
  ppRenderTargetView_ = _ppRenderTargetView;
  pDepthStencilView_ = _pDepthStencilView;

  VertexShader_ = Engine::Get<IVertexShader>()->CreateDefault2D(pInputLayout_.GetAddressOf());
  PixelShader_ = Engine::Get<IPixelShader>()->CreateDefault2D();

  //  エラーチェック用
  HRESULT hr = S_OK;

  //  頂点バッファを作成
  {
    Vertex Vertices[] =
    {
      { hdx::float3(0.0f, 0.0f, 0.0f), hdx::float2(0.0f, 0.0f) },
      { hdx::float3(1.0f, 0.0f, 0.0f), hdx::float2(1.0f, 0.0f) },
      { hdx::float3(0.0f, 1.0f, 0.0f), hdx::float2(0.0f, 1.0f) },
      { hdx::float3(1.0f, 1.0f, 0.0f), hdx::float2(1.0f, 1.0f) },
    };

    D3D11_BUFFER_DESC BufferDesc{};
    {
      BufferDesc.ByteWidth = sizeof(Vertices);
      BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
      BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
      BufferDesc.CPUAccessFlags = 0;
      BufferDesc.MiscFlags = 0;
      BufferDesc.StructureByteStride = 0;
    }

    D3D11_SUBRESOURCE_DATA InitialData{};
    {
      InitialData.pSysMem = Vertices;
      InitialData.SysMemPitch = 0;
      InitialData.SysMemSlicePitch = 0;
    }
    hr = _pDevice->CreateBuffer(&BufferDesc, &InitialData, pVertexBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  //  インスタンスバッファを作成
  {
    Instances_ = new Instance[kSpriteBatchMaxNum];

    D3D11_BUFFER_DESC BufferDesc{};
    {
      BufferDesc.ByteWidth = sizeof(Instance) * kSpriteBatchMaxNum;
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
}

void CRenderer2D::Begin()
{
  pImmediateContext_->OMSetBlendState(Engine::Get<IBlendState>()->GetBlendState(BlendState_), nullptr, 0xFFFFFFFF);
  pImmediateContext_->OMSetDepthStencilState(Engine::Get<IDepthStencilState>()->GetDepthStencilState(DepthStencilState_), 1);
  pImmediateContext_->RSSetState(Engine::Get<IRasterizerState>()->GetRasterizerState(RasterizerState_));
  pImmediateContext_->VSSetShader(Engine::Get<IVertexShader>()->GetVertexShader(VertexShader_), nullptr, 0);
  pImmediateContext_->PSSetShader(Engine::Get<IPixelShader>()->GetPixeShader(PixelShader_), nullptr, 0);
  pImmediateContext_->IASetInputLayout(pInputLayout_.Get());
  pImmediateContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

  //  IASetVertexBuffers
  {
    ID3D11Buffer* pVertexBuffers[2] = { pVertexBuffer_.Get(), pInstanceBuffer_.Get() };
    UINT Strides[2] = { sizeof(Vertex), sizeof(Instance) };
    UINT Offsets[2] = { 0, 0 };

    pImmediateContext_->IASetVertexBuffers(0, 2, pVertexBuffers, Strides, Offsets);
  }

  //  VSSetConstantBuffers
  {
    ID3D11Buffer* pConstantBuffers[kConstantBufferMaxNum];

    for (int i = 0; i < kConstantBufferMaxNum; ++i)
    {
      ConstantBufferData& ConstantBuffer = VertexStageConstantBuffers_[i];

      if (ConstantBuffer.ID < 0)
      {
        ID3D11Buffer* NullObject = nullptr;
        pConstantBuffers[i] = NullObject;
      }
      else
      {
        pImmediateContext_->UpdateSubresource(pConstantBuffers[i] = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.ID), 0, 0, ConstantBuffer.pData, 0, 0);
      }
    }

    pImmediateContext_->VSSetConstantBuffers(0, kConstantBufferMaxNum, pConstantBuffers);
  }

  //  PSSetConstantBuffers
  {
    ID3D11Buffer* pConstantBuffers[kConstantBufferMaxNum];

    for (int i = 0; i < kConstantBufferMaxNum; ++i)
    {
      ConstantBufferData& ConstantBuffer = PixelStageConstantBuffers_[i];

      if (ConstantBuffer.ID < 0)
      {
        ID3D11Buffer* NullObject = nullptr;
        pConstantBuffers[i] = NullObject;
      }
      else
      {
        pImmediateContext_->UpdateSubresource(pConstantBuffers[i] = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.ID), 0, 0, ConstantBuffer.pData, 0, 0);
      }
    }

    pImmediateContext_->PSSetConstantBuffers(0, kConstantBufferMaxNum, pConstantBuffers);
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
    ID3D11ShaderResourceView* pShaderResourceViews[kTextureMaxNum];

    for (int i = 0; i < kTextureMaxNum; ++i)
    {
      pShaderResourceViews[i] = Engine::Get<ITexture>()->GetShaderResourceView(Textures_[i].GetID());
    }

    pImmediateContext_->PSSetShaderResources(0, kTextureMaxNum, pShaderResourceViews);
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

void CRenderer2D::Draw(const hdx::Texture& _Texture, const hdx::float2& _DstLeftTop, const hdx::float2& _DstSize, const hdx::float2& _SrcLeftPos, const hdx::float2& _SrcSize, const hdx::Radian& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const hdx::ColorF& _Color)
{
  if (!Instances_ || Textures_[0] != _Texture)
  {
    Engine::Get<IRenderer3D>()->Flush();
    Flush();

    Textures_[0] = _Texture;
    Begin();
  }

  Instance& Instance = Instances_[Count_];

  const hdx::float2 Center = _DstLeftTop + _DstSize / 2.0f;
  const hdx::float2 WindowSize = Engine::Get<ISystem>()->GetWindowSize();

  const float cos = cosf(_Angle);
  const float sin = sinf(_Angle);
  const float Width = 2.0f / WindowSize.x;
  const float Height = -2.0f / WindowSize.y;

  Instance.NDCTransform._11 = Width*_DstSize.x*cos;
  Instance.NDCTransform._21 = Height*_DstSize.x*sin;
  Instance.NDCTransform._31 = 0.0f;
  Instance.NDCTransform._41 = 0.0f;
  Instance.NDCTransform._12 = Width*_DstSize.y*-sin;
  Instance.NDCTransform._22 = Height*_DstSize.y*cos;
  Instance.NDCTransform._32 = 0.0f;
  Instance.NDCTransform._42 = 0.0f;
  Instance.NDCTransform._13 = 0.0f;
  Instance.NDCTransform._23 = 0.0f;
  Instance.NDCTransform._33 = 1.0f;
  Instance.NDCTransform._43 = 0.0f;
  Instance.NDCTransform._14 = Width*(-Center.x*cos + -Center.y*-sin + Center.x + _DstLeftTop.x) - 1.0f;
  Instance.NDCTransform._24 = Height*(-Center.x*sin + -Center.y*cos + Center.y + _DstLeftTop.y) + 1.0f;
  Instance.NDCTransform._34 = 0.0f;
  Instance.NDCTransform._44 = 1.0f;

  const hdx::int2 Size = _Texture.GetSize();

  Instance.TexcoordTransfrom.x = ((!_HorizontalFlip) ? _SrcLeftPos.x : _SrcSize.x) / Size.x;
  Instance.TexcoordTransfrom.y = ((!_VerticalFlip) ? _SrcLeftPos.y : _SrcSize.y) / Size.y;
  Instance.TexcoordTransfrom.z = ((!_HorizontalFlip) ? _SrcSize.x : _SrcLeftPos.x) / Size.x;
  Instance.TexcoordTransfrom.w = ((!_VerticalFlip) ? _SrcSize.y : _SrcLeftPos.y) / Size.y;

  Instance.Color = _Color;

  if (++Count_ >= kSpriteBatchMaxNum)
  {
    Flush();

    Textures_[0] = _Texture;
    Begin();
  }
}

void CRenderer2D::Flush()
{
  if (!Instances_)return;

  pImmediateContext_->Unmap(pInstanceBuffer_.Get(), 0);
  pImmediateContext_->DrawInstanced(4, Count_, 0, 0);

  Textures_[0] = hdx::Texture();
  Count_ = 0;

  Instances_ = nullptr;
}

void CRenderer2D::SetBlendState(const hdx::BlendState& _BlendState)
{
  if (BlendState_ == _BlendState)return;

  BlendState_ = _BlendState;
}

void CRenderer2D::SetConstantBuffer(hdx::ShaderStage _Stage, UINT _ID, const void* _pData, UINT _Slot)
{
  switch (_Stage)
  {
  case hdx::ShaderStage::Vertex:
    VertexStageConstantBuffers_[_Slot] = ConstantBufferData(_ID, const_cast<void*>(_pData));
    break;
  case hdx::ShaderStage::Pixel:
    PixelStageConstantBuffers_[_Slot] = ConstantBufferData(_ID, const_cast<void*>(_pData));
    break;
  default: assert(false);
  }
}

void CRenderer2D::SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
{
  if (DepthStencilState_ == _DepthStencilState)return;

  DepthStencilState_ = _DepthStencilState;
}

void CRenderer2D::SetRasterizerState(const hdx::RasterizerState& _RasterizerState)
{
  if (RasterizerState_ == _RasterizerState)return;

  RasterizerState_ = _RasterizerState;
}

void CRenderer2D::CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  Engine::Get<ITexture>()->SetShaderResouceView(_RenderTarget, Engine::Get<IRenderTarget>()->GetShaderResourceView(_RenderTarget));
  Textures_[0] = _RenderTarget;
}

void CRenderer2D::SetRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  if (RenderTarget_ == _RenderTarget)return;

  ID3D11ShaderResourceView* NullObject = nullptr;
  pImmediateContext_->PSSetShaderResources(0, 1, &NullObject);

  if (RenderTarget_.GetSize() != hdx::int2())
  {
    CreateTextureFromRenderTarget(RenderTarget_);
    SetViewPort(RenderTarget_.GetSize());
  }
  RenderTarget_ = _RenderTarget;
}

void CRenderer2D::SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot)
{
  hdx::SamplerState& SamplerState = SamplerStatus_[_Slot];
  if (SamplerState == _SamplerState)return;

  SamplerState = _SamplerState;
}

void CRenderer2D::SetTexture(const hdx::Texture& _Texture, UINT _Slot)
{
  hdx::Texture& Texture = Textures_[_Slot];
  if (Texture == _Texture)return;

  Texture = _Texture;
}

void CRenderer2D::SetVertexShader(const hdx::VertexShader& _VertexShader)
{
  if (VertexShader_ == _VertexShader)return;

  VertexShader_ = _VertexShader;
}

void CRenderer2D::SetPixelShader(const hdx::PixelShader& _PixelShader)
{
  if (PixelShader_ == _PixelShader)return;

  PixelShader_ = _PixelShader;
}

void CRenderer2D::RestoreRenderTarget()
{
  if (RenderTarget_.GetSize() == hdx::int2())return;

  ID3D11ShaderResourceView* NullObject = nullptr;
  pImmediateContext_->PSSetShaderResources(0, 1, &NullObject);

  CreateTextureFromRenderTarget(RenderTarget_);
  RenderTarget_ = hdx::RenderTarget();
  SetViewPort(Engine::Get<ISystem>()->GetWindowSize());
}

void CRenderer2D::SetViewPort(const hdx::float2& _Size)
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
