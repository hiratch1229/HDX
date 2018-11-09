#pragma once

namespace detail
{
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
  class IWIC;
  class ITexture;
  class IRandom;

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
    Component<IWIC> pWIC_;
    Component<ITexture> pTexture_;
    Component<IRandom> pRandom_;
  public:
    Engine();
    ~Engine();
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
    static IWIC* GetWIC() { return pEngine->pWIC_.Get(); }
    static ITexture* GetTexture() { return pEngine->pTexture_.Get(); }
    static IRandom* GetRandom() { return pEngine->pRandom_.Get(); }
  };
}

#if 1

#define GetFunc(name) \
inline detail::I##name* Get##name()\
{\
  static detail::I##name* p##name = nullptr;\
\
  if (!p##name)\
  {\
  p##name = detail::Engine::Get##name();\
  }\
\
return p##name;\
}\

#else

#define GetFunc(name) \
inline detail::I##name* Get##name()\
{\
return detail::Engine::Get##name();\
}\

#endif // 0

GetFunc(System)
GetFunc(Renderer2D)
GetFunc(Keyboard)
GetFunc(Mouse)
GetFunc(XInput)
GetFunc(Gamepad)
GetFunc(BlendState)
GetFunc(SamplerState)
GetFunc(RasterizerState)
GetFunc(DepthStencilState)
GetFunc(VertexShader)
GetFunc(PixelShader)
GetFunc(WIC)
GetFunc(Texture)
GetFunc(Random)
