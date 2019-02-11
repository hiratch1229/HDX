#pragma once
#include "Button.hpp"
#include "Type2.hpp"
#include "Types.hpp"

namespace hdx
{
  namespace Input
  {
    class Gamepad
    {
      const int Index_;
    public:
      enum class Buttons
      {
        Up,
        Down,
        Left,
        Right,
      };
      enum class ButtonsForXInput
      {
        Start = 4,
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
      enum class ButtonsForPS
      {
        Square = 4,
        X,
        Circle,
        Triangle,
        L1,
        R1,
        L2,
        R2,
        Share,
        Options,
        L3,
        R3,
        PS,
        TouchPad,
      };
    public:
      static constexpr int kMaxButtonNum = 32;
    public:
      //  ゲームパッドを作成
      //  _Index:ゲームパッドの番号
      constexpr Gamepad(int _Index)noexcept : Index_(_Index) {}
    public:
      //  接続されているならtrueを返す
      operator bool()const { return isConnect(); }
    public:
      constexpr bool operator==(const Gamepad& _Gamepad)const { return Index_ == _Gamepad.Index_; }
      constexpr bool operator!=(const Gamepad& _Gamepad)const { return !((*this) == _Gamepad); }
    public:
      //  ボタンを取得
      //  _Number:ボタン番号
      Button GetButton(UINT _Number)const;
      Button GetButton(Buttons _Number)const { return GetButton(static_cast<UINT>(_Number)); }
      Button GetButton(ButtonsForXInput _Number)const { return GetButton(static_cast<UINT>(_Number)); }
      Button GetButton(ButtonsForPS _Number)const { return GetButton(static_cast<UINT>(_Number)); }
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
      //  ボタンの数を取得
      int GetButtonNum()const;
      //  コントローラを振動させます
      //  0は停止、1は最大速度
      void SetVibration(float _Speed)const;
      //  コントローラの振動を止めます
      void StopVibration()const;
    };
  }
}
