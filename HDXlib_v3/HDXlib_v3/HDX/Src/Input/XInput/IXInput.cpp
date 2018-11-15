#include "IXInput.hpp"

#include "../InputState.hpp"

#include "../../../Include/Math.hpp"

#include <Windows.h>
#include <Xinput.h>

//  更新
void IXInput::Update()
{
  XINPUT_STATE XInputState;

  for (int i = 0; i < kControllerNum; ++i)
  {
    //  接続されていない時
    if (XInputGetState(i, &XInputState) == ERROR_DEVICE_NOT_CONNECTED)
    {
      Status_[i].isConnect = false;
      continue;
    }

    Status& Status = Status_[i];
    Status.isConnect = true;

    auto& Gamepad = XInputState.Gamepad;
    for (int j = 0; j < kButtonNum; ++j)
    {
      Status.InputStatus[j].Update((Gamepad.wButtons & kXInputButtonsCode[j]) != 0);
    }

    //  状態を保存
    {
      //  アナログスティック
      static constexpr int kAnalogStickMaxValue = 65535;

      hdx::float2 LeftValue = hdx::float2(static_cast<float>(Gamepad.sThumbLX), static_cast<float>(Gamepad.sThumbLY)) - SHRT_MIN;
      hdx::float2 RightValue = hdx::float2(static_cast<float>(Gamepad.sThumbRX), static_cast<float>(Gamepad.sThumbRY)) - SHRT_MIN;
      {
        Status.LeftStick = ((LeftValue*2.0f) / kAnalogStickMaxValue) - 1.0f;
        Status.RightStick = ((RightValue*2.0f) / kAnalogStickMaxValue) - 1.0f;
      }

      //  トリガー
      static constexpr float kTriggerMaxValue = 255.0f;
      {
        Status.LeftTrigger = Gamepad.bLeftTrigger / kTriggerMaxValue;
        Status.RightTrigger = Gamepad.bRightTrigger / kTriggerMaxValue;
      }
    }
  }
}

//  解放
IXInput::~IXInput()
{
  //  振動の停止
  {
    XINPUT_VIBRATION Vibration{ 0, 0 };

    for (int i = 0; i < kControllerNum; ++i)
    {
      XInputSetState(i, &Vibration);
    }
  }
}


//--------------------------------------------------

//  左スティックの入力状態を取得
hdx::float2 IXInput::GetLeftStick(int _Index, float _DeadZone)const
{
  hdx::float2 Value = Status_[_Index].LeftStick;

  if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
  if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

  return Value;
}

//  右スティックの入力状態を取得
hdx::float2 IXInput::GetRightStick(int _Index, float _DeadZone)const
{
  hdx::float2 Value = Status_[_Index].RightStick;

  if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
  if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

  return Value;
}

//  左トリガーの入力状態を取得
float IXInput::GetLeftTrigger(int _Index, float _DeadZone)const
{
  if (Status_[_Index].LeftTrigger < _DeadZone) return 0.0f;

  return Status_[_Index].LeftTrigger;
}

//  右トリガーの入力状態を取得
float IXInput::GetRightTrigger(int _Index, float _DeadZone)const
{
  if (Status_[_Index].RightTrigger < _DeadZone) return 0.0f;

  return Status_[_Index].RightTrigger;
}

//  コントローラを振動させます
void IXInput::SetVibration(int _Index, float _Speed)const
{
  static constexpr WORD kMaxSpeed = 65535;

  const WORD MotorSpeed = static_cast<WORD>(kMaxSpeed*_Speed);

  XINPUT_VIBRATION Vibration{ MotorSpeed, MotorSpeed };

  XInputSetState(_Index, &Vibration);
}

//  コントローラの振動を止めます
void IXInput::StopVibration(int _Index)const
{
  XINPUT_VIBRATION Vibration{ 0, 0 };

  XInputSetState(_Index, &Vibration);
}
