#include <HDX/Graphics/Graphics2D.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>
#include <HDX/BlendState/IBlendState.hpp>

#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/PixelShader/PixelShader.hpp>
#include <HDX/BlendState/BlendState.hpp>

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  namespace Graphics2D
  {
    void SetVertexShader(const VertexShader& _VertexShader)
    {

    }
    void RestoreVertexShader()
    {

    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {

    }
    void RestorePixelShader()
    {

    }

    void SetBlendState(const BlendState& _BlendState)
    {
      detail::Engine::GetSystem()->SetBlendState(detail::Engine::GetBlendState()->GetBlendState(_BlendState));
    }
  }
}
