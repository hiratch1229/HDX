#include <HDX/Renderer/Renderer2D.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>
#include <HDX/Renderer/IRenderer2D.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>

#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/BlendState/BlendState.hpp>
#include <HDX/SamplerState/SamplerState.hpp>
#include <HDX/Texture/Texture.hpp>
#include <HDX/RasterizerState/RasterizerState.hpp>

#include <HDX/Constants.hpp>

#include <crtdbg.h>

//  ライブラリ
namespace hdx
{
  namespace Renderer2D
  {
    void SetVertexShader(const VertexShader& _VertexShader)
    {
      GetRenderer2D()->SetVertexShader(_VertexShader);
    }

    void RestoreVertexShader()
    {
      GetRenderer2D()->SetVertexShader(GetVertexShader()->CreateDefault2D());
    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {
      GetRenderer2D()->SetPixelShader(_PixelShader);
    }

    void RestorePixelShader()
    {
      GetRenderer2D()->SetPixelShader(GetPixelShader()->CreateDefault2D());
    }

    void SetBlendState(const BlendState& _BlendState)
    {
      GetRenderer2D()->SetBlendState(_BlendState);
    }

    void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot)
    {
      _ASSERT_EXPR(_Slot >= 0 && _Slot <= hdx::SamplerStateMaxNum, L"サンプラーステートのスロットは0～hdx::SamplerStateMaxNumを指定してください");

      GetRenderer2D()->SetSamplerState(_SamplerState, _Slot);
    }

    void SetRasterizerState(const RasterizerState& _RasterizerState)
    {
      GetRenderer2D()->SetRasterizerState(_RasterizerState);
    }

    void SetTexture(const Texture& _Texture, UINT _Slot)
    {
      _ASSERT_EXPR(_Slot >= 1 && _Slot <= hdx::TextureMaxNum, L"テクスチャのスロットは1～hdx::TextureMaxNumを指定してください");

      GetRenderer2D()->SetTexture(_Texture, _Slot);
    }

    void RestoreRenderTarget()
    {
      GetRenderer2D()->RestoreRenderTarget();
    }

    void SetRenderTarget(const RenderTarget& _RenderTarget)
    {
      GetRenderer2D()->SetRenderTarget(_RenderTarget);
    }
  }
}
