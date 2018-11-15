#pragma once
#include "../InputState.hpp"

//  キーボード
class IKeyboard
{
  //  使用キー数
  static constexpr int kKeyNum = 256;
private:
  InputState InputStatus_[kKeyNum];
private:
  bool isWithinRange(int _Number)const
  {
    return (0 <= _Number && _Number < kKeyNum);
  }
public:
  //  押されているならtrueを返す
  bool Press(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Press() : false;
  }
  //  押された瞬間ならtrueを返す
  bool Pressed(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Pressed() : false;
  }
  //  離された瞬間ならtrueを返す
  bool Released(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Released() : false;
  }
  //  押されていないならtrueを返す
  bool Release(int _Number)const
  {
    return isWithinRange(_Number) ? InputStatus_[_Number].Release() : false;
  }
public:
  //  何かのキーが押されていればtrueを返す
  bool AnyKeyPress()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }
  //  何かのキーが押されたならtrueを返す
  bool AnyKeyPressed()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }
  //  何かのキーが離されたならtrueを返す
  bool AnyKeyReleased()const
  {
    for (int i = 0; i < kKeyNum; ++i)
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
  IKeyboard() = default;
  //  状態の更新
  void Update();
};
