#include "Include/Renderer3D.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Renderer/Renderer3D/IRenderer3D.hpp"
#include "Src/Misc.hpp"
#include "Src/Constants.hpp"

#include "Include/VertexShader.hpp"
#include "Include/BlendState.hpp"
#include "Include/SamplerState.hpp"
#include "Include/Texture.hpp"
#include "Include/RasterizerState.hpp"
#include "Include/DepthStencilState.hpp"

#include "Include/Constants.hpp"

#include <string>

//  ライブラリ
namespace hdx
{
  namespace Renderer3D
  {
    void SetVertexShader(const VertexShader& _VertexShader)
    {
      Engine::Get<IRenderer3D>()->SetVertexShader(_VertexShader);
    }

    void RestoreVertexShader()
    {
      Engine::Get<IRenderer3D>()->SetVertexShader(hdx::VertexShader(kDefault3DVertexShaderFilePath));
    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {
      Engine::Get<IRenderer3D>()->SetPixelShader(_PixelShader);
    }

    void RestorePixelShader()
    {
      Engine::Get<IRenderer3D>()->SetPixelShader(hdx::PixelShader(kDefault3DPixelShaderFilePath));
    }

    void SetBlendState(const BlendState& _BlendState)
    {
      Engine::Get<IRenderer3D>()->SetBlendState(_BlendState);
    }

    void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot)
    {
      _ASSERT_EXPR_A(_Slot >= 0 && _Slot < hdx::Constants::kSamplerStateMaxNum, ("0から" + std::to_string(hdx::Constants::kSamplerStateMaxNum - 1) + "の範囲を指定してください。").c_str());

      Engine::Get<IRenderer3D>()->SetSamplerState(_SamplerState, _Slot);
    }

    void SetRasterizerState(const RasterizerState& _RasterizerState)
    {
      Engine::Get<IRenderer3D>()->SetRasterizerState(_RasterizerState);
    }

    void SetDepthStencilState(const DepthStencilState& _DepthStencilState)
    {
      Engine::Get<IRenderer3D>()->SetDepthStencilState(_DepthStencilState);
    }

    void SetTexture(const Texture& _Texture, UINT _Slot)
    {
      _ASSERT_EXPR_A(_Slot >= 1 && _Slot < hdx::Constants::kTextureMaxNum, ("1から" + std::to_string(hdx::Constants::kTextureMaxNum - 1) + "の範囲を指定してください。").c_str());

      Engine::Get<IRenderer3D>()->SetTexture(_Texture, _Slot);
    }

    void RestoreRenderTarget()
    {
      Engine::Get<IRenderer3D>()->RestoreRenderTarget();
    }

    void SetRenderTarget(const RenderTarget& _RenderTarget)
    {
      Engine::Get<IRenderer3D>()->SetRenderTarget(_RenderTarget);
    }

    void SetConstantBuffer(ShaderStage _Stage, UINT _ID, const void* _pData, UINT _Slot)
    {
      _ASSERT_EXPR_A(_Slot >= 1 && _Slot < hdx::Constants::kConstantBufferMaxNum, ("1から" + std::to_string(hdx::Constants::kConstantBufferMaxNum - 1) + "の範囲を指定してください。").c_str());

      Engine::Get<IRenderer3D>()->SetConstantBuffer(_Stage, _ID, _pData, _Slot);
    }

    void SetCamera(const Camera& _Camera)
    {
      Engine::Get<IRenderer3D>()->SetCamera(_Camera);
    }

    void FreeCamera()
    {
      Engine::Get<IRenderer3D>()->FreeCamera();
    }

    Matrix GetProjectionMatrix()
    {
      return Engine::Get<IRenderer3D>()->GetProjectionMatrix();
    }

    Matrix GetViewMatrix()
    {
      return Engine::Get<IRenderer3D>()->GetViewMatrix();
    }

  }
}
