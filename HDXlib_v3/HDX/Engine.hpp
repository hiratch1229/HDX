#pragma once

namespace detail
{
  class ISystem;
  class IKeyboard;
  class IMouse;
  class IXInput;
  class IGamepad;
  class IVertexShader;
  class IPixelShader;
  class WIC;
  class ISprite;
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
    Component<IKeyboard> pKeyboard_;
    Component<IMouse> pMouse_;
    Component<IXInput> pXInput_;
    Component<IGamepad> pGamepad_;
    Component<IVertexShader> pVertexShader_;
    Component<IPixelShader> pPixelShader_;
    Component<WIC> pWIC_;
    Component<ISprite> pSprite_;
    Component<IRandom> pRandom_;
  public:
    Engine();
    ~Engine();
  public:
    static ISystem* GetSystem()
    {
      return pEngine->pSystem_.Get();
    }
    static IKeyboard* GetKeyboard()
    {
      return pEngine->pKeyboard_.Get();
    }
    static IMouse* GetMouse()
    {
      return pEngine->pMouse_.Get();
    }
    static IXInput* GetXInput()
    {
      return pEngine->pXInput_.Get();
    }
    static IGamepad* GetGamepad()
    {
      return pEngine->pGamepad_.Get();
    }
    static IVertexShader* GetVertexShader()
    {
      return pEngine->pVertexShader_.Get();
    }
    static IPixelShader* GetPixelShader()
    {
      return pEngine->pPixelShader_.Get();
    }
    static WIC* GetWIC()
    {
      return pEngine->pWIC_.Get();
    }
    static ISprite* GetSprite()
    {
      return pEngine->pSprite_.Get();
    }
    static IRandom* GetRandom()
    {
      return pEngine->pRandom_.Get();
    }
  };
}
