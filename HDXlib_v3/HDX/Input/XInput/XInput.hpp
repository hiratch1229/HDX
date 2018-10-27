#pragma once
#include <HDX/Input/Button.hpp>
#include <HDX/Type2.hpp>

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    class XInput
    {
      const int Index_;
    public:
      //  ゲームパッドを作成
      //  _Index:ゲームパッドの番号
      constexpr XInput(int _Index)noexcept : Index_(_Index),
        ButtonUp({ detail::InputDevice::XInput, 0, _Index }),
        ButtonDown({ detail::InputDevice::XInput, 1, _Index }),
        ButtonLeft({ detail::InputDevice::XInput, 2, _Index }),
        ButtonRight({ detail::InputDevice::XInput, 3, _Index }),
        ButtonStart({ detail::InputDevice::XInput, 4, _Index }),
        ButtonSelect({ detail::InputDevice::XInput, 5, _Index }),
        ButtonLeftStick({ detail::InputDevice::XInput, 6, _Index }),
        ButtonRightStick({ detail::InputDevice::XInput, 7, _Index }),
        ButtonLB({ detail::InputDevice::XInput, 8, _Index }),
        ButtonRB({ detail::InputDevice::XInput, 9, _Index }),
        ButtonA({ detail::InputDevice::XInput, 10, _Index }),
        ButtonB({ detail::InputDevice::XInput, 11, _Index }),
        ButtonX({ detail::InputDevice::XInput, 12, _Index }),
        ButtonY({ detail::InputDevice::XInput, 13, _Index })
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
