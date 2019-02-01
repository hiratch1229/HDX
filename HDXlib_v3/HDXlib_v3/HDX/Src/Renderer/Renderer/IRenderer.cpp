#include "IRenderer.hpp"

#include "CRenderer.hpp"

IRenderer* IRenderer::Get()
{
  static CRenderer Renderer;

  return &Renderer;
}
