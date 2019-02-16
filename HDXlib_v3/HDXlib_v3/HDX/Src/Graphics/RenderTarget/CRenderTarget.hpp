#pragma once
#include "IRenderTarget.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>

class CRenderTarget : public IRenderTarget
{
  struct State
  {
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  pDepthStencilView;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResouceView;
  };
private:
  ID3D11Device* pDevice_ = nullptr;
  ID3D11DeviceContext* pImmediateContext_ = nullptr;
  IDXGISwapChain* pSwapChain_ = nullptr;
  NumberMap<ID, State> StateMap_;
public:
  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, IDXGISwapChain* _pSwapChain)override;

  void CreateRenderTarget(const hdx::RenderTarget& _RenderTarget)override;

  void ClearRenderTarget(const hdx::RenderTarget& _RenderTarget, const hdx::ColorF& _Color)override;

  ID3D11ShaderResourceView* GetShaderResourceView(const hdx::RenderTarget& _RenderTarget)override;

  ID3D11RenderTargetView** GetRenderTargetView(const hdx::RenderTarget& _RenderTarget)override;

  ID3D11DepthStencilView* GetDepthStencilView(const hdx::RenderTarget& _RenderTarget)override;
};
