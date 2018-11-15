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
    //  接続状態
    bool isConnect = false;
    //  入力状態
    InputState* InputStatus;
    //  左のアナログスティックの入力状態
    hdx::float2 LeftStick;
    //  右のアナログスティックの入力状態
    hdx::float2 RightStick;
    //  左のトリガーの入力状態
    float LeftTrigger;
    //  右のトリガーの入力状態
    float RightTrigger;
    //  ボタン数
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
  //  押されているならtrueを返す
  bool Press(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Press() : false;
  }
  //  押された瞬間ならtrueを返す
  bool Pressed(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Pressed() : false;
  }
  //  離された瞬間ならtrueを返す
  bool Released(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Released() : false;
  }
  //  押されていないならtrueを返す
  bool Release(int _Number, int _Index)const
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Release() : false;
  }
public:
  //  接続されているか確認
  bool isConnect(int _Index)const
  {
    return isWithinRange(_Index) ? Status_[_Index].isConnect : false;
  }
  //  ボタンの数を取得
  int GetButtonNum(int _Index)const
  {
    return isWithinRange(_Index) ? Status_[_Index].ButtonNum : 0;
  }
public:
  //  何かのボタンが押されていればtrueを返す
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

    //  何も押されていない
    return false;
  }
  //  何かのボタンが押されたならtrueを返す
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

    //  何も押されていない
    return false;
  }
  //  何かのボタンが離されたならtrueを返す
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

    //  何も押されていない
    return false;
  }
public:
  //  ボタンを取得
  hdx::Button GetButton(int _Index, int _Number)const
  {
    return isWithinRange(_Index) ? hdx::Button(hdx::InputDevice::Gamepad, _Number, _Index) : hdx::Button();
  }
public:
  //  左スティックの入力状態を取得
  hdx::float2 GetLeftStick(int _Index, float _DeadZone)const;
  //  右スティックの入力状態を取得
  hdx::float2 GetRightStick(int _Index, float _DeadZone)const;
public:
  //  左トリガーの入力状態を取得
  float GetLeftTrigger(int _Index, float _DeadZone)const;
  //  右トリガーの入力状態を取得
  float GetRightTrigger(int _Index, float _DeadZone)const;
public:
  //  コントローラを振動させます
  void SetVibration(int _Index, float _Speed)const;
  //  コントローラの振動を止めます
  void StopVibration(int _Index)const;
public:
  //  初期化
  IGamepad();
  //  状態の更新
  void Update();
  //  解放
  ~IGamepad();
};
