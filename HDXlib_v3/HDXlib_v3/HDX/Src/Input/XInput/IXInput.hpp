#pragma once
#include "../../../Include/Button.hpp"
#include "../../../Include/Type2.hpp"
#include "../../../Include/Constants.hpp"

#include "../InputState.hpp"

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
  static constexpr int kButtonNum = sizeof(kXInputButtonsCode) / sizeof(kXInputButtonsCode[0]);
  static constexpr int kControllerNum = (hdx::Constants::ControllerMaxNum <= 4) ? hdx::Constants::ControllerMaxNum : 4;
private:
  struct Status
  {
    //  �ڑ����
    bool isConnect;
    //  ���͏��
    InputState InputStatus[kButtonNum];
    //  ���̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 LeftStick;
    //  �E�̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 RightStick;
    //  ���̃g���K�[�̓��͏��
    float LeftTrigger;
    //  �E�̃g���K�[�̓��͏��
    float RightTrigger;
  };
private:
  Status Status_[kControllerNum];
private:
  bool isWithinRange(int _Index)const
  {
    return (Status_[_Index].isConnect && 0 <= _Index && _Index < kControllerNum);
  }
  bool isWithinRange(int _Number, int _Index)const
  {
    return (Status_[_Index].isConnect && 0 <= _Number && _Number < kButtonNum && 0 <= _Index && _Index < kControllerNum);
  }
public:
  //  ������Ă���Ȃ�true��Ԃ�
  bool Press(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Press() : false;
  }
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Pressed(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Pressed() : false;
  }
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Released(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Released() : false;
  }
  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool Release(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Release() : false;
  }
public:
  //  �ڑ�����Ă��邩�m�F
  bool isConnect(int _Index)const { return Status_[_Index].isConnect; }
public:
  //  �����̃{�^����������Ă����true��Ԃ�
  bool AnyButtonPress(int _Index)const
  {
    if (!(isWithinRange(_Index))) return false;

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
  bool AnyButtonPressed(int _Index)const
  {
    if (!(isWithinRange(_Index))) return false;

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
  bool AnyButtonReleased(int _Index)const
  {
    if (!(isWithinRange(_Index))) return false;

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
public:
  //  ���X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 GetLeftStick(int _Index, float _DeadZone)const;
  //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 GetRightStick(int _Index, float _DeadZone)const;
public:
  //  ���g���K�[�̓��͏�Ԃ��擾
  float GetLeftTrigger(int _Index, float _DeadZone)const;
  //  �E�g���K�[�̓��͏�Ԃ��擾
  float GetRightTrigger(int _Index, float _DeadZone)const;
public:
  //  �R���g���[����U�������܂�
  void SetVibration(int _Index, float _Speed)const;
  //  �R���g���[���̐U�����~�߂܂�
  void StopVibration(int _Index)const;
public:
  //  ��Ԃ̍X�V
  void Update();
  //  ���
  ~IXInput();
};
