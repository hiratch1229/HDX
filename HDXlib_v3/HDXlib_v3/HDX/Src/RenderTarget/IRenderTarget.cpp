#include "IRenderTarget.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../Misc.hpp"

#include "../NumberMap.hpp"

#include "../../Include/RenderTarget.hpp"

#include <d3d11.h>
#include <wrl.h>

namespace
{
  struct State
  {
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  pDepthStencilView;
  };

  NumberMap<ID, State> StateMap;
  ID3D11Device* pDevice = nullptr;
  ID3D11DeviceContext* pImmediateContext = nullptr;
  IDXGISwapChain* pSwapChain = nullptr;
}

void IRenderTarget::Initialize()
{
  pDevice = Engine::Get<ISystem>()->GetDevice();
  pImmediateContext = Engine::Get<ISystem>()->GetImmediateContext();
  pSwapChain = Engine::Get<ISystem>()->GetSwapChain();
}

void IRenderTarget::CreateRenderTarget(const hdx::RenderTarget& _RenderTarget)
{
  HRESULT hr = S_OK;

  State State;

  Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
  hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  D3D11_TEXTURE2D_DESC RenderTargetDesc;
  {
    pBackBuffer->GetDesc(&RenderTargetDesc);
    RenderTargetDesc.Width = _RenderTarget.GetWidth();
    RenderTargetDesc.Height = _RenderTarget.GetHeight();
    RenderTargetDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
  }

  Microsoft::WRL::ComPtr<ID3D11Texture2D> pRenderTarget;
  hr = pDevice->CreateTexture2D(&RenderTargetDesc, nullptr, pRenderTarget.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  hr = pDevice->CreateRenderTargetView(pRenderTarget.Get(), nullptr, State.pRenderTargetView.GetAddressOf());
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

    hr = pDevice->CreateTexture2D(&DepthStencilBufferDesc, nullptr, DepthStencilBuffer.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    pSwapChain->GetDesc(&SwapChainDesc);

    D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
    {
      DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
      DepthStencilViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
      DepthStencilViewDesc.Flags = 0;
      DepthStencilViewDesc.Texture2D.MipSlice = 0;
    }

    hr = pDevice->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, State.pDepthStencilView.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  StateMap.insert({ _RenderTarget.GetID() }, State);
}

ID3D11ShaderResourceView* IRenderTarget::GetShaderResourceView(const hdx::RenderTarget& _RenderTarget)
{
  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<ID3D11Resource> pResource;

  State& State = StateMap[ID(_RenderTarget.GetID())];

  State.pRenderTargetView->GetResource(pResource.GetAddressOf());

  Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D;
  hr = pResource.Get()->QueryInterface<ID3D11Texture2D>(pTexture2D.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  D3D11_TEXTURE2D_DESC Texture2dDesc;
  pTexture2D->GetDesc(&Texture2dDesc);

  D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
  ShaderResourceViewDesc.Format = Texture2dDesc.Format;
  DXGI_SWAP_CHAIN_DESC SwapChainDesc;
  pSwapChain->GetDesc(&SwapChainDesc);
  ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
  ShaderResourceViewDesc.Texture2D.MipLevels = Texture2dDesc.MipLevels;

  Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceView;
  hr = pDevice->CreateShaderResourceView(pTexture2D.Get(), &ShaderResourceViewDesc, ShaderResourceView.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return ShaderResourceView.Get();
}

void IRenderTarget::ClearRenderTarget(const hdx::RenderTarget& _RenderTarget, const hdx::ColorF& _Color)
{
  State& State = StateMap[ID(_RenderTarget.GetID())];

  //  クリア色
  const float ClearColor[4] = { _Color.R,_Color.G,_Color.B,_Color.A };

  pImmediateContext->ClearRenderTargetView(State.pRenderTargetView.Get(), ClearColor);
  pImmediateContext->ClearDepthStencilView(State.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

ID3D11RenderTargetView** IRenderTarget::GetRenderTargetView(const hdx::RenderTarget& _RenderTarget)const
{
  return (_RenderTarget.GetSize() == hdx::int2()) ? nullptr : StateMap[ID(_RenderTarget.GetID())].pRenderTargetView.GetAddressOf();
}

ID3D11DepthStencilView* IRenderTarget::GetDepthStencilView(const hdx::RenderTarget& _RenderTarget)const
{
  return (_RenderTarget.GetSize() == hdx::int2()) ? nullptr : StateMap[ID(_RenderTarget.GetID())].pDepthStencilView.Get();
}
