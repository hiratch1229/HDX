#include "Include/XInput.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/XInput/IXInput.hpp"

#include "Include/Gamepad.hpp"

namespace hdx
{
  namespace Input
  {
    //  左スティックの入力状態を取得
    float2 XInput::GetLeftStick(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetLeftStick(Index_, _DeadZone);
    }

    //  右スティックの入力状態を取得
    float2 XInput::GetRightStick(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetRightStick(Index_, _DeadZone);
    }
    //  左トリガーの入力状態を取得
    float XInput::GetLeftTrigger(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetLeftTrigger(Index_, _DeadZone);
    }
    //  右トリガーの入力状態を取得
    float XInput::GetRightTrigger(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetRightTrigger(Index_, _DeadZone);
    }
    //  何かのボタンが押されていればtrueを返す
    bool XInput::AnyButtonPress()const
    {
      return Engine::Get<IXInput>()->AnyButtonPress(Index_);
    }
    //  何かのボタンが押されたならtrueを返す
    bool XInput::AnyButtonPressed()const
    {
      return Engine::Get<IXInput>()->AnyButtonPressed(Index_);
    }
    //  何かのボタンが離されたならtrueを返す
    bool XInput::AnyButtonReleased()const
    {
      return Engine::Get<IXInput>()->AnyButtonReleased(Index_);
    }
    //  接続されているか確認
    bool XInput::isConnect()const
    {
      return Engine::Get<IXInput>()->isConnect(Index_);
    }
    //  コントローラを振動させます
    void XInput::SetVibration(float _Speed)const
    {
      return Engine::Get<IXInput>()->SetVibration(Index_, _Speed);
    }
    //  コントローラの振動を止めます
    void XInput::StopVibration()const
    {
      return Engine::Get<IXInput>()->StopVibration(Index_);
    }
  }
}