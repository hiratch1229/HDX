#include "IKeyboard.hpp"

#include "../../Input/InputState.hpp"

#include <Windows.h>

namespace detail
{
  //  ‰Šú‰»
  IKeyboard::IKeyboard()
  {
    InputStatus_ = new InputState[kKeyNum];

    for (int i = 0; i < kKeyNum; ++i)
    {
      InputStatus_[i] = InputState::Release;
    }
  }

  //  ó‘Ô‚ÌXV
  void IKeyboard::Update()
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      //  ó‘Ô‚Ì•âŠÔ
      {
        //  ‰Ÿ‚µ‚½uŠÔ
        if (InputStatus_[i] == InputState::Pressed)
        {
          InputStatus_[i] = InputState::Press;
        }
        //  —£‚µ‚½uŠÔ
        else if (InputStatus_[i] == InputState::Released)
        {
          InputStatus_[i] = InputState::Release;
        }
      }

      //  ó‘Ô‚ğæ“¾
      {
        if (GetKeyState(kKeyboardVirtualKeyCode[i]) & 0x8000)
        {
          //  ‰Ÿ‚µ‚½uŠÔ
          if (InputStatus_[i] == InputState::Release)
          {
            InputStatus_[i] = InputState::Pressed;
          }
        }
        else
        {
          //  —£‚µ‚½uŠÔ
          if (InputStatus_[i] == InputState::Press)
          {
            InputStatus_[i] = InputState::Released;
          }
        }
      }
    }
  }

  //  ‰ğ•ú
  IKeyboard::~IKeyboard()
  {
    delete[] InputStatus_;
    InputStatus_ = nullptr;
  }


  //--------------------------------------------------

  //  ‰Ÿ‚³‚ê‚Ä‚¢‚é‚È‚çtrue‚ğ•Ô‚·
  bool IKeyboard::Press(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Press || InputStatus_[_Number] == InputState::Pressed;
  }

  //  ‰Ÿ‚³‚ê‚½uŠÔ‚È‚çtrue‚ğ•Ô‚·
  bool IKeyboard::Pressed(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Pressed;
  }

  //  —£‚³‚ê‚½uŠÔ‚È‚çtrue‚ğ•Ô‚·
  bool IKeyboard::Released(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Released;
  }

  //  ‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢‚È‚çtrue‚ğ•Ô‚·
  bool IKeyboard::Release(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Release || InputStatus_[_Number] == InputState::Released;
  }

  //  ‰½‚©‚ÌƒL[‚ª‰Ÿ‚³‚ê‚Ä‚¢‚ê‚Îtrue‚ğ•Ô‚·
  bool IKeyboard::AnyKeyPress()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  ‰½‚à‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
    return false;
  }

  //  ‰½‚©‚ÌƒL[‚ª‰Ÿ‚³‚ê‚½‚È‚çtrue‚ğ•Ô‚·
  bool IKeyboard::AnyKeyPressed()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  ‰½‚à‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
    return false;
  }

  //  ‰½‚©‚ÌƒL[‚ª—£‚³‚ê‚½‚È‚çtrue‚ğ•Ô‚·
  bool IKeyboard::AnyKeyReleased()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Released(i))
      {
        return true;
      }
    }

    //  ‰½‚à—£‚³‚ê‚Ä‚¢‚È‚¢
    return false;
  }
}
