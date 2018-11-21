#pragma once

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
  IRenderTarget() = default;
public:
  void Initialize();
};
