#pragma once
#include "Type3.hpp"
#include "Types.hpp"
#include "Texture.hpp"
#include "VertexShader.hpp"
#include "PixelShader.hpp"
#include "BlendState.hpp"
#include "SamplerState.hpp"
#include "RasterizerState.hpp"
#include "RenderTarget.hpp"
#include "DepthStencilState.hpp"
#include "Camera.hpp"
#include "ConstantBuffer.hpp"
#include "Matrix.hpp"

namespace hdx::Renderer3D
{
  void SetVertexShader(const VertexShader& _VertexShader);
  void RestoreVertexShader();
  void SetPixelShader(const PixelShader& _PixelShader);
  void RestorePixelShader();
  void SetBlendState(const BlendState& _BlendState);
  void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot);
  void SetRasterizerState(const RasterizerState& _RasterizerState);
  void SetDepthStencilState(const DepthStencilState& _DepthStencilState);
  void SetTexture(const Texture& _Texture, UINT _Slot);
  void RestoreRenderTarget();
  void SetRenderTarget(const RenderTarget& _RenderTarget);
  void SetCamera(const Camera& _Camera);
  void SetConstantBuffer(ShaderStage _Stage, UINT _ID, const void* _pData, UINT _Slot);

  template<class T>
  void SetConstantBuffer(const ConstantBuffer<T>& ConstantBuffer, UINT _Slot, ShaderStage _Stage = ShaderStage::Vertex)
  {
    SetConstantBuffer(_Stage, ConstantBuffer.GetID(), ConstantBuffer.GetPtr(), _Slot);
  }

  void FreeCamera();

  Matrix GetProjectionMatrix();
  Matrix GetViewMatrix();
}
