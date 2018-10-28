#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/Input/InputState.hpp>

#include <Windows.h>

namespace detail
{
  //  初期化
  IKeyboard::IKeyboard()
  {
    InputStatus_ = new InputState[kKeyNum];

    for (int i = 0; i < kKeyNum; ++i)
    {
      InputStatus_[i] = InputState::Release;
    }
  }

  //  状態の更新
  void IKeyboard::Update()
  {
    for (int i = 0; i < kKeyNum; ++i)
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

      //  状態を取得
      {
        if (GetKeyState(kKeyboardVirtualKeyCode[i]) & 0x8000)
        {
          //  押した瞬間
          if (InputStatus_[i] == InputState::Release)
          {
            InputStatus_[i] = InputState::Pressed;
          }
        }
        else
        {
          //  離した瞬間
          if (InputStatus_[i] == InputState::Press)
          {
            InputStatus_[i] = InputState::Released;
          }
        }
      }
    }
  }

  //  解放
  IKeyboard::~IKeyboard()
  {
    delete[] InputStatus_;
    InputStatus_ = nullptr;
  }


  //--------------------------------------------------

  //  押されているならtrueを返す
  bool IKeyboard::Press(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Press || InputStatus_[_Number] == InputState::Pressed;
  }

  //  押された瞬間ならtrueを返す
  bool IKeyboard::Pressed(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Pressed;
  }

  //  離された瞬間ならtrueを返す
  bool IKeyboard::Released(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Released;
  }

  //  押されていないならtrueを返す
  bool IKeyboard::Release(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Release || InputStatus_[_Number] == InputState::Released;
  }

  //  何かのキーが押されていればtrueを返す
  bool IKeyboard::AnyKeyPress()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }

  //  何かのキーが押されたならtrueを返す
  bool IKeyboard::AnyKeyPressed()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }

  //  何かのキーが離されたならtrueを返す
  bool IKeyboard::AnyKeyReleased()const
  {
    for (int i = 0; i < kKeyNum; ++i)
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
