#include "CXInput.hpp"

#include "Include/Math.hpp"

#include <Windows.h>
#include <Xinput.h>

//  ���
CXInput::~CXInput()
{
  //  �U���̒�~
  {
    XINPUT_VIBRATION Vibration{ 0, 0 };

    for (int i = 0; i < kControllerNum; ++i)
    {
      XInputSetState(i, &Vibration);
    }
  }
}

//  �X�V
void CXInput::Update()
{
  XINPUT_STATE XInputState;

  for (int i = 0; i < kControllerNum; ++i)
  {
    //  �ڑ�����Ă��Ȃ���
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

    //  ��Ԃ�ۑ�
    {
      //  �A�i���O�X�e�B�b�N
      hdx::float2 LeftValue = (hdx::float2(Gamepad.sThumbLX + SHRT_MIN, Gamepad.sThumbLY + SHRT_MIN)*2.0f / kAnalogStickMaxValue);
      hdx::float2 RightValue = (hdx::float2(Gamepad.sThumbRX + SHRT_MIN, Gamepad.sThumbRY + SHRT_MIN)*2.0f / kAnalogStickMaxValue);
      {
        Status.LeftStick = hdx::float2(LeftValue.x - 1.0f, LeftValue.y - 1.0f);
        Status.RightStick = hdx::float2(RightValue.x - 1.0f, RightValue.y - 1.0f);
      }

      //  �g���K�[
      {
        Status.LeftTrigger = Gamepad.bLeftTrigger / kTriggerMaxValue;
        Status.RightTrigger = Gamepad.bRightTrigger / kTriggerMaxValue;
      }
    }
  }
}

//  ���X�e�B�b�N�̓��͏�Ԃ��擾
hdx::float2 CXInput::GetLeftStick(int _Index, float _DeadZone)const
{
  hdx::float2 Value = Status_[_Index].LeftStick;

  if (hdx::Math::GetAbsoluteValue(Value.x) < _DeadZone) Value.x = 0.0f;
  if (hdx::Math::GetAbsoluteValue(Value.y) < _DeadZone) Value.y = 0.0f;

  return Value;
}

//  �E�X�e�B�b�N�̓��͏�Ԃ��擾
hdx::float2 CXInput::GetRightStick(int _Index, float _DeadZone)const
{
  hdx::float2 Value = Status_[_Index].RightStick;

  if (hdx::Math::GetAbsoluteValue(Value.x) < _DeadZone) Value.x = 0.0f;
  if (hdx::Math::GetAbsoluteValue(Value.y) < _DeadZone) Value.y = 0.0f;

  return Value;
}

//  ���g���K�[�̓��͏�Ԃ��擾
float CXInput::GetLeftTrigger(int _Index, float _DeadZone)const
{
  if (Status_[_Index].LeftTrigger < _DeadZone) return 0.0f;

  return Status_[_Index].LeftTrigger;
}

//  �E�g���K�[�̓��͏�Ԃ��擾
float CXInput::GetRightTrigger(int _Index, float _DeadZone)const
{
  if (Status_[_Index].RightTrigger < _DeadZone) return 0.0f;

  return Status_[_Index].RightTrigger;
}

//  �R���g���[����U�������܂�
void CXInput::SetVibration(int _Index, float _Speed)const
{
  static constexpr WORD kMaxSpeed = 65535;

  const WORD MotorSpeed = static_cast<WORD>(kMaxSpeed*_Speed);

  XINPUT_VIBRATION Vibration{ MotorSpeed, MotorSpeed };

  XInputSetState(_Index, &Vibration);
}

//  �R���g���[���̐U�����~�߂܂�
void CXInput::StopVibration(int _Index)const
{
  XINPUT_VIBRATION Vibration{ 0, 0 };

  XInputSetState(_Index, &Vibration);
}
