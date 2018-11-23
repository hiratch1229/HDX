#include "Engine.hpp"

#include "System/ISystem.hpp"
#include "BlendState/IBlendState.hpp"
#include "ConstantBuffer/IConstantBuffer.hpp"
#include "DepthStencilState/IDepthStencilState.hpp"
#include "RasterizerState/IRasterizerState.hpp"
#include "RenderTarget/IRenderTarget.hpp"
#include "SamplerState/ISamplerState.hpp"
#include "VertexShader/IVertexShader.hpp"
#include "PixelShader/IPixelShader.hpp"
#include "Renderer/Renderer2D/IRenderer2D.hpp"
#include "Renderer/Renderer3D/IRenderer3D.hpp"
#include "Input/Keyboard/IKeyboard.hpp"
#include "Input/Mouse/IMouse.hpp"
#include "Input/XInput/IXInput.hpp"
#include "Input/Gamepad/IGamepad.hpp"
#include "Texture/ITexture.hpp"
#include "Model/IModel.hpp"
#include "Random/IRandom.hpp"
#include "GUI/IGUI.hpp"

#include "../Include/System.hpp"

#include <Windows.h>
#include <assert.h>
#include <string>

#include "Benchmark.hpp"

namespace
{
  Benchmark Timer;
}

Engine* Engine::pEngine = nullptr;

Engine::Engine()
{
  //  ��x�ڈȍ~�쐬���G���[
  assert(!pEngine);

  //  �쐬���Ƀf�[�^�����o����悤�ɂ���
  pEngine = this;

  //  ������
  pSystem_->Initialize();
}

Engine::~Engine()
{
  pSystem_.Release();
  pBlendState_.Release();
  pConstantBuffer_.Release();
  pDepthStencilState_.Release();
  pRasterizerState_.Release();
  pRenderTarget_.Release();
  pSamplerState_.Release();
  pVertexShader_.Release();
  pPixelShader_.Release();
  pRenderer2D_.Release();
  pRenderer3D_.Release();
  pKeyboard_.Release();
  pMouse_.Release();
  pXInput_.Release();
  pGamepad_.Release();
  pTexture_.Release();
  pModel_.Release();
  pRandom_.Release();
  pGUI_.Release();

  pEngine = nullptr;
}

void Engine::Start(const char* _InterfaceName)
{
  char c[256];
  sprintf_s(c, "%s �J�n\n", _InterfaceName);

  hdx::System::OutputDebug(c);

  Timer.Start();
}

long long Engine::End(const char* _InterfaceName)
{
  long long Time = Timer.End<std::chrono::nanoseconds>();

  char c[256];
  sprintf_s(c, "%s �I�� �o�ߎ���:%sns\n", _InterfaceName, std::to_string(Time).c_str());

  hdx::System::OutputDebug(c);

  return Time;
}
