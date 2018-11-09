#pragma once

struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace hdx
{
  class RenderTarget;
  struct ColorF;
}

namespace detail
{
  class IRenderTarget
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    void CreateRenderTarget(const hdx::RenderTarget& _RenderTarget);
    ID3D11ShaderResourceView* GetShaderResourceView(const hdx::RenderTarget& _RenderTarget);
    void ClearRenderTarget(const hdx::RenderTarget& _RenderTarget, const hdx::ColorF& _Color);
    ID3D11RenderTargetView** GetRenderTargetView(const hdx::RenderTarget& _RenderTarget)const;
    ID3D11DepthStencilView* GetDepthStencilView(const hdx::RenderTarget& _RenderTarget)const;
  public:
    IRenderTarget();
    ~IRenderTarget();
  };
}
