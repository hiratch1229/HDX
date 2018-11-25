#pragma once
#include "Types.hpp"
#include "Texture.hpp"
#include "VertexShader.hpp"
#include "PixelShader.hpp"
#include "BlendState.hpp"
#include "SamplerState.hpp"
#include "RasterizerState.hpp"
#include "RenderTarget.hpp"
#include "Camera.hpp"
#include "ConstantBuffer.hpp"

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
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
    void SetConstantBuffer(ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot);

    template<class T>
    void SetConstantBuffer(const ConstantBuffer<T>& ConstantBuffer, UINT _Slot, ShaderStage _Stage = ShaderStage::Vertex)
    {
      SetConstantBuffer(_Stage, ConstantBuffer.Size, ConstantBuffer.GetPtr(), _Slot);
    }
  };
}
