#pragma once
#include "Button.hpp"

//  ライブラリ
namespace hdx
{
  struct int2;

  //  入力系
  namespace Input
  {
    //  マウス
    class Mouse
    {
    public:
      //  使うボタン
      enum Buttons
      {
        Left,
        Middle,
        Right,
        X1,
        X2
      };
    public:
      //  マウスを作成
      constexpr Mouse()
        : ButtonLeft(InputDevice::Mouse, Buttons::Left),
        ButtonCenter(InputDevice::Mouse, Buttons::Middle),
        ButtonRight(InputDevice::Mouse, Buttons::Right),
        ButtonX1(InputDevice::Mouse, Buttons::X1),
        ButtonX2(InputDevice::Mouse, Buttons::X2)
      {

      }
    public:
      //  左 ボタン
      const Button ButtonLeft;
      //  中(ホイール) ボタン
      const Button ButtonCenter;
      //  右 ボタン
      const Button ButtonRight;
      //  X1(戻る) ボタン
      const Button ButtonX1;
      //  X2(進む) ボタン
      const Button ButtonX2;
    public:
      //  座標を取得
      const int2& GetPos()const;
      //  座標を変更
      void SetPos(const int2& _Pos)const;
      //  移動量を取得
      const int2& GetDelta()const;
      //  ホイール移動量を取得
      //  正の数：奥,負の数：手前
      int GetWheel()const;
    public:
      //  何かのボタンが押されていればtrueを返す
      bool AnyButtonPress()const;
      //  何かのボタンが押されたならtrueを返す
      bool AnyButtonPressed()const;
      //  何かのボタンが離されたならtrueを返す
      bool AnyButtonReleased()const;
    };
  }
}
