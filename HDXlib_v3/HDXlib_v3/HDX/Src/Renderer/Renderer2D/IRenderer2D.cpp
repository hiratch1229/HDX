#include "IRenderer2D.hpp"

#include "../../Engine.hpp"
#include "../../System/ISystem.hpp"
#include "../../Texture/ITexture.hpp"
#include "../../BlendState/IBlendState.hpp"
#include "../../SamplerState/ISamplerState.hpp"
#include "../../RasterizerState/IRasterizerState.hpp"
#include "../../DepthStencilState/IDepthStencilState.hpp"
#include "../../VertexShader/IVertexShader.hpp"
#include "../../PixelShader/IPixelShader.hpp"
#include "../../RenderTarget/IRenderTarget.hpp"
#include "../../Misc.hpp"

#include "../../../Include/System.hpp"
#include "../../../Include/VertexShader.hpp"
#include "../../../Include/PixelShader.hpp"
#include "../../../Include/BlendState.hpp"
#include "../../../Include/SamplerState.hpp"
#include "../../../Include/RasterizerState.hpp"
#include "../../../Include/DepthStencilState.hpp"
#include "../../../Include/Texture.hpp"
#include "../../../Include/RenderTarget.hpp"

#include "../../../Include/Type2.hpp"
#include "../../../Include/Type3.hpp"
#include "../../../Include/Color.hpp"

#include "../../../Include/Constants.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

namespace
{
  hdx::VertexShader CurrentVertexShader;
  hdx::PixelShader CurrentPixelShader;
  hdx::BlendState CurrentBlendState = hdx::BlendState::Default;
  hdx::RasterizerState CurrentRasterizerState = hdx::RasterizerState::Default2D;
  hdx::DepthStencilState CurrentDepthStencilState = hdx::DepthStencilState::Default2D;
  hdx::RenderTarget CurrentRenderTarget;

  hdx::SamplerState CurrentSamplerStatus[hdx::SamplerStateMaxNum];
  hdx::Texture CurrentTextures[hdx::TextureMaxNum];

  Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
  Microsoft::WRL::ComPtr<ID3D11Buffer> pInstanceBuffer;

  struct Vertex
  {
    hdx::float3 Position;
    hdx::float2 Texcoord;
  };
  struct Instance
  {
    DirectX::XMFLOAT4X4 NDCTransform;
    DirectX::XMFLOAT4 TexcoordTransfrom;
    hdx::ColorF Color;
  };

  Instance* Instances = nullptr;
  int Count = 0;

  constexpr int Num = 10000;
}

IRenderer2D::IRenderer2D()
{
  TIMER_START("Renderer2D");

  CurrentSamplerStatus[0] = hdx::SamplerState::Default2D;

  TIMER_END("Renderer2D");
}

void IRenderer2D::Initialize()
{
  //  エラーチェック用
  HRESULT hr = S_OK;

  ID3D11Device* pDevice = Engine::Get<ISystem>()->GetDevice();

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
    hr = pDevice->CreateBuffer(&BufferDesc, &InitialData, pVertexBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  //  インスタンスバッファを作成
  {
    Instances = new Instance[Num];

    D3D11_BUFFER_DESC BufferDesc{};
    {
      BufferDesc.ByteWidth = sizeof(Instance) * Num;
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

    hr = pDevice->CreateBuffer(&BufferDesc, &InitialData, pInstanceBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    delete[] Instances;
    Instances = nullptr;
  }
}

void IRenderer2D::Draw(const hdx::Texture& _Texture, const hdx::float2& _DstLeftTop, const hdx::float2& _DstSize, const hdx::float2& _SrcLeftPos, const hdx::float2& _SrcSize, const hdx::Radian& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const hdx::ColorF& _Color)
{
  if (!Instances || CurrentTextures[0] != _Texture)
  {
    End();
    Begin(_Texture);
  }

  Instance& Instance = Instances[Count];

  const hdx::float2 Center = _DstLeftTop + _DstSize / 2.0f;

  const float cos = cosf(_Angle.GetValue());
  const float sin = sinf(_Angle.GetValue());
  const float Width = 2.0f / hdx::System::GetWindowWidth();
  const float Height = -2.0f / hdx::System::GetWindowHeight();

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

  if (++Count >= Num)
  {
    End();
    Begin(_Texture);
  }
}

void IRenderer2D::Begin(const hdx::Texture& _Texture)
{
  CurrentTextures[0] = _Texture;

  IRenderer::SetVertexBuffer(pVertexBuffer.GetAddressOf(), sizeof(Vertex), 0);
  IRenderer::SetVertexBuffer(pInstanceBuffer.GetAddressOf(), sizeof(Instance), 1);

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

  for (int i = 0; i < hdx::TextureMaxNum; ++i)
  {
    const int ID = CurrentTextures[i].GetID();
    if (ID < 0)continue;

    IRenderer::SetShaderResouceView(Engine::Get<ITexture>()->GetShaderResourceView(CurrentTextures[i].GetID()), i);
  }

  IRenderer::SetRenderTarget(Engine::Get<IRenderTarget>()->GetRenderTargetView(CurrentRenderTarget), Engine::Get<IRenderTarget>()->GetDepthStencilView(CurrentRenderTarget));

  //  頂点バッファオブジェクトを書き換え
  D3D11_MAPPED_SUBRESOURCE MappedSubresorce;
  Map(pInstanceBuffer.Get(), &MappedSubresorce);
  Instances = static_cast<Instance*>(MappedSubresorce.pData);
}

void IRenderer2D::End()
{
  if (!Instances)return;

  Unmap(pInstanceBuffer.Get());
  DrawInstanced(4, Count, 0, 0);

  CurrentTextures[0] = hdx::Texture();
  Count = 0;

  Instances = nullptr;
}

void IRenderer2D::SetVertexShader(const hdx::VertexShader& _VertexShader)
{
  if (CurrentVertexShader == _VertexShader)return;

  CurrentVertexShader = _VertexShader;
  End();
  Begin(CurrentTextures[0]);
}

void IRenderer2D::SetPixelShader(const hdx::PixelShader& _PixelShader)
{
  if (CurrentPixelShader == _PixelShader)return;

  CurrentPixelShader = _PixelShader;
  End();
  Begin(CurrentTextures[0]);
}

void IRenderer2D::SetBlendState(const hdx::BlendState& _BlendState)
{
  if (CurrentBlendState == _BlendState)return;

  CurrentBlendState = _BlendState;
  End();
  Begin(CurrentTextures[0]);
}

void IRenderer2D::SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot)
{
  hdx::SamplerState& CurrentSamplerState = CurrentSamplerStatus[_Slot];
  if (CurrentSamplerState == _SamplerState)return;

  CurrentSamplerState = _SamplerState;
  End();
  Begin(CurrentTextures[0]);
}

void IRenderer2D::SetRasterizerState(const hdx::RasterizerState& _RasterizerState)
{
  if (CurrentRasterizerState == _RasterizerState)return;

  CurrentRasterizerState = _RasterizerState;
  End();
  Begin(CurrentTextures[0]);
}

void IRenderer2D::SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
{
  if (CurrentDepthStencilState == _DepthStencilState)return;

  CurrentDepthStencilState = _DepthStencilState;
  End();
  Begin(CurrentTextures[0]);
}

void IRenderer2D::SetTexture(const hdx::Texture& _Texture, UINT _Slot)
{
  hdx::Texture& CurrentTexture = CurrentTextures[_Slot];
  if (CurrentTexture == _Texture)return;

  CurrentTexture = _Texture;
  End();
  Begin(CurrentTextures[0]);
}

inline void CreateTextureFromRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  Engine::Get<ITexture>()->SetShaderResouceView(_RenderTarget, Engine::Get<IRenderTarget>()->GetShaderResourceView(_RenderTarget));
}

void IRenderer2D::RestoreRenderTarget()
{
  if (CurrentRenderTarget.GetSize() == hdx::int2())return;

  CreateTextureFromRenderTarget(CurrentRenderTarget);
  CurrentRenderTarget = hdx::RenderTarget();
}

void IRenderer2D::SetRenderTarget(const hdx::RenderTarget& _RenderTarger)
{
  if (CurrentRenderTarget == _RenderTarger)return;

  if (CurrentRenderTarget.GetSize() != hdx::int2())
  {
    CreateTextureFromRenderTarget(CurrentRenderTarget);
  }
  CurrentRenderTarget = _RenderTarger;
}
