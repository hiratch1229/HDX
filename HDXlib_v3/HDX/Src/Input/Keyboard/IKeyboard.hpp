#pragma once
#include "../InputState.hpp"

//  �L�[�{�[�h
class IKeyboard
{
  //  �g�p�L�[��
  static constexpr int kKeyNum = 256;
private:
  InputState InputStatus_[kKeyNum];
public:
  //  ������Ă���Ȃ�true��Ԃ�
  bool Press(int _Number)const { return InputStatus_[_Number].Press(); }
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Pressed(int _Number)const { return InputStatus_[_Number].Pressed(); }
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Released(int _Number)const { return InputStatus_[_Number].Released(); }
  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool Release(int _Number)const { return InputStatus_[_Number].Release(); }
public:
  //  �����̃L�[��������Ă����true��Ԃ�
  bool AnyKeyPress()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }
  //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
  bool AnyKeyPressed()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }
  //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
  bool AnyKeyReleased()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Released(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }
public:
  //  ������
  IKeyboard() = default;
  //  ��Ԃ̍X�V
  void Update();
};
