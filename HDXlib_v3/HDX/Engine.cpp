#include <HDX/Engine.hpp>

#include <HDX/System/ISystem.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>
#include <HDX/WIC.hpp>
#include <HDX/Sprite/ISprite.hpp>
#include <HDX/Random/IRandom.hpp>

#include <assert.h>

namespace detail
{
  Engine* Engine::pEngine = nullptr;

  Engine::Engine()
  {
    //  二度目以降作成時エラー
    assert(!pEngine);

    //  作成時にデータを取り出せるようにする
    pEngine = this;
  }

  Engine::~Engine()
  {
    pSystem_.Release();
    pKeyboard_.Release();
    pMouse_.Release();
    pXInput_.Release();
    pGamepad_.Release();
    pVertexShader_.Release();
    pPixelShader_.Release();
    pWIC_.Release();
    pSprite_.Release();
    pRandom_.Release();
  }
}
