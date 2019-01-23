#pragma once
#include "Include/Type2.hpp"

#include "Include/Constants.hpp"

constexpr int kXInputButtonsCode[] = {
  0x0001, //  XINPUT_GAMEPAD_DPAD_UP
  0x0002, //  XINPUT_GAMEPAD_DPAD_DOWN
  0x0004, //  XINPUT_GAMEPAD_DPAD_LEFT
  0x0008, //  XINPUT_GAMEPAD_DPAD_RIGHT
  0x0010, //  XINPUT_GAMEPAD_START
  0x0020, //  XINPUT_GAMEPAD_BACK
  0x0040, //  XINPUT_GAMEPAD_LEFT_THUMB
  0x0080, //  XINPUT_GAMEPAD_RIGHT_THUMB
  0x0100, //  XINPUT_GAMEPAD_LEFT_SHOULDER
  0x0200, //  XINPUT_GAMEPAD_RIGHT_SHOULDER
  0x1000, //  XINPUT_GAMEPAD_A
  0x2000, //  XINPUT_GAMEPAD_B
  0x4000, //  XINPUT_GAMEPAD_X
  0x8000, //  XINPUT_GAMEPAD_Y
};

class IXInput
{
public:
  static constexpr int kControllerNum = (hdx::Constants::ControllerMaxNum <= 4) ? hdx::Constants::ControllerMaxNum : 4;
  static constexpr int kButtonNum = sizeof(kXInputButtonsCode) / sizeof(kXInputButtonsCode[0]);
public:
  static IXInput* Create();

  IXInput() = default;

  virtual ~IXInput() = default;

  virtual void Update() = 0;

  virtual bool Press(int _Number, int _Index)const = 0;

  virtual bool Pressed(int _Number, int _Index)const = 0;

  virtual bool Released(int _Number, int _Index)const = 0;

  virtual bool Release(int _Number, int _Index)const = 0;

  virtual bool isConnect(int _Index)const = 0;

  virtual bool AnyButtonPress(int _Index)const = 0;

  virtual bool AnyButtonPressed(int _Index)const = 0;

  virtual bool AnyButtonReleased(int _Index)const = 0;

  virtual hdx::float2 GetLeftStick(int _Index, float _DeadZone)const = 0;

  virtual hdx::float2 GetRightStick(int _Index, float _DeadZone)const = 0;

  virtual float GetLeftTrigger(int _Index, float _DeadZone)const = 0;

  virtual float GetRightTrigger(int _Index, float _DeadZone)const = 0;

  virtual void SetVibration(int _Index, float _Speed)const = 0;

  virtual void StopVibration(int _Index)const = 0;
};
