#include "Include/Mouse.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/Mouse/IMouse.hpp"

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
      const int2& GetPos()
      {
        return Engine::Get<IMouse>()->GetPos();
      }

      //  座標を変更
      void SetPos(const int2& _Pos)
      {
        Engine::Get<IMouse>()->SetPos(_Pos);
      }

      //  移動量を取得
      const int2& GetDelta()
      {
        return Engine::Get<IMouse>()->GetDelta();
      }

      //  ホイール移動量を取得
      const int2& GetWheel()
      {
        return Engine::Get<IMouse>()->GetWheel();
      }

      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress()
      {
        return Engine::Get<IMouse>()->AnyButtonPress();
      }

      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed()
      {
        return Engine::Get<IMouse>()->AnyButtonPressed();
      }

      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased()
      {
        return Engine::Get<IMouse>()->AnyButtonReleased();
      }
    }
  }
}
