#pragma once
#include "Include/BlendState.hpp"
#include "Include/ConstantBuffer.hpp"
#include "Include/DepthStencilState.hpp"
#include "Include/RasterizerState.hpp"
#include "Include/RenderTarget.hpp"
#include "Include/SamplerState.hpp"
#include "Include/VertexShader.hpp"
#include "Include/PixelShader.hpp"

#include "Include/Model.hpp"
#include "Include/Camera.hpp"

#include <d3d11.h>

class IRenderer3D
{
public:
  static IRenderer3D* Create();

  IRenderer3D() = default;

  virtual ~IRenderer3D() = default;

  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual void Draw(const hdx::Model& _Model, const hdx::Matrix& _WorldMatrix, const hdx::MotionData& _MotionData, const hdx::ColorF& _Color) = 0;

  virtual void Flush() = 0;

  virtual void SetBlendState(const hdx::BlendState& _BlendState) = 0;

  virtual void SetConstantBuffer(hdx::ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot) = 0;

  virtual void SetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState) = 0;

  virtual void SetRasterizerState(const hdx::RasterizerState& _RasterizerState) = 0;

  virtual void SetRenderTarget(const hdx::RenderTarget& _RenderTarget) = 0;

  virtual void SetSamplerState(const hdx::SamplerState& _SamplerState, UINT _Slot) = 0;

  virtual void SetTexture(const hdx::Texture& _Texture, UINT _Slot) = 0;

  virtual void SetVertexShader(const hdx::VertexShader& _VertexShader) = 0;

  virtual void SetPixelShader(const hdx::PixelShader& _PixelShader) = 0;

  virtual void RestoreRenderTarget() = 0;

  virtual void SetLightDirection(const hdx::float3& _LightDirection) = 0;

  virtual void SetCamera(const hdx::Camera& _Camera) = 0;

  virtual void CalcProjection() = 0;

  virtual void FreeCamera() = 0;

  virtual hdx::Matrix GetProjectionMatrix()const = 0;

  virtual hdx::Matrix GetViewMatrix()const = 0;
};
