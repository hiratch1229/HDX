#include "../../Input/Mouse/IMouse.hpp"
#include "../../Input/InputState.hpp"

#include <Windows.h>

namespace detail
{
  //  初期化
  IMouse::IMouse()
  {
    InputStatus_ = new InputState[kButtonNum];

    for (int i = 0; i < kButtonNum; ++i)
    {
      InputStatus_[i] = InputState::Release;
    }
  }

  //  更新
  void IMouse::Update()
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      //  状態の補間
      {
        //  押した瞬間
        if (InputStatus_[i] == InputState::Pressed)
        {
          InputStatus_[i] = InputState::Press;
        }
        //  離した瞬間
        else if (InputStatus_[i] == InputState::Released)
        {
          InputStatus_[i] = InputState::Release;
        }
      }
    }

    //  移動量を0にする
    Delta_ = { 0,0 };

    //  カーソルの移動量と座標を保存
    {
      //  現在のカーソルの位置
      POINT Point;
      GetCursorPos(&Point);

      //  現在のカーソルの位置
      const hdx::int2 CursorPos = { static_cast<int>(Point.x), static_cast<int>(Point.y) };

      //  移動量を保存
      Delta_ = CursorPos - Pos_;

      //  座標を保存
      Pos_ = CursorPos;

      Wheel_ = 0;
    }
  }

  //  解放
  IMouse::~IMouse()
  {
    delete[] InputStatus_;
    InputStatus_ = nullptr;
  }


  //--------------------------------------------------

  //  ボタンが押された時の処理
  void IMouse::ButtonPressed(MouseButtons Button)
  {
    if (InputStatus_[static_cast<int>(Button)] == InputState::Release)
    {
      InputStatus_[static_cast<int>(Button)] = InputState::Pressed;
    }
  }

  //  ボタンが離された時の処理
  void IMouse::ButtonReleased(MouseButtons Button)
  {
    if (InputStatus_[static_cast<int>(Button)] == InputState::Press)
    {
      InputStatus_[static_cast<int>(Button)] = InputState::Released;
    }
  }

  //  押されているならtrueを返す
  bool IMouse::Press(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Press || InputStatus_[_Number] == InputState::Pressed;
  }

  //  押された瞬間ならtrueを返す
  bool IMouse::Pressed(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Pressed;
  }

  //  離された瞬間ならtrueを返す
  bool IMouse::Released(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Released;
  }

  //  押されていないならtrueを返す
  bool IMouse::Release(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Release || InputStatus_[_Number] == InputState::Released;
  }

  //  座標を取得
  hdx::int2 IMouse::GetPos()const
  {
    return Pos_;
  }

  //  座標を変更
  void IMouse::SetPos(const hdx::int2& _Pos)
  {
    //  ウィンドウの中心にカーソルをセット
    SetCursorPos(_Pos.X, _Pos.Y);
  }

  //  移動量を取得
  hdx::int2 IMouse::GetDelta()const
  {
    return Delta_;
  }

  //  ホイール移動量を取得
  int IMouse::GetWheel()const
  {
    return Wheel_;
  }

  //  ホイール移動量を変更
  void IMouse::SetWheel(int _Wheel)
  {
    Wheel_ = _Wheel;
  }

  //  何かのボタンが押されていればtrueを返す
  bool IMouse::AnyButtonPress()const
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }

  //  何かのボタンが押されたならtrueを返す
  bool IMouse::AnyButtonPressed()const
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }

  //  何かのボタンが離されたならtrueを返す
  bool IMouse::AnyButtonReleased()const
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Released(i))
      {
        return true;
      }
    }

    //  何も離されていない
    return false;
  }
}
