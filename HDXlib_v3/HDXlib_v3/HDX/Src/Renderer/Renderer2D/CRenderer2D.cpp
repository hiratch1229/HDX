#include "CRenderer2D.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Renderer/Renderer3D/IRenderer3D.hpp"
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

void CRenderer2D::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
{
  pRenderer_ = IRenderer::Get();
  pRenderer_->Initialize(_pImmediateContext, _ppRenderTargetView, _pDepthStencilView);

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

  VertexShader_ = Engine::Get<IVertexShader>()->CreateDefault2D();
  PixelShader_ = Engine::Get<IPixelShader>()->CreateDefault2D();
}

void CRenderer2D::Begin()
{
  pRenderer_->SetVertexBuffer(pVertexBuffer_.GetAddressOf(), sizeof(Vertex), 0);
  pRenderer_->SetVertexBuffer(pInstanceBuffer_.GetAddressOf(), sizeof(Instance), 1);

  pRenderer_->SetBlendState(Engine::Get<IBlendState>()->GetBlendState(BlendState_));
  for (int i = 0; i < kConstantBufferMaxNum; ++i)
  {
    ConstantBufferData& ConstantBuffer = VertexStageConstantBuffers_[i];

    if (ConstantBuffer.Size == 0)continue;

    ID3D11Buffer* pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size);
    pRenderer_->UpdateSubresource(pConstantBuffer, ConstantBuffer.pData);
    pRenderer_->SetConstatBufferVS(&pConstantBuffer, i);
  }
  for (int i = 0; i < kConstantBufferMaxNum; ++i)
  {
    ConstantBufferData& ConstantBuffer = PixelStageConstantBuffers_[i];

    if (ConstantBuffer.Size == 0)continue;

    ID3D11Buffer* pConstantBuffer = Engine::Get<IConstantBuffer>()->GetConstantBuffer(ConstantBuffer.Size);
    pRenderer_->UpdateSubresource(pConstantBuffer, ConstantBuffer.pData);
    pRenderer_->SetConstatBufferPS(&pConstantBuffer, i);
  }
  pRenderer_->SetRasterizerState(Engine::Get<IRasterizerState>()->GetRasterizerState(RasterizerState_));
  pRenderer_->SetDepthStencilState(Engine::Get<IDepthStencilState>()->GetDepthStencilState(DepthStencilState_));
  pRenderer_->SetRenderTarget(Engine::Get<IRenderTarget>()->GetRenderTargetView(RenderTarget_), Engine::Get<IRenderTarget>()->GetDepthStencilView(RenderTarget_));
  for (int i = 0; i < kSamplerStateMaxNum; ++i)
  {
    pRenderer_->SetSamplersState(Engine::Get<ISamplerState>()->GetSamplerState(SamplerStatus_[i]), i);
  }
  for (int i = 0; i < kTextureMaxNum; ++i)
  {
    const int ID = Textures_[i].GetID();
    if (ID < 0)continue;

    pRenderer_->SetShaderResouceView(Engine::Get<ITexture>()->GetShaderResourceView(ID), i);
  }
  pRenderer_->SetVertexShader(Engine::Get<IVertexShader>()->GetVertexShader(VertexShader_));
  pRenderer_->SetInputLayout(Engine::Get<IVertexShader>()->GetInputLayout(VertexShader_));
  pRenderer_->SetPixelShader(Engine::Get<IPixelShader>()->GetPixeShader(PixelShader_));
  pRenderer_->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

  //  頂点バッファオブジェクトを書き換え
  D3D11_MAPPED_SUBRESOURCE MappedSubresorce;
  pRenderer_->Map(pInstanceBuffer_.Get(), &MappedSubresorce);
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

  const float cos = cosf(_Angle.GetValue());
  const float sin = sinf(_Angle.GetValue());
  const float Width = 2.0f / Engine::Get<ISystem>()->GetWindowWidth();
  const float Height = -2.0f / Engine::Get<ISystem>()->GetWindowHeight();

  Instance.NDCTransform._11 = Width*_DstSize.X*cos;
  Instance.NDCTransform._21 = Height*_DstSize.X*sin;
  Instance.NDCTransform._31 = 0.0f;
  Instance.NDCTransform._41 = 0.0f;
  Instance.NDCTransform._12 = Width*_DstSize.Y*-sin;
  Instance.NDCTransform._22 = Height*_DstSize.Y*cos;
  Instance.NDCTransform._32 = 0.0f;
  Instance.NDCTransform._42 = 0.0f;
  Instance.NDCTransform._13 = 0.0f;
  Instance.NDCTransform._23 = 0.0f;
  Instance.NDCTransform._33 = 1.0f;
  Instance.NDCTransform._43 = 0.0f;
  Instance.NDCTransform._14 = Width*(-Center.X*cos + -Center.Y*-sin + Center.X + _DstLeftTop.X) - 1.0f;
  Instance.NDCTransform._24 = Height*(-Center.X*sin + -Center.Y*cos + Center.Y + _DstLeftTop.Y) + 1.0f;
  Instance.NDCTransform._34 = 0.0f;
  Instance.NDCTransform._44 = 1.0f;

  const hdx::int2 Size = _Texture.GetSize();

  Instance.TexcoordTransfrom.x = ((!_HorizontalFlip) ? _SrcLeftPos.X : _SrcSize.X) / Size.X;
  Instance.TexcoordTransfrom.y = ((!_VerticalFlip) ? _SrcLeftPos.Y : _SrcSize.Y) / Size.Y;
  Instance.TexcoordTransfrom.z = ((!_HorizontalFlip) ? _SrcSize.X : _SrcLeftPos.X) / Size.X;
  Instance.TexcoordTransfrom.w = ((!_VerticalFlip) ? _SrcSize.Y : _SrcLeftPos.Y) / Size.Y;

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

  pRenderer_->Unmap(pInstanceBuffer_.Get());
  pRenderer_->DrawInstanced(4, Count_, 0, 0);

  Textures_[0] = hdx::Texture();
  Count_ = 0;

  Instances_ = nullptr;
}

void CRenderer2D::SetBlendState(const hdx::BlendState& _BlendState)
{
  if (BlendState_ == _BlendState)return;

  BlendState_ = _BlendState;
}

void CRenderer2D::SetConstantBuffer(hdx::ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot)
{
  switch (_Stage)
  {
  case hdx::ShaderStage::Vertex:
    VertexStageConstantBuffers_[_Slot] = ConstantBufferData(_Size, const_cast<void*>(_pData));
    break;
  case hdx::ShaderStage::Pixel:
    PixelStageConstantBuffers_[_Slot] = ConstantBufferData(_Size, const_cast<void*>(_pData));
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
  pRenderer_->SetShaderResouceView(&NullObject, 0);

  if (RenderTarget_.GetSize() != hdx::int2())
  {
    CreateTextureFromRenderTarget(RenderTarget_);
    pRenderer_->SetViewPort(RenderTarget_.GetSize());
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
  pRenderer_->SetShaderResouceView(&NullObject, 0);

  CreateTextureFromRenderTarget(RenderTarget_);
  RenderTarget_ = hdx::RenderTarget();
  pRenderer_->SetViewPort(Engine::Get<ISystem>()->GetWindowSize());
}
