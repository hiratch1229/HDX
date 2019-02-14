#pragma once
#include "IMouse.hpp"

class CMouse : public IMouse
{
  //  �g�p�{�^����
  static constexpr int kButtonNum = 5;
private:
  //  ���͏��
  InputState InputStatus_[kButtonNum];
  //  ���W
  hdx::int2 Pos_ = hdx::int2(0, 0);
  //  �ړ���
  hdx::int2 Delta_ = hdx::int2(0, 0);
  //  �z�C�[���ړ���
  hdx::int2 Wheel_ = 0;
  //  ��ʉ𑜓x
  hdx::float2 DpiScale_ = hdx::float2(0.0f, 0.0f);
private:
  bool isWithinRange(int _Number)const
  {
    return (0 <= _Number && _Number < kButtonNum);
  }
public:
  CMouse();

  void Update()override;

  bool Press(int _Number)const override
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Press() : false;
  }

  bool Pressed(int _Number)const override
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Pressed() : false;
  }

  bool Released(int _Number)const override
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Released() : false;
  }

  bool Release(int _Number)const override
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Release() : false;
  }

  const hdx::int2& GetPos()const override
  {
    return Pos_;
  }

  const hdx::int2& GetDelta()const override
  {
    return Delta_;
  }

  const hdx::int2& GetWheel()const override
  {
    return Wheel_;
  }

  void SetPos(const hdx::int2& _Pos)override;

  void SetWheel(const hdx::int2& _Wheel)override
  {
    Wheel_ = _Wheel;
  }

  bool AnyButtonPress()const override
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

  bool AnyButtonPressed()const override
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

  bool AnyButtonReleased()const override
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
};