#include "../../../Include/Mouse.hpp"

#include "../../Engine/Engine.hpp"
#include "../../Input/Mouse/IMouse.hpp"

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
        return GetMouse()->GetPos();
      }

      //  座標を変更
      void SetPos(const hdx::int2& _Pos)
      {
        GetMouse()->SetPos(_Pos);
      }

      //  移動量を取得
      int2 GetDelta()
      {
        return GetMouse()->GetDelta();
      }

      //  ホイール移動量を取得
      int2 GetWheel()
      {
        return GetMouse()->GetWheel();
      }

      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress()
      {
        return GetMouse()->AnyButtonPress();
      }

      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed()
      {
        return GetMouse()->AnyButtonPressed();
      }

      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased()
      {
        return GetMouse()->AnyButtonReleased();
      }
    }
  }
}
