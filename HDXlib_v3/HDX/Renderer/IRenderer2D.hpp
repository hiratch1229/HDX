#pragma once

namespace hdx
{
  class VertexShader;
  class PixelShader;
  class BlendState;
  class SamplerState;
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
  public:
    const hdx::VertexShader& GetVertexShader()const;
    const hdx::PixelShader& GetPixelShader()const;
    const hdx::BlendState& GetBlendState()const;
    const hdx::SamplerState& GetSamplerState()const;
  public:
    IRenderer2D();
    ~IRenderer2D();
  };
}
