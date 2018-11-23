#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace hdx
{
  class RenderTarget;
  struct ColorF;
}

class IRenderTarget
{
public:
  void CreateRenderTarget(const hdx::RenderTarget& _RenderTarget);
  void ClearRenderTarget(const hdx::RenderTarget& _RenderTarget, const hdx::ColorF& _Color);
public:
  ID3D11ShaderResourceView* GetShaderResourceView(const hdx::RenderTarget& _RenderTarget);
  ID3D11RenderTargetView** GetRenderTargetView(const hdx::RenderTarget& _RenderTarget)const;
  ID3D11DepthStencilView* GetDepthStencilView(const hdx::RenderTarget& _RenderTarget)const;
public:
  void Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, IDXGISwapChain* _pSwapChain);
};
