#include "IXInput.hpp"

#include "../InputState.hpp"

#include "../../../Include/Math.hpp"

#include <Windows.h>
#include <Xinput.h>

namespace detail
{
  struct IXInput::Status
  {
    bool isConnect_;
    //  ���͏��
    InputState InputStatus_[kButtonNum];
    //  ���̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 LeftStick_;
    //  �E�̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 RightStick_;
    //  ���̃g���K�[�̓��͏��
    float LeftTrigger_;
    //  �E�̃g���K�[�̓��͏��
    float RightTrigger_;
  };

  //  ������
  IXInput::IXInput()
  {
    Status_ = new Status[XUSER_MAX_COUNT];

    for (int i = 0; i < XUSER_MAX_COUNT; ++i)
    {
      for (int j = 0; j < kButtonNum; ++j)
      {
        Status_[i].InputStatus_[j] = InputState::Released;
      }
    }
  }

  //  �X�V
  void IXInput::Update()
  {
    for (int i = 0; i < XUSER_MAX_COUNT; ++i)
    {
      XINPUT_STATE State;

      //  �ڑ�����Ă��Ȃ���
      if (XInputGetState(i, &State) == ERROR_DEVICE_NOT_CONNECTED)
      {
        Status_[i].isConnect_ = false;
        continue;
      }

      auto& Gamepad = State.Gamepad;
      Status_[i].isConnect_ = true;

      for (int j = 0; j < kButtonNum; ++j)
      {
        auto& InputStatus_ = Status_[i].InputStatus_;

        //  ��Ԃ̕��
        {
          //  �������u��
          if (InputStatus_[j] == InputState::Pressed)
          {
            InputStatus_[j] = InputState::Press;
          }
          //  �������u��
          else if (InputStatus_[j] == InputState::Released)
          {
            InputStatus_[j] = InputState::Release;
          }
        }

        //  ��Ԃ��擾
        {
          //  �����Ă���Ȃ�true
          if (Gamepad.wButtons & kXInputButtonsCode[j])
          {
            //  �������u��
            if (InputStatus_[j] == InputState::Release)
            {
              InputStatus_[j] = InputState::Pressed;
            }
          }
          else
          {
            //  �������u��
            if (InputStatus_[j] == InputState::Press)
            {
              InputStatus_[j] = InputState::Released;
            }
          }

          static constexpr float kAnalogStickMinimumValue = -32768.0f;
          static constexpr float kAnalogStickHalfValue = 65535 * 0.5f;

          Status_[i].LeftStick_ = ((hdx::float2(static_cast<float>(Gamepad.sThumbLX), static_cast<float>(Gamepad.sThumbLY)) - kAnalogStickMinimumValue) / kAnalogStickHalfValue) - 1.0f;
          Status_[i].RightStick_ = ((hdx::float2(static_cast<float>(Gamepad.sThumbRX), static_cast<float>(Gamepad.sThumbRY)) - kAnalogStickMinimumValue) / kAnalogStickHalfValue) - 1.0f;

          static constexpr float kTriggerMaxValue = 255.0f;

          Status_[i].LeftTrigger_ = Gamepad.bLeftTrigger / kTriggerMaxValue;
          Status_[i].RightTrigger_ = Gamepad.bRightTrigger / kTriggerMaxValue;
        }
      }
    }

  }

  //  ���
  IXInput::~IXInput()
  {
    //  �U���̒�~
    {
      XINPUT_VIBRATION Vibration{ 0, 0 };

      for (int i = 0; i < XUSER_MAX_COUNT; ++i)
      {
        XInputSetState(i, &Vibration);
      }
    }

    delete[] Status_;
    Status_ = nullptr;
  }


  //--------------------------------------------------

  //  ������Ă���Ȃ�true��Ԃ�
  bool IXInput::Press(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Press || Status_[_Index].InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IXInput::Pressed(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IXInput::Released(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Released;
  }

  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool IXInput::Release(int _Number, int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Release || Status_[_Index].InputStatus_[_Number] == InputState::Released;
  }

  //  �����̃{�^����������Ă����true��Ԃ�
  bool IXInput::AnyButtonPress(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Press(i, _Index))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool IXInput::AnyButtonPressed(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Pressed(i, _Index))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool IXInput::AnyButtonReleased(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Released(i, _Index))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }

  //  ���X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 IXInput::GetLeftStick(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return hdx::float2(0.0f);

    hdx::float2 Value = Status_[_Index].LeftStick_;

    if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
    if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

    return Value;
  }

  //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 IXInput::GetRightStick(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return hdx::float2(0.0f);

    hdx::float2 Value = Status_[_Index].RightStick_;

    if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
    if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

    return Value;
  }

  //  ���g���K�[�̓��͏�Ԃ��擾
  float IXInput::GetLeftTrigger(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return 0.0f;

    if (Status_[_Index].LeftTrigger_ < _DeadZone) return 0.0f;

    return Status_[_Index].LeftTrigger_;
  }

  //  �E�g���K�[�̓��͏�Ԃ��擾
  float IXInput::GetRightTrigger(int _Index, float _DeadZone)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return 0.0f;

    if (Status_[_Index].RightTrigger_ < _DeadZone) return 0.0f;

    return Status_[_Index].RightTrigger_;
  }

  //  �ڑ�����Ă��邩�m�F
  bool IXInput::isConnect(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].isConnect_;
  }

  //  �R���g���[����U�������܂�
  void IXInput::SetVibration(int _Index, float _Speed)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return;

    static constexpr WORD kMaxSpeed = 65534;

    XINPUT_VIBRATION Vibration{ static_cast<WORD>(kMaxSpeed*_Speed),static_cast<WORD>(kMaxSpeed*_Speed) };

    XInputSetState(_Index, &Vibration);
  }

  //  �R���g���[���̐U�����~�߂܂�
  void IXInput::StopVibration(int _Index)const
  {
    //  �ΏۊO
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return;

    XINPUT_VIBRATION Vibration{ 0, 0 };

    XInputSetState(_Index, &Vibration);
  }
}
