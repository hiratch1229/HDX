#pragma once

class ISystem;
class IBlendState;
class IConstantBuffer;
class IDepthStencilState;
class IRasterizerState;
class IRenderTarget;
class ISamplerState;
class IVertexShader;
class IPixelShader;
class IRenderer2D;
class IRenderer3D;
class IKeyboard;
class IMouse;
class IXInput;
class IGamepad;
class ITexture;
class IModel;
class ISound;
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
  Interface* operator->()
  {
    return pInterface_;
  }
public:
  Component()
    : pInterface_(new Interface)
  {

  }
};

class Engine
{
  static Engine* pEngine;
private:
  Component<ISystem> pSystem_;
  Component<IBlendState> pBlendState_;
  Component<IConstantBuffer> pConstantBuffer_;
  Component<IDepthStencilState> pDepthStencilState_;
  Component<IRasterizerState> pRasterizerState_;
  Component<IRenderTarget> pRenderTarget_;
  Component<ISamplerState> pSamplerState_;
  Component<IVertexShader> pVertexShader_;
  Component<IPixelShader> pPixelShader_;
  Component<IRenderer2D> pRenderer2D_;
  Component<IRenderer3D> pRenderer3D_;
  Component<IKeyboard> pKeyboard_;
  Component<IMouse> pMouse_;
  Component<IXInput> pXInput_;
  Component<IGamepad> pGamepad_;
  Component<ITexture> pTexture_;
  Component<IModel> pModel_;
  Component<ISound> pSound_;
  Component<IRandom> pRandom_;
  Component<IGUI> pGUI_;
public:
  Engine();
  ~Engine();
public:
  static void Start(const char* _InterfaceName);
  static long long End(const char* _InterfaceName);
private:
public:
  template<class T> static T* Get() { return nullptr; }
  template<> static ISystem* Get() { return pEngine->pSystem_.Get(); }
  template<> static IBlendState* Get() { return pEngine->pBlendState_.Get(); }
  template<> static IConstantBuffer* Get() { return pEngine->pConstantBuffer_.Get(); }
  template<> static IDepthStencilState* Get() { return pEngine->pDepthStencilState_.Get(); }
  template<> static IRasterizerState* Get() { return pEngine->pRasterizerState_.Get(); }
  template<> static IRenderTarget* Get() { return pEngine->pRenderTarget_.Get(); }
  template<> static ISamplerState* Get() { return pEngine->pSamplerState_.Get(); }
  template<> static IVertexShader* Get() { return pEngine->pVertexShader_.Get(); }
  template<> static IPixelShader* Get() { return pEngine->pPixelShader_.Get(); }
  template<> static IRenderer2D* Get() { return pEngine->pRenderer2D_.Get(); }
  template<> static IRenderer3D* Get() { return pEngine->pRenderer3D_.Get(); }
  template<> static IKeyboard* Get() { return pEngine->pKeyboard_.Get(); }
  template<> static IMouse* Get() { return pEngine->pMouse_.Get(); }
  template<> static IXInput* Get() { return pEngine->pXInput_.Get(); }
  template<> static IGamepad* Get() { return pEngine->pGamepad_.Get(); }
  template<> static ITexture* Get() { return pEngine->pTexture_.Get(); }
  template<> static IModel* Get() { return pEngine->pModel_.Get(); }
  template<> static ISound* Get() { return pEngine->pSound_.Get(); }
  template<> static IRandom* Get() { return pEngine->pRandom_.Get(); }
  template<> static IGUI* Get() { return pEngine->pGUI_.Get(); }
};
