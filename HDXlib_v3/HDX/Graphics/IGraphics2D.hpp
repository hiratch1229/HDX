#pragma once

namespace hdx
{
  class VertexShader;
  class PixelShader;
  class BlendState;
}

namespace detail
{
  class IGraphics2D
  {
    struct Impl;
  private:
    Impl* pImpl_;
  public:
    void SetVertexShader(const hdx::VertexShader& _VertexShader);
    void SetPixelShader(const hdx::PixelShader& _PixelShader);
    void SetBlendState(const hdx::BlendState& _BlendState);
  public:
    const hdx::VertexShader& GetVertexShader()const;
    const hdx::PixelShader& GetPixelShader()const;
    const hdx::BlendState& GetBlendState()const;
  public:
    IGraphics2D();
    ~IGraphics2D();
  };
}
