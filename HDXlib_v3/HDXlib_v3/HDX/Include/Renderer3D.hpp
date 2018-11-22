#pragma once
#include "Types.hpp"

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
  struct Camera;

  namespace Renderer3D
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
    void SetCamera(const Camera& _Camera);
  };
}
