#pragma once
#include "../../../Include/Types.hpp"
#include "../../../Include/Matrix.hpp"

#include "../IRenderer.hpp"

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
  struct Camera;

  struct float2;
  class Radian;
  struct ColorF;
  class Model;
}

class IRenderer3D : public IRenderer
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
  void SetCamera(const hdx::Camera& _Camera);
public:
  void Draw(const hdx::Model& _Model, const hdx::Matrix& _WorldMatrix, const hdx::ColorF& _Color);
  void CalcProjection();
  void FreeCamera();
public:
  IRenderer3D();
};
