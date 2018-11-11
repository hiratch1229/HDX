#pragma once
#include "Button.hpp"
#include "Type2.hpp"

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    //  マウス
    namespace Mouse
    {
      //  左 ボタン
      constexpr Button ButtonLeft{ detail::InputDevice::Mouse, 0 };
      //  中(ホイール) ボタン
      constexpr Button ButtonCenter{ detail::InputDevice::Mouse, 1 };
      //  右 ボタン
      constexpr Button ButtonRight{ detail::InputDevice::Mouse, 2 };
      //  X1(戻る) ボタン
      constexpr Button ButtonX1{ detail::InputDevice::Mouse, 3 };
      //  X2(進む) ボタン
      constexpr Button ButtonX2{ detail::InputDevice::Mouse, 4 };

      //  座標を取得
      int2 GetPos();
      //  座標を変更
      void SetPos(const hdx::int2& _Pos);
      //  移動量を取得
      int2 GetDelta();
      //  ホイール移動量を取得
      //  正の数：奥,負の数：手前
      int2 GetWheel();

      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress();
      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed();
      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased();
    };
  }
}
