#include "../../../Include/Mouse.hpp"

#include "../../Engine.hpp"
#include "../../Input/Mouse/IMouse.hpp"

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    //  座標を取得
    const int2& Mouse::GetPos()const
    {
      return Engine::Get<IMouse>()->GetPos();
    }

    //  座標を変更
    void Mouse::SetPos(const int2& _Pos)const
    {
      Engine::Get<IMouse>()->SetPos(_Pos);
    }

    //  移動量を取得
    const int2& Mouse::GetDelta()const
    {
      return Engine::Get<IMouse>()->GetDelta();
    }

    //  ホイール移動量を取得
    int Mouse::GetWheel()const
    {
      return Engine::Get<IMouse>()->GetWheel();
    }

    //  何かのボタンが押されていればtrueを返す
    bool Mouse::AnyButtonPress()const
    {
      return Engine::Get<IMouse>()->AnyButtonPress();
    }

    //  何かのボタンが押されたならtrueを返す
    bool Mouse::AnyButtonPressed()const
    {
      return Engine::Get<IMouse>()->AnyButtonPressed();
    }

    //  何かのボタンが離されたならtrueを返す
    bool Mouse::AnyButtonReleased()const
    {
      return Engine::Get<IMouse>()->AnyButtonReleased();
    }
  }
}
