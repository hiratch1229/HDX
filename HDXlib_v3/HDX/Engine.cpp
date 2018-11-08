#include <HDX/Engine.hpp>

#include <HDX/System/ISystem.hpp>
#include <HDX/Renderer/IRenderer2D.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/BlendState/IBlendState.hpp>
#include <HDX/SamplerState/ISamplerState.hpp>
#include <HDX/RasterizerState/IRasterizerState.hpp>
#include <HDX/DepthStencilState/IDepthStencilState.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>
#include <HDX/WIC.hpp>
#include <HDX/Texture/ITexture.hpp>
#include <HDX/Random/IRandom.hpp>

#include <crtdbg.h>

namespace detail
{
  Engine* Engine::pEngine = nullptr;

  Engine::Engine()
  {
    //  二度目以降作成時エラー
    _ASSERT_EXPR(!pEngine, L"Engineの二度目の作成です");
    
    //  作成時にデータを取り出せるようにする
    pEngine = this;
  }

  Engine::~Engine()
  {
    pSystem_.Release();
    pRenderer2D_.Release();
    pKeyboard_.Release();
    pMouse_.Release();
    pXInput_.Release();
    pGamepad_.Release();
    pBlendState_.Release();
    pSamplerState_.Release();
    pRasterizerState_.Release();
    pDepthStencilState_.Release();
    pVertexShader_.Release();
    pPixelShader_.Release();
    pWIC_.Release();
    pTexture_.Release();
    pRandom_.Release();
  }
}
