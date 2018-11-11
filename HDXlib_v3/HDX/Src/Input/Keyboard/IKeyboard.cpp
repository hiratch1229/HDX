#include "IKeyboard.hpp"

#include "../../Input/InputState.hpp"

#include <Windows.h>

namespace detail
{
  //  ������
  IKeyboard::IKeyboard()
  {
    InputStatus_ = new InputState[kKeyNum];

    for (int i = 0; i < kKeyNum; ++i)
    {
      InputStatus_[i] = InputState::Release;
    }
  }

  //  ��Ԃ̍X�V
  void IKeyboard::Update()
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      //  ��Ԃ̕��
      {
        //  �������u��
        if (InputStatus_[i] == InputState::Pressed)
        {
          InputStatus_[i] = InputState::Press;
        }
        //  �������u��
        else if (InputStatus_[i] == InputState::Released)
        {
          InputStatus_[i] = InputState::Release;
        }
      }

      //  ��Ԃ��擾
      {
        if (GetKeyState(kKeyboardVirtualKeyCode[i]) & 0x8000)
        {
          //  �������u��
          if (InputStatus_[i] == InputState::Release)
          {
            InputStatus_[i] = InputState::Pressed;
          }
        }
        else
        {
          //  �������u��
          if (InputStatus_[i] == InputState::Press)
          {
            InputStatus_[i] = InputState::Released;
          }
        }
      }
    }
  }

  //  ���
  IKeyboard::~IKeyboard()
  {
    delete[] InputStatus_;
    InputStatus_ = nullptr;
  }


  //--------------------------------------------------

  //  ������Ă���Ȃ�true��Ԃ�
  bool IKeyboard::Press(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Press || InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IKeyboard::Pressed(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IKeyboard::Released(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Released;
  }

  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool IKeyboard::Release(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Release || InputStatus_[_Number] == InputState::Released;
  }

  //  �����̃L�[��������Ă����true��Ԃ�
  bool IKeyboard::AnyKeyPress()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
  bool IKeyboard::AnyKeyPressed()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
  bool IKeyboard::AnyKeyReleased()const
  {
    for (int i = 0; i < kKeyNum; ++i)
    {
      if (Released(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }
}
