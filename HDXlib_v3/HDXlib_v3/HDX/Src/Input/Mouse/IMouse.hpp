#pragma once
#include "../InputState.hpp"
#include "../../../Include/Type2.hpp"

//  �}�E�X
class IMouse
{
  //  �g�p�{�^����
  static constexpr int kButtonNum = 5;
private:
  //  ���͏��
  InputState InputStatus_[kButtonNum];
  //  ���W
  hdx::int2 Pos_;
  //  �ړ���
  hdx::int2 Delta_;
  //  �z�C�[���ړ���
  int Wheel_;
private:
  bool isWithinRange(int _Number)const
  {
    return (0 <= _Number && _Number < kButtonNum);
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
  //  ���W���擾
  const hdx::int2& GetPos()const { return Pos_; }
  //  �ړ��ʂ��擾
  const hdx::int2& GetDelta()const { return Delta_; }
  //  �z�C�[���ړ��ʂ��擾
  int GetWheel()const { return Wheel_; }
public:
  //  ���W��ύX
  void SetPos(const hdx::int2& _Pos);
  //  �z�C�[���ړ��ʂ�ύX
  void SetWheel(int _Wheel) { Wheel_ = _Wheel; }
public:
  //  �����̃{�^����������Ă����true��Ԃ�
  bool AnyButtonPress()const
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }
  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool AnyButtonPressed()const
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }
  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool AnyButtonReleased()const
  {
    for (int i = 0; i < kButtonNum; ++i)
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
  IMouse() = default;
  //  ��Ԃ̍X�V
  void Update();
};
