#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct HWND__;
typedef struct HWND__ *HWND;

namespace hdx
{
  enum class BlendState;
}

namespace detail
{
  class ISystem
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    void ChangeWindowMode();
    void ScreenShot();
    void Exit();
  public:
    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetImmediateContext();
    IDXGISwapChain* GetSwapChain();
    HWND GetHWND();
  public:
    void SetBlendState(const hdx::BlendState& _BlendState);
  public:
    ISystem();
    ~ISystem();
    bool Update();
  };
}
