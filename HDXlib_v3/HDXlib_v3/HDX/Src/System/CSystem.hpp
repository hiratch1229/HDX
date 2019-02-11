#pragma once
#include "ISystem.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <memory>

class CSystem : public ISystem
{
  class FrameRate
  {
    //  固定フレームレート値
    const int MaxFrameRate_;
    //  フレーム間隔
    const float FrameInterval_;
  private:
    //  クロック数
    LARGE_INTEGER FreqTime_;
    //  最後の時間
    LARGE_INTEGER LastTime_;
  public:
    //  経過時間
    float DeltaTime_ = 0.0f;
    //  現在のFPS
    int CurrentFPS_ = 0;
  public:
    FrameRate(int _MaxFrameRate);
    bool Update();
    void Reset();
  };
  class Window
  {
  public:
    const HWND hWnd_;
  public:
    hdx::int2 LeftTopPos_ = { 0,0 };
    hdx::int2 Size_ = { 1280,720 };
    char* Title_ = "HDXlib";
    bool isFullScreen_ = false;
    bool isShowCursor_ = false;
    hdx::ColorF BackColor_ = hdx::Palette::Black;
  public:
    Window();
    //  ウィンドウを設定
    void SetUpWindow();
  };
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

  const hdx::int2& GetWindowSize()const override { return pWindow_->Size_; }

  float GetDeltaTime()const override { return pFrameRate_->DeltaTime_; }

  int GetFPS()const override { return pFrameRate_->CurrentFPS_; }

  void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos)override { pWindow_->LeftTopPos_ = _LeftTopPos; }

  void SetWindowSize(const hdx::int2& _Size)override { pWindow_->Size_ = _Size; }

  void SetWindowMode(bool _isFullScreen)override { pWindow_->isFullScreen_ = _isFullScreen; }

  void SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen)override
  {
    pWindow_->LeftTopPos_ = _LeftTopPos;
    pWindow_->Size_ = _Size;
    pWindow_->isFullScreen_ = _isFullScreen;
  }

  void SetTitle(const char* _Title)override
  {
    pWindow_->Title_ = const_cast<char*>(_Title);
  }

  void SetBackColor(const hdx::ColorF& _Color)override
  {
    pWindow_->BackColor_ = _Color;
  }

  void ShowCursor(bool _isShowCursor)override;

  void ChangeWindowMode()override;

  void RenameTitle(const char* _Title)override;

  void ScreenShot()override;

  void Exit()override;
};
