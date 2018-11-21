#include "../../../Include/Gamepad.hpp"

#include "../../Engine.hpp"
#include "../../Input/Gamepad/IGamepad.hpp"

#include "../../../Include/Constants.hpp"

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    //  ボタンを取得
    Button Gamepad::GetButton(int _Number)const
    {
      return Engine::Get<IGamepad>()->GetButton(Index_, _Number);
    }

    //  左スティックの入力状態を取得
    float2 Gamepad::GetLeftStick(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetLeftStick(Index_, _DeadZone);
    }

    //  右スティックの入力状態を取得
    float2 Gamepad::GetRightStick(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetRightStick(Index_, _DeadZone);
    }

    //  左トリガーの入力状態を取得
    float Gamepad::GetLeftTrigger(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetLeftTrigger(Index_, _DeadZone);
    }

    //  右トリガーの入力状態を取得
    float Gamepad::GetRightTrigger(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetRightTrigger(Index_, _DeadZone);
    }

    //  接続されているか確認
    bool Gamepad::isConnect()const
    {
      return Engine::Get<IGamepad>()->isConnect(Index_);
    }

    //  ボタンの数を取得
    int Gamepad::GetButtonNum()const
    {
      return Engine::Get<IGamepad>()->GetButtonNum(Index_);
    }

    //  コントローラを振動させます
    void Gamepad::SetVibration(float _Speed)const
    {
      return Engine::Get<IGamepad>()->SetVibration(Index_, _Speed);
    }

    //  コントローラの振動を止めます
    void Gamepad::StopVibration()const
    {
      return Engine::Get<IGamepad>()->StopVibration(Index_);
    }
  }
}
