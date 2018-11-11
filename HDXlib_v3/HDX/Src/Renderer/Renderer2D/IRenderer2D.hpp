#pragma once
#include "../../../Include/Types.hpp"

namespace hdx
{
  class VertexShader;
  class PixelShader;
  class BlendState;
  class SamplerState;
  class RasterizerState;
  class DepthStencilState;
  class Texture;
  class RenderTarget;
}

namespace detail
{
  class IRenderer2D
  {
    struct Impl;
  private:
    Impl* pImpl_;
  public:
    void SetVertexShader(const hdx::VertexShader& _VertexShader);
    void SetPixelShader(const hdx::PixelShader& _PixelShader);
    void SetBlendState(const hdx::BlendState& _BlendState);
    void SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot);
    void SetRasterizerState(const hdx::RasterizerState& _RasterizerState);
    void SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState);
    void SetTexture(const hdx::Texture& _Texture, UINT _Slot);
    void RestoreRenderTarget();
    void SetRenderTarget(const hdx::RenderTarget& _RenderTarger);
  public:
    const hdx::VertexShader& GetVertexShader()const;
    const hdx::PixelShader& GetPixelShader()const;
    const hdx::BlendState& GetBlendState()const;
    const hdx::SamplerState& GetSamplerState(UINT _Slot)const;
    const hdx::RasterizerState& GetRasterizerState()const;
    const hdx::DepthStencilState& GetDepthStencilState()const;
    const hdx::Texture& GetTexture(UINT _Slot)const;
    const hdx::RenderTarget& GetRenderTarget()const;
  public:
    IRenderer2D();
    ~IRenderer2D();
  };
}
