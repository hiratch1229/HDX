#include <HDX/Input/Mouse/Mouse.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/System/System.hpp>

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    //  マウス
    namespace Mouse
    {
      //  座標を取得
      int2 GetPos()
      {
        return detail::System::Get()->GetMouse()->GetPos();
      }

      //  座標を変更
      void SetPos(const hdx::int2& _Pos)
      {
        detail::System::Get()->GetMouse()->SetPos(_Pos);
      }

      //  移動量を取得
      int2 GetDelta()
      {
        return detail::System::Get()->GetMouse()->GetDelta();
      }

      //  ホイール移動量を取得
      int2 GetWheel()
      {
        return detail::System::Get()->GetMouse()->GetWheel();
      }

      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress()
      {
        return detail::System::Get()->GetMouse()->AnyButtonPress();
      }

      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed()
      {
        return detail::System::Get()->GetMouse()->AnyButtonPressed();
      }

      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased()
      {
        return detail::System::Get()->GetMouse()->AnyButtonReleased();
      }
    }
  }
}
