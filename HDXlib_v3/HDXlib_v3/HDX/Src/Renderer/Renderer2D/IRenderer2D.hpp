#pragma once
#include "../../../Include/Types.hpp"

#include "../Renderer.hpp"

namespace hdx
{
  class VertexShader;
  class PixelShader;
  class BlendState;
  class SamplerState;
  class RasterizerState;
  class DepthStencilState;
  class Texture;
  class RenderTarget;

  struct float2;
  class Radian;
  struct ColorF;
}

class IRenderer2D : public IRenderer
{
public:
  void SetVertexShader(const hdx::VertexShader& _VertexShader);
  void SetPixelShader(const hdx::PixelShader& _PixelShader);
  void SetBlendState(const hdx::BlendState& _BlendState);
  void SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot);
  void SetRasterizerState(const hdx::RasterizerState& _RasterizerState);
  void SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState);
  void SetTexture(const hdx::Texture& _Texture, UINT _Slot);
  void RestoreRenderTarget();
  void SetRenderTarget(const hdx::RenderTarget& _RenderTarger);
public:
  void Begin(const hdx::Texture& _Texture);
  void End();
  void Draw(const hdx::Texture& _Texture, const hdx::float2& _DstLeftTop, const hdx::float2& _DstSize, const hdx::float2& _SrcLeftPos, const hdx::float2& _SrcSize, const hdx::Radian& _Angle, bool _HorizontalFlip, bool _VerticalFlip, const hdx::ColorF& _Color);
public:
  IRenderer2D();
};