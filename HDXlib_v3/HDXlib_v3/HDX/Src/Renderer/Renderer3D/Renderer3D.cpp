#include "../../../Include/Renderer3D.hpp"

#include "../../Engine.hpp"
#include "../../System/ISystem.hpp"
#include "../../Renderer/Renderer3D/IRenderer3D.hpp"
#include "../../VertexShader/IVertexShader.hpp"
#include "../../PixelShader/IPixelShader.hpp"

#include "../../../Include/VertexShader.hpp"
#include "../../../Include/BlendState.hpp"
#include "../../../Include/SamplerState.hpp"
#include "../../../Include/Texture.hpp"
#include "../../../Include/RasterizerState.hpp"

#include "../../../Include/Constants.hpp"

#include <assert.h>

//  ƒ‰ƒCƒuƒ‰ƒŠ
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
      Engine::Get<IRenderer3D>()->SetVertexShader(Engine::Get<IVertexShader>()->CreateDefault3D());
    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {
      Engine::Get<IRenderer3D>()->SetPixelShader(_PixelShader);
    }

    void RestorePixelShader()
    {
      Engine::Get<IRenderer3D>()->SetPixelShader(Engine::Get<IPixelShader>()->CreateDefault3D());
    }

    void SetBlendState(const BlendState& _BlendState)
    {
      Engine::Get<IRenderer3D>()->SetBlendState(_BlendState);
    }

    void SetSamplerState(const SamplerState& _SamplerState, UINT _Slot)
    {
      assert(_Slot >= 0 && _Slot <= hdx::Constants::SamplerStateMaxNum);

      Engine::Get<IRenderer3D>()->SetSamplerState(_SamplerState, _Slot);
    }

    void SetRasterizerState(const RasterizerState& _RasterizerState)
    {
      Engine::Get<IRenderer3D>()->SetRasterizerState(_RasterizerState);
    }

    void SetTexture(const Texture& _Texture, UINT _Slot)
    {
      assert(_Slot >= 1 && _Slot <= hdx::Constants::TextureMaxNum);

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

    void SetConstantBuffer(ShaderStage _Stage, UINT _Size, const void* _pData, UINT _Slot)
    {
      assert(_Slot >= 1 && _Slot <= hdx::Constants::ConstantBufferMaxNum);

      Engine::Get<IRenderer3D>()->SetConstantBuffer(_Stage, _Size, _pData, _Slot);
    }

    void SetCamera(const Camera& _Camera)
    {
      Engine::Get<IRenderer3D>()->SetCamera(_Camera);
    }
  }
}
