#pragma once
#include "Types.hpp"
#include "Texture.hpp"
#include "VertexShader.hpp"
#include "PixelShader.hpp"
#include "BlendState.hpp"
#include "SamplerState.hpp"
#include "RasterizerState.hpp"
#include "RenderTarget.hpp"
#include "DepthStencilState.hpp"

namespace hdx::Renderer2D
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
}
