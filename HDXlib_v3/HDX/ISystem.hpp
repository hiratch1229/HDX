#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;

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
  public:
    ISystem();
    ~ISystem();
    bool Update();
  };
}
