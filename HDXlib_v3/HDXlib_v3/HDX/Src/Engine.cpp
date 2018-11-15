#include "Engine.hpp"

#include "System/ISystem.hpp"
#include "Renderer/Renderer2D/IRenderer2D.hpp"
#include "Input/Keyboard/IKeyboard.hpp"
#include "Input/Mouse/IMouse.hpp"
#include "Input/XInput/IXInput.hpp"
#include "Input/Gamepad/IGamepad.hpp"
#include "BlendState/IBlendState.hpp"
#include "SamplerState/ISamplerState.hpp"
#include "RasterizerState/IRasterizerState.hpp"
#include "DepthStencilState/IDepthStencilState.hpp"
#include "VertexShader/IVertexShader.hpp"
#include "PixelShader/IPixelShader.hpp"
#include "Texture/ITexture.hpp"
#include "RenderTarget/IRenderTarget.hpp"
#include "Random/IRandom.hpp"

#include "../Include/System.hpp"

#include <Windows.h>
#include <assert.h>

#include <chrono>

namespace
{
  std::chrono::high_resolution_clock::time_point Start = std::chrono::high_resolution_clock::now();
}

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
  pTexture_.Release();
  pRenderTarget_.Release();
  pRandom_.Release();

  pEngine = nullptr;
}

#include <string>
void Engine::End(const char* _InterfaceName)
{
  char c[256];
  sprintf_s(c, "%s 経過時間:%sms\n", _InterfaceName, std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - Start).count()).c_str());

  hdx::System::OutputDebug(c);

  Start = std::chrono::high_resolution_clock::now();
}
