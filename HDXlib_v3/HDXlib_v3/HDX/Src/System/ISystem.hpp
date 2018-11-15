#pragma once
#include "../../Include/Types.hpp"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct HWND__;
typedef HWND__* HWND;

namespace hdx
{
  class BlendState;
  struct int2;
  struct ColorF;
}

class ISystem
{
public:
  int GetWindowWidth()const;
  int GetWindowHeight()const;
  const hdx::int2& GetWindowSize()const;
  float GetDeltaTime()const;
public:
  void SetWindowLeftTopPos(int _LeftPos, int _TopPos);
  void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos);
  void SetWindowSize(int _Width, int _Height);
  void SetWindowSize(const hdx::int2& _Size);
  void SetWindowMode(bool _isFullScreen);
  void SetWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen);
  void SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen);
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
  ID3D11RenderTargetView** GetRenderTargetView();
  ID3D11DepthStencilView* GetDepthStencilView();
  const HWND& GethWnd();
public:
  bool Update();
public:
  ISystem();
};
