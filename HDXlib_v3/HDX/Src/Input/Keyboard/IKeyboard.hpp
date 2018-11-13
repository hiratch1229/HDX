#pragma once
#include "../InputState.hpp"

//  �L�[�{�[�h
class IKeyboard
{
  //  �g�p�L�[��
  static constexpr int kKeyNum = 256;
private:
  InputState InputStatus_[kKeyNum];
private:
  bool isWithinRange(int _Number)const
  {
    return (0 <= _Number && _Number < kKeyNum);
  }
public:
  //  ������Ă���Ȃ�true��Ԃ�
  bool Press(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Press() : false;
  }
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Pressed(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Pressed() : false;
  }
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Released(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Released() : false;
  }
  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool Release(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Release() : false;
  }
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
