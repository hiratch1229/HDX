#pragma once

namespace hdx
{
  class VertexShader;
  class PixelShader;
  class BlendState;
  class SamplerState;
  class RasterizerState;
  class DepthStencilState;
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
    void SetSamplerState(const hdx::SamplerState& _SamplerState);
    void SetRasterizerState(const hdx::RasterizerState& _RasterizerState);
    void SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState);
  public:
    const hdx::VertexShader& GetVertexShader()const;
    const hdx::PixelShader& GetPixelShader()const;
    const hdx::BlendState& GetBlendState()const;
    const hdx::SamplerState& GetSamplerState()const;
    const hdx::RasterizerState& GetRasterizerState()const;
    const hdx::DepthStencilState& GetDepthStencilState()const;
  public:
    IRenderer2D();
    ~IRenderer2D();
  };
}
