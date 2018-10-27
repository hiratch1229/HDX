#pragma once

namespace hdx
{
  class VertexShader;
  class PixelShader;
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
  public:
    IGraphics2D();
    ~IGraphics2D();
  };
}
