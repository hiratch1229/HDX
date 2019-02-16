#include "Include/Renderer2D.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Renderer/Renderer2D/IRenderer2D.hpp"
#include "Src/Misc.hpp"
#include "Src/Constants.hpp"

#include "Include/VertexShader.hpp"
#include "Include/BlendState.hpp"
#include "Include/SamplerState.hpp"
#include "Include/Texture.hpp"
#include "Include/RasterizerState.hpp"

#include "Include/Constants.hpp"

#include <string>

namespace hdx::Renderer2D
{
  void SetVertexShader(const VertexShader& _VertexShader)
  {
    Engine::Get<IRenderer2D>()->SetVertexShader(_VertexShader);
  }

  void RestoreVertexShader()
  {
    Engine::Get<IRenderer2D>()->SetVertexShader(hdx::VertexShader(kDefault2DVertexShaderFilePath));
  }

  void SetPixelShader(const PixelShader& _PixelShader)
  {
    Engine::Get<IRenderer2D>()->SetPixelShader(_PixelShader);
  }

  void RestorePixelShader()
  {
    Engine::Get<IRenderer2D>()->SetPixelShader(hdx::PixelShader(kDefault2DPixelShaderFilePath));
  }

  void SetBlendState(const BlendState& _BlendState)
  {
    Engine::Get<IRenderer2D>()->SetBlendState(_BlendState);
  }

  void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot)
  {
    _ASSERT_EXPR_A(_Slot >= 0 && _Slot < hdx::Constants::kSamplerStateMaxNum, ("0から" + std::to_string(hdx::Constants::kSamplerStateMaxNum - 1) + "の範囲を指定してください。").c_str());

    Engine::Get<IRenderer2D>()->SetSamplerState(_SamplerState, _Slot);
  }

  void SetRasterizerState(const RasterizerState& _RasterizerState)
  {
    Engine::Get<IRenderer2D>()->SetRasterizerState(_RasterizerState);
  }

  void SetTexture(const Texture& _Texture, UINT _Slot)
  {
    _ASSERT_EXPR_A(_Slot >= 1 && _Slot < hdx::Constants::kSamplerStateMaxNum, ("0から" + std::to_string(hdx::Constants::kTextureMaxNum - 1) + "の範囲を指定してください。").c_str());

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
