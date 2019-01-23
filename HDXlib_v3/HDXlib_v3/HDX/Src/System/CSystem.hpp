#pragma once
#include "ISystem.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <memory>

class CSystem : public ISystem
{
  class FrameRate;
  class Window;
private:
  bool isSetUpWindow_ = false;
  Microsoft::WRL::ComPtr<ID3D11Device> pDevice_;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext_;
  Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain_;
  Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView_;
  Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView_;
  std::unique_ptr<FrameRate> pFrameRate_;
  std::unique_ptr<Window> pWindow_;
private:
  void ResizeSwapChain();
  void CreateDevice();
  void CreateSwapChain();
  void CreateRenderTargetViewAndDepthStencilView();
public:
  CSystem();

  ~CSystem();

  void Initialize()override;

  bool Update()override;

  int GetWindowWidth()const override;

  int GetWindowHeight()const override;

  const hdx::int2& GetWindowSize()const override;

  float GetDeltaTime()const override;

  int GetFPS()const override;

  void SetWindowLeftTopPos(int _LeftPos, int _TopPos)override;

  void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos)override;

  void SetWindowSize(int _Width, int _Height)override;

  void SetWindowSize(const hdx::int2& _Size)override;

  void SetWindowMode(bool _isFullScreen)override;

  void SetWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen)override;

  void SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen)override;

  void ShowCursor(bool _isShowCursor)override;

  void SetTitle(const char* _Title)override;

  void SetBackColor(const hdx::ColorF& _Color)override;

  void ChangeWindowMode()override;

  void RenameTitle(const char* _Title)override;

  void ScreenShot()override;

  void Exit()override;
};
