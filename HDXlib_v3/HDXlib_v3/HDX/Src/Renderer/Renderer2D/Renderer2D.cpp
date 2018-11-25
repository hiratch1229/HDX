#include "../../../Include/Renderer2D.hpp"

#include "../../Engine.hpp"
#include "../../System/ISystem.hpp"
#include "../../Renderer/Renderer2D/IRenderer2D.hpp"
#include "../../VertexShader/IVertexShader.hpp"
#include "../../PixelShader/IPixelShader.hpp"

#include "../../../Include/VertexShader.hpp"
#include "../../../Include/BlendState.hpp"
#include "../../../Include/SamplerState.hpp"
#include "../../../Include/Texture.hpp"
#include "../../../Include/RasterizerState.hpp"

#include "../../../Include/Constants.hpp"

#include <assert.h>

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  namespace Renderer2D
  {
    void SetVertexShader(const VertexShader& _VertexShader)
    {
      Engine::Get<IRenderer2D>()->SetVertexShader(_VertexShader);
    }

    void RestoreVertexShader()
    {
      Engine::Get<IRenderer2D>()->SetVertexShader(Engine::Get<IVertexShader>()->CreateDefault2D());
    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {
      Engine::Get<IRenderer2D>()->SetPixelShader(_PixelShader);
    }

    void RestorePixelShader()
    {
      Engine::Get<IRenderer2D>()->SetPixelShader(Engine::Get<IPixelShader>()->CreateDefault2D());
    }

    void SetBlendState(const BlendState& _BlendState)
    {
      Engine::Get<IRenderer2D>()->SetBlendState(_BlendState);
    }

    void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot)
    {
      assert(_Slot >= 0 && _Slot <= hdx::Constants::SamplerStateMaxNum);

      Engine::Get<IRenderer2D>()->SetSamplerState(_SamplerState, _Slot);
    }

    void SetRasterizerState(const RasterizerState& _RasterizerState)
    {
      Engine::Get<IRenderer2D>()->SetRasterizerState(_RasterizerState);
    }

    void SetTexture(const Texture& _Texture, UINT _Slot)
    {
      assert(_Slot >= 1 && _Slot <= hdx::Constants::TextureMaxNum);

      Engine::Get<IRenderer2D>()->SetTexture(_Texture, _Slot);
    }

    void RestoreRenderTarget()
    {
      Engine::Get<IRenderer2D>()->RestoreRenderTarget();
    }

    void SetRenderTarget(const RenderTarget& _RenderTarget)
    {
      Engine::Get<IRenderer2D>()->SetRenderTarget(_RenderTarget);
    }
  }
}
