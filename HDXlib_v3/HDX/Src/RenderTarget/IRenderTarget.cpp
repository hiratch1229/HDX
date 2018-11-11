#include "IRenderTarget.hpp"

#include "../Engine/Engine.hpp"
#include "../System/ISystem.hpp"

#include "../NumberMap.hpp"

#include "../../Include/RenderTarget.hpp"

#include <d3d11.h>
#include <wrl.h>

struct ID
{
  int Value;
  ID(int _Value) : Value(_Value) { }
};

bool operator==(const ID& _ID1, const ID& _ID2)
{
  return _ID1.Value == _ID2.Value;
}

template<>
struct std::hash<ID>
{
  size_t operator()(const ID& _ID)const
  {
    return _ID.Value;
  }
};

namespace detail
{
  class IRenderTarget::Impl
  {
  public:
    struct State
    {
      Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
      Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  pDepthStencilView;
    };
  public:
    NumberMap<ID, State> StateMap_;
  public:
    Impl() { StateMap_.clear(); }
    ~Impl() { StateMap_.clear(); }
  };

  IRenderTarget::IRenderTarget()
    : pImpl_(new Impl)
  {

  }

  IRenderTarget::~IRenderTarget()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  void IRenderTarget::CreateRenderTarget(const hdx::RenderTarget& _RenderTarget)
  {
    HRESULT hr = S_OK;

    Impl::State State;

    ISystem* pSystem = GetSystem();

    Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
    hr = pSystem->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
    _ASSERT_EXPR(SUCCEEDED(hr), L"GetBuffer");

    D3D11_TEXTURE2D_DESC RenderTargetDesc;
    pBackBuffer->GetDesc(&RenderTargetDesc);
    RenderTargetDesc.Width = _RenderTarget.GetWidth();
    RenderTargetDesc.Height = _RenderTarget.GetHeight();
    RenderTargetDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> pRenderTarget;
    hr = pSystem->GetDevice()->CreateTexture2D(&RenderTargetDesc, nullptr, pRenderTarget.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");

    hr = pSystem->GetDevice()->CreateRenderTargetView(pRenderTarget.Get(), nullptr, State.pRenderTargetView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRenderTargetView");

    //  深度ステンシルビューの作成
    {
      D3D11_TEXTURE2D_DESC DepthStencilBufferDesc = RenderTargetDesc;
      Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthStencilBuffer;
      DepthStencilBufferDesc.MipLevels = 1;
      DepthStencilBufferDesc.ArraySize = 1;
      DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
      DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
      DepthStencilBufferDesc.CPUAccessFlags = 0;
      DepthStencilBufferDesc.MiscFlags = 0;

      hr = pSystem->GetDevice()->CreateTexture2D(&DepthStencilBufferDesc, nullptr, DepthStencilBuffer.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");

      DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
      pSystem->GetSwapChain()->GetDesc(&SwapChainDesc);

      D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
      DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
      DepthStencilViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
      DepthStencilViewDesc.Flags = 0;
      DepthStencilViewDesc.Texture2D.MipSlice = 0;

      hr = pSystem->GetDevice()->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, State.pDepthStencilView.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilView");
    }

    pImpl_->StateMap_.insert({ _RenderTarget.GetID() }, State);
  }

  ID3D11ShaderResourceView* IRenderTarget::GetShaderResourceView(const hdx::RenderTarget& _RenderTarget)
  {
    HRESULT hr = S_OK;

    ISystem* pSystem = GetSystem();

    Microsoft::WRL::ComPtr<ID3D11Resource> pResource;

    Impl::State& State = pImpl_->StateMap_[ID(_RenderTarget.GetID())];

    State.pRenderTargetView->GetResource(pResource.GetAddressOf());

    Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D;
    hr = pResource.Get()->QueryInterface<ID3D11Texture2D>(pTexture2D.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"QueryInterface");
    D3D11_TEXTURE2D_DESC Texture2dDesc;
    pTexture2D->GetDesc(&Texture2dDesc);

    D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
    ShaderResourceViewDesc.Format = Texture2dDesc.Format;
    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    pSystem->GetSwapChain()->GetDesc(&SwapChainDesc);
    ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
    ShaderResourceViewDesc.Texture2D.MipLevels = Texture2dDesc.MipLevels;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
    hr = pSystem->GetDevice()->CreateShaderResourceView(pTexture2D.Get(), &ShaderResourceViewDesc, ShaderResourceView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateShaderResourceView");

    return ShaderResourceView.Get();
  }

  void IRenderTarget::ClearRenderTarget(const hdx::RenderTarget& _RenderTarget, const hdx::ColorF& _Color)
  {
    ISystem* pSystem = GetSystem();

    Impl::State& State = pImpl_->StateMap_[ID(_RenderTarget.GetID())];

    //  クリア色
    const float ClearColor[4] = { _Color.R,_Color.G,_Color.B,_Color.A };

    pSystem->GetImmediateContext()->ClearRenderTargetView(State.pRenderTargetView.Get(), ClearColor);
    pSystem->GetImmediateContext()->ClearDepthStencilView(State.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  }

  ID3D11RenderTargetView** IRenderTarget::GetRenderTargetView(const hdx::RenderTarget& _RenderTarget)const
  {
    return (_RenderTarget.GetSize() == hdx::int2()) ? nullptr : pImpl_->StateMap_[ID(_RenderTarget.GetID())].pRenderTargetView.GetAddressOf();
  }

  ID3D11DepthStencilView* IRenderTarget::GetDepthStencilView(const hdx::RenderTarget& _RenderTarget)const
  {
    return (_RenderTarget.GetSize() == hdx::int2()) ? nullptr : pImpl_->StateMap_[ID(_RenderTarget.GetID())].pDepthStencilView.Get();
  }
}
