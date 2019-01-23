#pragma once
#include "IMouse.hpp"

class CMouse : public IMouse
{
  //  使用ボタン数
  static constexpr int kButtonNum = 5;
private:
  //  入力状態
  InputState InputStatus_[kButtonNum];
  //  座標
  hdx::int2 Pos_;
  //  移動量
  hdx::int2 Delta_;
  //  ホイール移動量
  int Wheel_;
  //  画面解像度
  hdx::float2 DpiScale_;
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

  int GetWheel()const override
  {
    return Wheel_; 
  }

  void SetPos(const hdx::int2& _Pos)override;

  void SetWheel(int _Wheel)override
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

    //  何も押されていない
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

    //  何も押されていない
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

    //  何も離されていない
    return false;
  }
};
