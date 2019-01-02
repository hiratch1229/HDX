#pragma once
#include "Texture.hpp"
#include "Types.hpp"

namespace hdx
{
  class RenderTarget : public hdx::Texture
  {
  public:
    RenderTarget();
    RenderTarget(const int2& _Size);
    RenderTarget(UINT _Width, UINT _Height);
  public:
    void Clear(const ColorF& _Color = hdx::ColorF(hdx::Palette::Black, 0.0f));
  };
}
