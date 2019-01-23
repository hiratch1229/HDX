#include "IRenderTarget.hpp"

#include "CRenderTarget.hpp"

IRenderTarget* IRenderTarget::Create()
{
  return new CRenderTarget;
}
