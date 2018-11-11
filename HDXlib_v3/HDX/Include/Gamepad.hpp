#pragma once
#include "Button.hpp"
#include "Type2.hpp"

#include <Windows.h>

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    class Gamepad
    {
      const int Index_;
    public:
      static constexpr int kMaxButtonNum = 32;
    public:
      //  ゲームパッドを作成
      //  _Index:ゲームパッドの番号
      constexpr Gamepad(int _Index)noexcept
        : Index_(_Index)
      {

      }
    public:
      //  接続されているならtrueを返す
      operator bool()const { return isConnect(); }
    public:
      //  ボタンを取得
      //  _Number:ボタン番号
      Button GetButton(int _Number)const;
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
