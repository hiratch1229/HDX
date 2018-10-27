#include <HDX/Input/XInput/XInput.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/System/System.hpp>

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    //  左スティックの入力状態を取得
    float2 XInput::GetLeftStick(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetLeftStick(Index_, _DeadZone);
    }

    //  右スティックの入力状態を取得
    float2 XInput::GetRightStick(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetRightStick(Index_, _DeadZone);
    }
    //  左トリガーの入力状態を取得
    float XInput::GetLeftTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetLeftTrigger(Index_, _DeadZone);
    }
    //  右トリガーの入力状態を取得
    float XInput::GetRightTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetRightTrigger(Index_, _DeadZone);
    }
    //  接続されているか確認
    bool XInput::isConnect()const
    {
      return detail::System::Get()->GetXInput()->isConnect(Index_);
    }
    //  コントローラを振動させます
    void XInput::SetVibration(float _Speed)const
    {
      return detail::System::Get()->GetXInput()->SetVibration(Index_, _Speed);
    }
    //  コントローラの振動を止めます
    void XInput::StopVibration()const
    {
      return detail::System::Get()->GetXInput()->StopVibration(Index_);
    }
  }
}