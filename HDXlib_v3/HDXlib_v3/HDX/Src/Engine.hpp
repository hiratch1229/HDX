#pragma once

class ISystem;
class IRenderer2D;
class IKeyboard;
class IMouse;
class IXInput;
class IGamepad;
class IBlendState;
class ISamplerState;
class IRasterizerState;
class IDepthStencilState;
class IVertexShader;
class IPixelShader;
class ITexture;
class IRenderTarget;
class IRandom;
class IGUI;

template <class Interface>
class Component
{
  Interface* pInterface_ = nullptr;
public:
  Interface* Get()
  {
    return pInterface_;
  }
  void Release()
  {
    delete pInterface_;
    pInterface_ = nullptr;
  }
public:
  Component()
    : pInterface_(new Interface)
  {

  }
  ~Component() = default;
};

class Engine
{
  static Engine* pEngine;
private:
  Component<ISystem> pSystem_;
  Component<IRenderer2D> pRenderer2D_;
  Component<IKeyboard> pKeyboard_;
  Component<IMouse> pMouse_;
  Component<IXInput> pXInput_;
  Component<IGamepad> pGamepad_;
  Component<IBlendState> pBlendState_;
  Component<ISamplerState> pSamplerState_;
  Component<IRasterizerState> pRasterizerState_;
  Component<IDepthStencilState> pDepthStencilState_;
  Component<IVertexShader> pVertexShader_;
  Component<IPixelShader> pPixelShader_;
  Component<ITexture> pTexture_;
  Component<IRenderTarget> pRenderTarget_;
  Component<IRandom> pRandom_;
  Component<IGUI> pGUI_;
public:
  Engine();
  ~Engine();
public:
  static void Start(const char* _InterfaceName);
  static long long End(const char* _InterfaceName);
public:
  static ISystem* GetSystem() { return pEngine->pSystem_.Get(); }
  static IRenderer2D* GetRenderer2D() { return pEngine->pRenderer2D_.Get(); }
  static IKeyboard* GetKeyboard() { return pEngine->pKeyboard_.Get(); }
  static IMouse* GetMouse() { return pEngine->pMouse_.Get(); }
  static IXInput* GetXInput() { return pEngine->pXInput_.Get(); }
  static IGamepad* GetGamepad() { return pEngine->pGamepad_.Get(); }
  static IBlendState* GetBlendState() { return pEngine->pBlendState_.Get(); }
  static ISamplerState* GetSamplerState() { return pEngine->pSamplerState_.Get(); }
  static IRasterizerState* GetRasterizerState() { return pEngine->pRasterizerState_.Get(); }
  static IDepthStencilState* GetDepthStencilState() { return pEngine->pDepthStencilState_.Get(); }
  static IVertexShader* GetVertexShader() { return pEngine->pVertexShader_.Get(); }
  static IPixelShader* GetPixelShader() { return pEngine->pPixelShader_.Get(); }
  static ITexture* GetTexture() { return pEngine->pTexture_.Get(); }
  static IRenderTarget* GetRenderTarget() { return pEngine->pRenderTarget_.Get(); }
  static IRandom* GetRandom() { return pEngine->pRandom_.Get(); }
  static IGUI* GetGUI() { return pEngine->pGUI_.Get(); }
};
