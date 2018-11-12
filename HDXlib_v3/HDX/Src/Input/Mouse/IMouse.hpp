#pragma once
#include "../InputState.hpp"
#include "../../../Include/Type2.hpp"

//  マウス
class IMouse
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
public:
  //  押されているならtrueを返す
  bool Press(int _Number)const { return InputStatus_[_Number].Press(); }
  //  押された瞬間ならtrueを返す
  bool Pressed(int _Number)const { return InputStatus_[_Number].Pressed(); }
  //  離された瞬間ならtrueを返す
  bool Released(int _Number)const { return InputStatus_[_Number].Released(); }
  //  押されていないならtrueを返す
  bool Release(int _Number)const { return InputStatus_[_Number].Release(); }
public:
  //  座標を取得
  const hdx::int2& GetPos()const { return Pos_; }
  //  移動量を取得
  const hdx::int2& GetDelta()const { return Delta_; }
  //  ホイール移動量を取得
  int GetWheel()const { return Wheel_; }
public:
  //  座標を変更
  void SetPos(const hdx::int2& _Pos);
  //  ホイール移動量を変更
  void SetWheel(int _Wheel) { Wheel_ = _Wheel; }
public:
  //  何かのボタンが押されていればtrueを返す
  bool AnyButtonPress()const
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
  //  何かのボタンが押されたならtrueを返す
  bool AnyButtonPressed()const
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
  //  何かのボタンが離されたならtrueを返す
  bool AnyButtonReleased()const
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
public:
  //  初期化
  IMouse() = default;
  //  状態の更新
  void Update();
};
