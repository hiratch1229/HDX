#pragma once
#include "Include/Type2.hpp"
#include "Include/Color.hpp"

class ISystem
{
public:
  static ISystem* Create();

  ISystem() = default;

  virtual ~ISystem() = default;

  virtual void Initialize() = 0;

  virtual bool Update() = 0;

  virtual int GetWindowWidth()const = 0;

  virtual int GetWindowHeight()const = 0;

  virtual const hdx::int2& GetWindowSize()const = 0;

  virtual float GetDeltaTime()const = 0;

  virtual int GetFPS()const = 0;

  virtual void SetWindowLeftTopPos(int _LeftPos, int _TopPos) = 0;

  virtual void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos) = 0;

  virtual void SetWindowSize(int _Width, int _Height) = 0;

  virtual void SetWindowSize(const hdx::int2& _Size) = 0;

  virtual void SetWindowMode(bool _isFullScreen) = 0;

  virtual void SetWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen) = 0;

  virtual void SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen) = 0;

  virtual void ShowCursor(bool _isShowCursor) = 0;

  virtual void SetTitle(const char* _Title) = 0;

  virtual void SetBackColor(const hdx::ColorF& _Color) = 0;

  virtual void ChangeWindowMode() = 0;

  virtual void RenameTitle(const char* _Title) = 0;

  virtual void ScreenShot() = 0;

  virtual void Exit() = 0;
};
