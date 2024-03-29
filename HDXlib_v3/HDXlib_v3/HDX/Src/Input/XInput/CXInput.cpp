#include "CXInput.hpp"

#include "Include/Math.hpp"

#include <Windows.h>
#include <Xinput.h>

//  解放
CXInput::~CXInput()
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

//  更新
void CXInput::Update()
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
      {
        Status.LeftStick = ((hdx::float2(Gamepad.sThumbLX, Gamepad.sThumbLY) - SHRT_MIN)*2.0f) / kAnalogStickMaxValue - 1.0f;
        Status.RightStick = ((hdx::float2(Gamepad.sThumbRX, Gamepad.sThumbRY) - SHRT_MIN)*2.0f) / kAnalogStickMaxValue - 1.0f;
      }

      //  トリガー
      {
        Status.LeftTrigger = Gamepad.bLeftTrigger / kTriggerMaxValue;
        Status.RightTrigger = Gamepad.bRightTrigger / kTriggerMaxValue;
      }
    }
  }
}

//  左スティックの入力状態を取得
hdx::float2 CXInput::GetLeftStick(int _Index, float _DeadZone)const
{
  hdx::float2 Value = Status_[_Index].LeftStick;

  if (hdx::Math::GetAbsoluteValue(Value.x) < _DeadZone) Value.x = 0.0f;
  if (hdx::Math::GetAbsoluteValue(Value.y) < _DeadZone) Value.y = 0.0f;

  return Value;
}

//  右スティックの入力状態を取得
hdx::float2 CXInput::GetRightStick(int _Index, float _DeadZone)const
{
  hdx::float2 Value = Status_[_Index].RightStick;

  if (hdx::Math::GetAbsoluteValue(Value.x) < _DeadZone) Value.x = 0.0f;
  if (hdx::Math::GetAbsoluteValue(Value.y) < _DeadZone) Value.y = 0.0f;

  return Value;
}

//  左トリガーの入力状態を取得
float CXInput::GetLeftTrigger(int _Index, float _DeadZone)const
{
  if (Status_[_Index].LeftTrigger < _DeadZone) return 0.0f;

  return Status_[_Index].LeftTrigger;
}

//  右トリガーの入力状態を取得
float CXInput::GetRightTrigger(int _Index, float _DeadZone)const
{
  if (Status_[_Index].RightTrigger < _DeadZone) return 0.0f;

  return Status_[_Index].RightTrigger;
}

//  コントローラを振動させます
void CXInput::SetVibration(int _Index, float _Speed)const
{
  static constexpr WORD kMaxSpeed = 65535;

  const WORD MotorSpeed = static_cast<WORD>(kMaxSpeed*_Speed);

  XINPUT_VIBRATION Vibration{ MotorSpeed, MotorSpeed };

  XInputSetState(_Index, &Vibration);
}

//  コントローラの振動を止めます
void CXInput::StopVibration(int _Index)const
{
  XINPUT_VIBRATION Vibration{ 0, 0 };

  XInputSetState(_Index, &Vibration);
}
