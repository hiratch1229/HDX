#include <HDX/Renderer/Renderer2D.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Renderer/IRenderer2D.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>
//#include <HDX/System/ISystem.hpp>
//#include <HDX/BlendState/IBlendState.hpp>

#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/BlendState/BlendState.hpp>
#include <HDX/SamplerState/SamplerState.hpp>

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  namespace Renderer2D
  {
    void SetVertexShader(const VertexShader& _VertexShader)
    {
      detail::Engine::GetRenderer2D()->SetVertexShader(_VertexShader);
    }

    void RestoreVertexShader()
    {
      detail::Engine::GetRenderer2D()->SetVertexShader(detail::Engine::GetVertexShader()->CreateDefault2D());
    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {
      detail::Engine::GetRenderer2D()->SetPixelShader(_PixelShader);
    }

    void RestorePixelShader()
    {
      detail::Engine::GetRenderer2D()->SetPixelShader(detail::Engine::GetPixelShader()->CreateDefault2D());
    }

    void SetBlendState(const BlendState& _BlendState)
    {
      detail::Engine::GetRenderer2D()->SetBlendState(_BlendState);
    }

    void SetSamplerState(const SamplerState& _SamplerState)
    {
      detail::Engine::GetRenderer2D()->SetSamplerState(_SamplerState);
    }
  }
}
