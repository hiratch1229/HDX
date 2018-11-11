#include "Engine.hpp"

#include "../System/ISystem.hpp"
#include "../Renderer/Renderer2D/IRenderer2D.hpp"
#include "../Input/Keyboard/IKeyboard.hpp"
#include "../Input/Mouse/IMouse.hpp"
#include "../Input/XInput/IXInput.hpp"
#include "../Input/Gamepad/IGamepad.hpp"
#include "../BlendState/IBlendState.hpp"
#include "../SamplerState/ISamplerState.hpp"
#include "../RasterizerState/IRasterizerState.hpp"
#include "../DepthStencilState/IDepthStencilState.hpp"
#include "../VertexShader/IVertexShader.hpp"
#include "../PixelShader/IPixelShader.hpp"
#include "../WIC/IWIC.hpp"
#include "../Texture/ITexture.hpp"
#include "../RenderTarget/IRenderTarget.hpp"
#include "../Random/IRandom.hpp"

#include <crtdbg.h>

namespace detail
{
  Engine* Engine::pEngine = nullptr;

  Engine::Engine()
  {
    //  ��x�ڈȍ~�쐬���G���[
    _ASSERT_EXPR(!pEngine, L"Engine�̓�x�ڂ̍쐬�ł�");
    
    //  �쐬���Ƀf�[�^�����o����悤�ɂ���
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
    pRenderTarget_.Release();
    pRandom_.Release();

    pEngine = nullptr;
  }
}
