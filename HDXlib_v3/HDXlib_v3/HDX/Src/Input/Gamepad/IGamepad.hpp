#pragma once
#include "../../../Include/Button.hpp"
#include "../../../Include/Type2.hpp"
#include "../../../Include/Constants.hpp"

#include "../InputState.hpp"

class IGamepad
{
private:
  enum class PovDirection
  {
    Up,
    Down,
    Left,
    Right,

    Num
  };
  static constexpr int kPovDirectionNum = static_cast<int>(PovDirection::Num);
  static constexpr int kButtonNum = 32 + kPovDirectionNum;
  static constexpr int kControllerNum = hdx::ControllerMaxNum;
private:
  struct Status
  {
    //  �ڑ����
    bool isConnect = false;
    //  ���͏��
    InputState* InputStatus;
    //  ���̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 LeftStick;
    //  �E�̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 RightStick;
    //  ���̃g���K�[�̓��͏��
    float LeftTrigger;
    //  �E�̃g���K�[�̓��͏��
    float RightTrigger;
    //  �{�^����
    int ButtonNum = 0;
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
    return (Status_[_Index].isConnect && 0 <= _Number && _Number < Status_[_Index].ButtonNum && 0 <= _Index && _Index < kControllerNum);
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
  bool isConnect(int _Index)const
  {
    return isWithinRange(_Index) ? Status_[_Index].isConnect : false;
  }
  //  �{�^���̐����擾
  int GetButtonNum(int _Index)const
  {
    return isWithinRange(_Index) ? Status_[_Index].ButtonNum : 0;
  }
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
  //  �{�^�����擾
  hdx::Button GetButton(int _Index, int _Number)const
  {
    return isWithinRange(_Index) ? hdx::Button(hdx::InputDevice::Gamepad, _Number, _Index) : hdx::Button();
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
  //  ������
  IGamepad();
  //  ��Ԃ̍X�V
  void Update();
  //  ���
  ~IGamepad();
};
