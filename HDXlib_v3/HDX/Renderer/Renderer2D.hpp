#pragma once

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
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
    void SetSamplerState(const SamplerState& _SamplerState);
    void SetRasterizerState(const RasterizerState& _RasterizerState);
    void RestoreRenderTarget();
    void SetRenderTarget(const RenderTarget& _RenderTarget);
  };
}
