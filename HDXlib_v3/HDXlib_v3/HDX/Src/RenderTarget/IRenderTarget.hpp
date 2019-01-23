#pragma once
#include <d3d11.h>

#include "Include/RenderTarget.hpp"

class IRenderTarget
{
public:
  static IRenderTarget* Create();

  IRenderTarget() = default;

  virtual ~IRenderTarget() = default;

  virtual void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, IDXGISwapChain* _pSwapChain) = 0;

  virtual void CreateRenderTarget(const hdx::RenderTarget& _RenderTarget) = 0;

  virtual void ClearRenderTarget(const hdx::RenderTarget& _RenderTarget, const hdx::ColorF& _Color) = 0;

  virtual ID3D11ShaderResourceView* GetShaderResourceView(const hdx::RenderTarget& _RenderTarget) = 0;

  virtual ID3D11RenderTargetView** GetRenderTargetView(const hdx::RenderTarget& _RenderTarget) = 0;

  virtual ID3D11DepthStencilView* GetDepthStencilView(const hdx::RenderTarget& _RenderTarget) = 0;
};
