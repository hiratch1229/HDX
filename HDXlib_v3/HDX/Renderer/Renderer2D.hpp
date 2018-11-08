#pragma once
#include <HDX/Types.hpp>

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  class Texture;
  class VertexShader;
  class PixelShader;
  class BlendState;
  class SamplerState;
  class RasterizerState;
  class RenderTarget;

  namespace Renderer2D
  {
    void SetVertexShader(const VertexShader& _VertexShader);
    void RestoreVertexShader();
    void SetPixelShader(const PixelShader& _PixelShader);
    void RestorePixelShader();
    void SetBlendState(const BlendState& _BlendState);
    void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot);
    void SetRasterizerState(const RasterizerState& _RasterizerState);
    void SetTexture(const Texture& _Texture, UINT _Slot);
    void RestoreRenderTarget();
    void SetRenderTarget(const RenderTarget& _RenderTarget);
  };
}
