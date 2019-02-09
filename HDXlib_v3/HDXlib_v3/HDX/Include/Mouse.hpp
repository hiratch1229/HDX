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
      //  使うボタン
      enum Buttons
      {
        Left,
        Middle,
        Right,
        X1,
        X2
      };

      //  左 ボタン
      constexpr Button ButtonLeft{ InputDevice::Mouse, Buttons::Left };
      //  中(ホイール) ボタン
      constexpr Button ButtonCenter{ InputDevice::Mouse, Buttons::Middle };
      //  右 ボタン
      constexpr Button ButtonRight{ InputDevice::Mouse, Buttons::Right };
      //  X1(戻る) ボタン
      constexpr Button ButtonX1{ InputDevice::Mouse, Buttons::X1 };
      //  X2(進む) ボタン
      constexpr Button ButtonX2{ InputDevice::Mouse, Buttons::X2 };

      //  座標を取得
      const int2& GetPos();
      //  座標を変更
      void SetPos(const int2& _Pos);
      //  移動量を取得
      const int2& GetDelta();
      //  ホイール移動量を取得
      //  正の数：奥,負の数：手前
      const int2& GetWheel();

      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress();
      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed();
      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased();
    }
  }
}
