#include <HDX/Graphics/Graphics2D.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Graphics/IGraphics2D.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>
//#include <HDX/System/ISystem.hpp>
//#include <HDX/BlendState/IBlendState.hpp>

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
      detail::Engine::GetGraphics2D()->SetVertexShader(_VertexShader);
    }

    void RestoreVertexShader()
    {
      detail::Engine::GetGraphics2D()->SetVertexShader(detail::Engine::GetVertexShader()->CreateDefault2D());
    }

    void SetPixelShader(const PixelShader& _PixelShader)
    {
      detail::Engine::GetGraphics2D()->SetPixelShader(_PixelShader);
    }

    void RestorePixelShader()
    {
      detail::Engine::GetGraphics2D()->SetPixelShader(detail::Engine::GetPixelShader()->CreateDefault2D());
    }

    void SetBlendState(const BlendState& _BlendState)
    {
      detail::Engine::GetGraphics2D()->SetBlendState(_BlendState);
    }
  }
}
