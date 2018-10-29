#pragma once
#include <HDX/Type2.hpp>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11BlendState;
struct HWND__;
typedef struct HWND__ *HWND;

namespace hdx
{
  class BlendState;
  struct ColorF;
}

namespace detail
{
  class ISystem
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    int GetWindowWidth();
    int GetWindowHeight();
    hdx::int2 GetWindowSize();
  public:
    void SetWindowLeftTopPos(int _LeftPos, int _TopPos);
    void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos);
    void SetWindowSize(int _Width, int _Height);
    void SetWindowSize(const hdx::int2& _Size);
    void SetWindowMode(bool _isFullScreen);
    void SetWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen );
    void SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen );
    void ShowCursor(bool _isShowCursor);
    void SetTitle(const char* _Title);
    void SetBackColor(const hdx::ColorF& _Color);
  public:
    void ChangeWindowMode();
    void RenameTitle(const char* _Title);
    void ScreenShot();
    void Exit();
  public:
    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetImmediateContext();
    IDXGISwapChain* GetSwapChain();
    HWND GetHWND();
  public:
    void SetBlendState(ID3D11BlendState* _pBlendState);
  public:
    ISystem();
    ~ISystem();
    bool Update();
  };
}
