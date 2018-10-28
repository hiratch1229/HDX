#include <HDX/Input/Mouse/Mouse.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>

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
        return detail::Engine::GetMouse()->GetPos();
      }

      //  座標を変更
      void SetPos(const hdx::int2& _Pos)
      {
        detail::Engine::GetMouse()->SetPos(_Pos);
      }

      //  移動量を取得
      int2 GetDelta()
      {
        return detail::Engine::GetMouse()->GetDelta();
      }

      //  ホイール移動量を取得
      int2 GetWheel()
      {
        return detail::Engine::GetMouse()->GetWheel();
      }

      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress()
      {
        return detail::Engine::GetMouse()->AnyButtonPress();
      }

      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed()
      {
        return detail::Engine::GetMouse()->AnyButtonPressed();
      }

      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased()
      {
        return detail::Engine::GetMouse()->AnyButtonReleased();
      }
    }
  }
}
