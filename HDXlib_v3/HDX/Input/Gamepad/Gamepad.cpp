#include <HDX/Input/Gamepad/Gamepad.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/System/System.hpp>

//  ライブラリ
namespace hdx
{
  //入力系
  namespace Input
  {
    //  ボタンを取得
    Button Gamepad::GetButton(int _Number)const
    {
      return detail::System::Get()->GetGamepad()->GetButton(Index_, _Number);
    }

    //  左スティックの入力状態を取得
    float2 Gamepad::GetLeftStick(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetLeftStick(Index_, _DeadZone);
    }

    //  右スティックの入力状態を取得
    float2 Gamepad::GetRightStick(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetRightStick(Index_, _DeadZone);
    }

    //  左トリガーの入力状態を取得
    float Gamepad::GetLeftTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetLeftTrigger(Index_, _DeadZone);
    }

    //  右トリガーの入力状態を取得
    float Gamepad::GetRightTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetRightTrigger(Index_, _DeadZone);
    }

    //  接続されているか確認
    bool Gamepad::isConnect()const
    {
      return detail::System::Get()->GetGamepad()->isConnect(Index_);
    }

    //  コントローラを振動させます
    void Gamepad::SetVibration(float _Speed)const
    {
      return detail::System::Get()->GetGamepad()->SetVibration(Index_, _Speed);
    }

    //  コントローラの振動を止めます
    void Gamepad::StopVibration()const
    {
      return detail::System::Get()->GetGamepad()->StopVibration(Index_);
    }
  }
}
