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

#include <crtdbg.h>

//  ライブラリ
namespace hdx
{
  namespace Renderer2D
  {
    void SetVertexShader(const VertexShader& _VertexShader)
    {
      Engine::GetRenderer2D()->SetVertexShader(_VertexShader);
    }

    void RestoreVertexShader()
    {
      Engine::GetRenderer2D()->SetVertexShader(Engine::GetVertexShader()->CreateDefault2D());
    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {
      Engine::GetRenderer2D()->SetPixelShader(_PixelShader);
    }

    void RestorePixelShader()
    {
      Engine::GetRenderer2D()->SetPixelShader(Engine::GetPixelShader()->CreateDefault2D());
    }

    void SetBlendState(const BlendState& _BlendState)
    {
      Engine::GetRenderer2D()->SetBlendState(_BlendState);
    }

    void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot)
    {
      _ASSERT_EXPR(_Slot >= 0 && _Slot <= hdx::SamplerStateMaxNum, L"サンプラーステートのスロットは0～hdx::SamplerStateMaxNumを指定してください");

      Engine::GetRenderer2D()->SetSamplerState(_SamplerState, _Slot);
    }

    void SetRasterizerState(const RasterizerState& _RasterizerState)
    {
      Engine::GetRenderer2D()->SetRasterizerState(_RasterizerState);
    }

    void SetTexture(const Texture& _Texture, UINT _Slot)
    {
      _ASSERT_EXPR(_Slot >= 1 && _Slot <= hdx::TextureMaxNum, L"テクスチャのスロットは1～hdx::TextureMaxNumを指定してください");

      Engine::GetRenderer2D()->SetTexture(_Texture, _Slot);
    }

    void RestoreRenderTarget()
    {
      Engine::GetRenderer2D()->RestoreRenderTarget();
    }

    void SetRenderTarget(const RenderTarget& _RenderTarget)
    {
      Engine::GetRenderer2D()->SetRenderTarget(_RenderTarget);
    }
  }
}
