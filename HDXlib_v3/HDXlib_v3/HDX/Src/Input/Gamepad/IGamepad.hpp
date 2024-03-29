#pragma once
#include <d3d11.h>

#include "Include/Button.hpp"
#include "Include/Type2.hpp"

class IGamepad
{
public:
  static IGamepad* Create();

  IGamepad() = default;

  virtual ~IGamepad() = default;

  virtual void Initialize(const HWND& _hWnd) = 0;

  virtual void CreateDirectInputDevice(const GUID& GuidProductFromDirectInput) = 0;

  virtual void Update() = 0;

  virtual bool Press(int _Number, int _Index)const = 0;

  virtual bool Pressed(int _Number, int _Index)const = 0;

  virtual bool Released(int _Number, int _Index)const = 0;

  virtual bool Release(int _Number, int _Index)const = 0;

  virtual bool isConnect(int _Index)const = 0;

  virtual int GetButtonNum(int _Index)const = 0;

  virtual bool AnyButtonPress(int _Index)const = 0;

  virtual bool AnyButtonPressed(int _Index)const = 0;

  virtual bool AnyButtonReleased(int _Index)const = 0;

  virtual hdx::Button GetButton(int _Index, int _Number)const = 0;

  virtual hdx::float2 GetLeftStick(int _Index, float _DeadZone)const = 0;

  virtual hdx::float2 GetRightStick(int _Index, float _DeadZone)const = 0;

  virtual float GetLeftTrigger(int _Index, float _DeadZone)const = 0;

  virtual float GetRightTrigger(int _Index, float _DeadZone)const = 0;

  virtual void SetVibration(int _Index, float _Speed)const = 0;

  virtual void StopVibration(int _Index)const = 0;
};
