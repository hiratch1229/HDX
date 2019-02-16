#include "CRenderTarget.hpp"

#include "Src/Misc.hpp"

void CRenderTarget::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, IDXGISwapChain* _pSwapChain)
{
  pDevice_ = _pDevice;
  pImmediateContext_ = _pImmediateContext;
  pSwapChain_ = _pSwapChain;
}

void CRenderTarget::CreateRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  HRESULT hr = S_OK;

  State State;

  Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
  hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  D3D11_TEXTURE2D_DESC RenderTargetDesc;
  {
    pBackBuffer->GetDesc(&RenderTargetDesc);
    RenderTargetDesc.Width = _RenderTarget.GetWidth();
    RenderTargetDesc.Height = _RenderTarget.GetHeight();
    RenderTargetDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
  }

  Microsoft::WRL::ComPtr<ID3D11Texture2D> pRenderTarget;
  hr = pDevice_->CreateTexture2D(&RenderTargetDesc, nullptr, pRenderTarget.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  hr = pDevice_->CreateRenderTargetView(pRenderTarget.Get(), nullptr, State.pRenderTargetView.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

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

    hr = pDevice_->CreateTexture2D(&DepthStencilBufferDesc, nullptr, DepthStencilBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    pSwapChain_->GetDesc(&SwapChainDesc);

    D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
    {
      DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
      DepthStencilViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
      DepthStencilViewDesc.Flags = 0;
      DepthStencilViewDesc.Texture2D.MipSlice = 0;
    }

    hr = pDevice_->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, State.pDepthStencilView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  StateMap_.insert({ _RenderTarget.GetID() }, State);
}

ID3D11ShaderResourceView* CRenderTarget::GetShaderResourceView(const hdx::RenderTarget& _RenderTarget)
{
  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<ID3D11Resource> pResource;

  State& State = StateMap_[ID(_RenderTarget.GetID())];

  State.pRenderTargetView->GetResource(pResource.GetAddressOf());

  Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D;
  hr = pResource.Get()->QueryInterface<ID3D11Texture2D>(pTexture2D.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  D3D11_TEXTURE2D_DESC Texture2dDesc;
  pTexture2D->GetDesc(&Texture2dDesc);

  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  ShaderResourceViewDesc.Format = Texture2dDesc.Format;

  DXGI_SWAP_CHAIN_DESC SwapChainDesc;
  pSwapChain_->GetDesc(&SwapChainDesc);
  ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
  ShaderResourceViewDesc.Texture2D.MipLevels = Texture2dDesc.MipLevels;

  hr = pDevice_->CreateShaderResourceView(pTexture2D.Get(), &ShaderResourceViewDesc, State.pShaderResouceView.ReleaseAndGetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return State.pShaderResouceView.Get();
}

void CRenderTarget::ClearRenderTarget(const hdx::RenderTarget& _RenderTarget, const hdx::ColorF& _Color)
{
  State& State = StateMap_[ID(_RenderTarget.GetID())];

  //  クリア色
  const float ClearColor[4] = { _Color.R,_Color.G,_Color.B,_Color.A };

  pImmediateContext_->ClearRenderTargetView(State.pRenderTargetView.Get(), ClearColor);
  pImmediateContext_->ClearDepthStencilView(State.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11RenderTargetView** CRenderTarget::GetRenderTargetView(const hdx::RenderTarget& _RenderTarget)
{
  return (_RenderTarget.GetSize() == hdx::int2()) ? nullptr : StateMap_[ID(_RenderTarget.GetID())].pRenderTargetView.GetAddressOf();
}

ID3D11DepthStencilView* CRenderTarget::GetDepthStencilView(const hdx::RenderTarget& _RenderTarget)
{
  return (_RenderTarget.GetSize() == hdx::int2()) ? nullptr : StateMap_[ID(_RenderTarget.GetID())].pDepthStencilView.Get();
}
