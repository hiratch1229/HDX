#pragma once
#include "Button.hpp"
#include "Type2.hpp"

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    class XInput
    {
      //  使うボタン
      enum Buttons
      {
        Up,
        Down,
        Left,
        Right,
        Start,
        Back,
        LeftStick,
        RightStick,
        LeftShoulder,
        RightShoulder,
        A,
        B,
        X,
        Y,
      };
    private:
      const int Index_;
    public:
      //  ゲームパッドを作成
      //  _Index:ゲームパッドの番号
      constexpr XInput(int _Index)noexcept : Index_(_Index),
        ButtonUp(InputDevice::XInput, Buttons::Up, _Index),
        ButtonDown(InputDevice::XInput, Buttons::Down, _Index),
        ButtonLeft(InputDevice::XInput, Buttons::Left, _Index),
        ButtonRight(InputDevice::XInput, Buttons::Right, _Index),
        ButtonStart(InputDevice::XInput, Buttons::Start, _Index),
        ButtonSelect(InputDevice::XInput, Buttons::Back, _Index),
        ButtonLeftStick(InputDevice::XInput, Buttons::LeftStick, _Index),
        ButtonRightStick(InputDevice::XInput, Buttons::RightStick, _Index),
        ButtonLB(InputDevice::XInput, Buttons::LeftShoulder, _Index),
        ButtonRB(InputDevice::XInput, Buttons::RightShoulder, _Index),
        ButtonA(InputDevice::XInput, Buttons::A, _Index),
        ButtonB(InputDevice::XInput, Buttons::B, _Index),
        ButtonX(InputDevice::XInput, Buttons::X, _Index),
        ButtonY(InputDevice::XInput, Buttons::Y, _Index)
      {

      }
    public:
      //  十字キー↑ ボタン
      const Button ButtonUp;
      //  十字キー↓ ボタン
      const Button ButtonDown;
      //  十字キー← ボタン
      const Button ButtonLeft;
      //  十字キー→ ボタン
      const Button ButtonRight;
      //  Start ボタン
      const Button ButtonStart;
      //  Select(Back,Share) ボタン
      const Button ButtonSelect;
      //  左スティック押し込み ボタン
      const Button ButtonLeftStick;
      //  右スティック押し込み ボタン
      const Button ButtonRightStick;
      //  LB ボタン
      const Button ButtonLB;
      //  RB ボタン
      const Button ButtonRB;
      //  A ボタン
      const Button ButtonA;
      //  B ボタン
      const Button ButtonB;
      //  X ボタン
      const Button ButtonX;
      //  Y ボタン
      const Button ButtonY;
    public:
      //  接続されているならtrueを返す
      operator bool()const { return isConnect(); }
    public:
      constexpr bool operator==(const XInput& _XInput)const { return Index_ == _XInput.Index_; }
      constexpr bool operator!=(const XInput& _XInput)const { return !((*this) == _XInput); }
    public:
      //  左スティックの入力状態を取得
      //  -1~1の範囲で表現されてます
      float2 GetLeftStick(float _DeadZone = 0.0f)const;
      //  右スティックの入力状態を取得
      //  -1~1の範囲で表現されてます
      float2 GetRightStick(float _DeadZone = 0.0f)const;
      //  左トリガーの入力状態を取得
      //  0-1の範囲で表現されます
      float GetLeftTrigger(float _DeadZone = 0.0f)const;
      //  右トリガーの入力状態を取得
      //  0-1の範囲で表現されます
      float GetRightTrigger(float _DeadZone = 0.0f)const;
      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress()const;
      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed()const;
      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased()const;
      //  接続されているか確認
      //  接続中はtrue
      bool isConnect()const;
      //  コントローラを振動させます
      //  0は停止、1は最大速度
      void SetVibration(float _Speed)const;
      //  コントローラの振動を止めます
      void StopVibration()const;
    };
  }
}
