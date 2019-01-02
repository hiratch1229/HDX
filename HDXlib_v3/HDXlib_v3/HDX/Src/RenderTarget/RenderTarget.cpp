#include "Include/RenderTarget.hpp"

#include "Src/Engine.hpp"
#include "Src/RenderTarget/IRenderTarget.hpp"

namespace hdx
{
  inline void CreateRenderTarget(const RenderTarget& _RenderTarget)
  {
    Engine::Get<IRenderTarget>()->CreateRenderTarget(_RenderTarget);
  }

  RenderTarget::RenderTarget()
  {
    Size_ = hdx::int2();
  }

  RenderTarget::RenderTarget(const int2& _Size)
    : Texture(_Size)
  {
    CreateRenderTarget(*this);
  }

  RenderTarget::RenderTarget(UINT _Width, UINT _Height)
    : Texture({ static_cast<int>(_Width), static_cast<int>(_Height) })
  {
    CreateRenderTarget(*this);
  }

  void RenderTarget::Clear(const ColorF& _Color)
  {
    Engine::Get<IRenderTarget>()->ClearRenderTarget(*this, _Color);
  }
}
