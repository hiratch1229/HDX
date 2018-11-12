#include "../../Include/RenderTarget.hpp"

#include "../Engine.hpp"
#include "../RenderTarget/IRenderTarget.hpp"

//#include <HDX/Color.hpp>
//#include <HDX/Vertex.hpp>
//#include <HDX/Angle.hpp>
//#include <HDX/VertexShader/IVertexShader.hpp>
//#include <HDX/PixelShader/IPixelShader.hpp>
//#include <HDX/VertexShader/VertexShader.hpp>
//#include <HDX/PixelShader/PixelShader.hpp>
//#include <HDX/Math.hpp>
//
//#include <HDX/System/System.hpp>
//#include <d3d11.h>
//#include <wrl.h>

namespace hdx
{
  inline void CreateRenderTarget(const RenderTarget& _RenderTarget)
  {
    Engine::GetRenderTarget()->CreateRenderTarget(_RenderTarget);
  }

  RenderTarget::RenderTarget()
  {
    Size_ = hdx::int2();
  }

  RenderTarget::RenderTarget(const int2& _Size)
    : Texture(_Size)
  {
    CreateRenderTarget(*this);
  }

  RenderTarget::RenderTarget(UINT _Width, UINT _Height)
    : Texture({ static_cast<int>(_Width), static_cast<int>(_Height) })
  {
    CreateRenderTarget(*this);
  }

  void RenderTarget::Clear(const ColorF& _Color)
  {
    Engine::GetRenderTarget()->ClearRenderTarget(*this, _Color);
  }

  //class RenderTarget::Impl
  //{
  //public:
  //  Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView_;
  //  Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  pDepthStencilView_;
  //  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResouceView_;
  //
  //  Impl()
  //  {
  //    HRESULT hr = S_OK;
  //
  //    Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
  //    hr = detail::System::Get()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
  //    _ASSERT_EXPR(SUCCEEDED(hr), L"GetBuffer");
  //
  //    D3D11_TEXTURE2D_DESC RenderTargetDesc;
  //    pBackBuffer->GetDesc(&RenderTargetDesc);
  //    RenderTargetDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
  //
  //    Microsoft::WRL::ComPtr<ID3D11Texture2D> pRenderTarget;
  //    hr = detail::System::Get()->GetDevice()->CreateTexture2D(&RenderTargetDesc, nullptr, pRenderTarget.GetAddressOf());
  //    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");
  //
  //    hr = detail::System::Get()->GetDevice()->CreateRenderTargetView(pRenderTarget.Get(), nullptr, pRenderTargetView_.GetAddressOf());
  //    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRenderTargetView");
  //
  //    //  深度ステンシルビューの作成
  //    {
  //      D3D11_TEXTURE2D_DESC DepthStencilBufferDesc = RenderTargetDesc;
  //      Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthStencilBuffer;
  //      DepthStencilBufferDesc.MipLevels = 1;
  //      DepthStencilBufferDesc.ArraySize = 1;
  //      DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  //      DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  //      DepthStencilBufferDesc.CPUAccessFlags = 0;
  //      DepthStencilBufferDesc.MiscFlags = 0;
  //
  //      hr = detail::System::Get()->GetDevice()->CreateTexture2D(&DepthStencilBufferDesc, nullptr, DepthStencilBuffer.GetAddressOf());
  //      _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");
  //
  //      DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
  //      detail::System::Get()->GetSwapChain()->GetDesc(&SwapChainDesc);
  //
  //      D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
  //      DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
  //      DepthStencilViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
  //      DepthStencilViewDesc.Flags = 0;
  //      DepthStencilViewDesc.Texture2D.MipSlice = 0;
  //
  //      hr = detail::System::Get()->GetDevice()->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, pDepthStencilView_.GetAddressOf());
  //      _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilView");
  //    }
  //  }
  //};
  //
  //RenderTarget::RenderTarget()
  //  : pImpl_(new Impl)
  //{
  //
  //}
  //
  //RenderTarget::~RenderTarget()
  //{
  //  delete pImpl_;
  //  pImpl_ = nullptr;
  //
  //  Restore();
  //}
  //
  //void RenderTarget::Set()
  //{
  //  detail::System::Get()->OMSetRenderTargets(pImpl_->pRenderTargetView_.GetAddressOf(), pImpl_->pDepthStencilView_.Get());
  //}
  //
  //void RenderTarget::Restore()
  //{
  //  detail::System::Get()->OMSetRenderTargets(nullptr, nullptr);
  //}
  //
  //void RenderTarget::Clear(const ColorF& _Color)
  //{
  //  //  クリア色
  //  const float ClearColor[4] = { _Color.R,_Color.G,_Color.B,_Color.A };
  //
  //  detail::System::Get()->GetDeviceContext()->ClearRenderTargetView(pImpl_->pRenderTargetView_.Get(), ClearColor);
  //  detail::System::Get()->GetDeviceContext()->ClearDepthStencilView(pImpl_->pDepthStencilView_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  //
  //  Set();
  //}
  //
  //void RenderTarget::CreateShaderResouceView()
  //{
  //  HRESULT hr = S_OK;
  //
  //  Microsoft::WRL::ComPtr<ID3D11Resource> pResource;
  //
  //  pImpl_->pRenderTargetView_->GetResource(pResource.GetAddressOf());
  //
  //  Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D;
  //  hr = pResource.Get()->QueryInterface<ID3D11Texture2D>(pTexture2D.GetAddressOf());
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"QueryInterface");
  //  D3D11_TEXTURE2D_DESC Texture2dDesc;
  //  pTexture2D->GetDesc(&Texture2dDesc);
  //
  //  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  //  ShaderResourceViewDesc.Format = Texture2dDesc.Format;
  //  DXGI_SWAP_CHAIN_DESC SwapChainDesc;
  //  detail::System::Get()->GetSwapChain()->GetDesc(&SwapChainDesc);
  //  ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
  //  ShaderResourceViewDesc.Texture2D.MipLevels = Texture2dDesc.MipLevels;
  //
  //  hr = detail::System::Get()->GetDevice()->CreateShaderResourceView(pTexture2D.Get(), &ShaderResourceViewDesc, pImpl_->pShaderResouceView_.ReleaseAndGetAddressOf());
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateShaderResourceView");
  //}
  //
  //ID3D11ShaderResourceView** RenderTarget::GetAddressOfShaderResourceView()const
  //{
  //  return pImpl_->pShaderResouceView_.GetAddressOf();
  //}
  //
  //void RenderTarget::Draw(const float2& _DstLeftTop, const float2& _DstSize, const float2& _SrcLeftPos, const float2& _SrcSize, const Degree& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const ColorF& _Color, const VertexShader* _pVertexShader, const PixelShader* _pPixelShader)
  //{
  //  HRESULT hr = S_OK;
  //
  //  //  頂点バッファオブジェクトを書き換え
  //  D3D11_MAPPED_SUBRESOURCE MappedSubresorce;
  //  hr = detail::System::Get()->GetDeviceContext()->Map(detail::System::Get()->GetSpriteManager()->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedSubresorce);
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"Map");
  //
  //  detail::Vertex2D v[4];
  //  //  画面座標設定
  //  {
  //    //  中心座標
  //    const float2 CenterPos{ _DstLeftTop + (_DstSize / 2.0f) };
  //    //  回転座標
  //    const float2 RotatePos[4] = {
  //      Math::RotateXY(_DstLeftTop, CenterPos, _Angle),
  //      Math::RotateXY(_DstLeftTop.X + _DstSize.X, _DstLeftTop.Y, CenterPos, _Angle),
  //      Math::RotateXY(_DstLeftTop.X, _DstLeftTop.Y + _DstSize.Y, CenterPos, _Angle),
  //      Math::RotateXY(_DstLeftTop + _DstSize, CenterPos, _Angle)
  //    };
  //
  //    for (int i = 0; i < 4; ++i)
  //    {
  //      v[i].Position.X = 2.0f * (RotatePos[i].X / System::GetWindowWidth()) - 1.0f;
  //      v[i].Position.Y = -2.0f * (RotatePos[i].Y / System::GetWindowHeight()) + 1.0f;
  //    }
  //  }
  //
  //  //  画像座標設定
  //  v[0].Texcoord.X = v[2].Texcoord.X = (!_HorizontalFlip) ? _SrcLeftPos.X / System::GetWindowWidth() : (_SrcLeftPos.X + _SrcSize.X) / System::GetWindowWidth();
  //  v[1].Texcoord.X = v[3].Texcoord.X = (!_HorizontalFlip) ? (_SrcLeftPos.X + _SrcSize.X) / System::GetWindowWidth() : _SrcLeftPos.X / System::GetWindowWidth();
  //  v[0].Texcoord.Y = v[1].Texcoord.Y = (!_VerticalFlip) ? _SrcLeftPos.Y / System::GetWindowHeight() : (_SrcLeftPos.Y + _SrcSize.Y) / System::GetWindowHeight();
  //  v[2].Texcoord.Y = v[3].Texcoord.Y = (!_VerticalFlip) ? (_SrcLeftPos.Y + _SrcSize.Y) / System::GetWindowHeight() : _SrcLeftPos.Y / System::GetWindowHeight();
  //
  //  //  最前面設定
  //  v[0].Position.Z = v[1].Position.Z = v[2].Position.Z = v[3].Position.Z = 0.0f;
  //
  //  //  色設定
  //  v[0].Color = v[1].Color = v[2].Color = v[3].Color = _Color;
  //
  //  detail::Vertex2D* Vertices = reinterpret_cast<detail::Vertex2D*>(MappedSubresorce.pData);
  //
  //  //  頂点情報をコピー
  //  memcpy(Vertices, v, sizeof(detail::Vertex2D) * 4);
  //
  //  //  頂点バッファオブジェクトを書き換え終了
  //  detail::System::Get()->GetDeviceContext()->Unmap(detail::System::Get()->GetSpriteManager()->GetVertexBuffer(), 0);
  //
  //  //  シェーダーリソースビューを設定
  //  detail::System::Get()->GetDeviceContext()->PSSetShaderResources(0, 1, pImpl_->pShaderResouceView_.GetAddressOf());
  //
  //  UINT Strides = sizeof(detail::Vertex2D);
  //  UINT Offsets = 0;
  //
  //  //detail::System::Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
  //  //detail::System::Get()->IASetVertexBuffers(detail::System::Get()->GetSpriteManager()->GetAddressOfVertexBuffer(), Strides, Offsets);
  //  //detail::System::Get()->IASetInputLayout(detail::System::Get()->GetVertexShader()->GetInputLayout((_pVertexShader) ? _pVertexShader->GetID() : detail::System::Get()->GetSpriteManager()->GetVertexShaderID()));
  //  //detail::System::Get()->VSSetShader(detail::System::Get()->GetVertexShader()->GetVertexShader((_pVertexShader) ? _pVertexShader->GetID() : detail::System::Get()->GetSpriteManager()->GetVertexShaderID()));
  //  //detail::System::Get()->PSSetShader(detail::System::Get()->GetPixelShader()->GetPixeShader((_pVertexShader) ? _pVertexShader->GetID() : detail::System::Get()->GetSpriteManager()->GetPixelShaderID()));
  //  //detail::System::Get()->PSSetSamplers(detail::System::Get()->GetSpriteManager()->GetAddressOfSamplerState());
  //  //detail::System::Get()->RSSetState(detail::System::Get()->GetSpriteManager()->GetRasterizerState());
  //  //detail::System::Get()->OMSetDepthStencilState(detail::System::Get()->GetSpriteManager()->GetDepthStencilState());
  //  //
  //  ////  描画
  //  //detail::System::Get()->GetDeviceContext()->Draw(4, 0);
  //}
}
