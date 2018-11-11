#include "../../Input/Mouse/IMouse.hpp"
#include "../../Input/InputState.hpp"

#include <Windows.h>

namespace detail
{
  //  ������
  IMouse::IMouse()
  {
    InputStatus_ = new InputState[kButtonNum];

    for (int i = 0; i < kButtonNum; ++i)
    {
      InputStatus_[i] = InputState::Release;
    }
  }

  //  �X�V
  void IMouse::Update()
  {
    for (int i = 0; i < kButtonNum; ++i)
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
    }

    //  �ړ��ʂ�0�ɂ���
    Delta_ = { 0,0 };

    //  �J�[�\���̈ړ��ʂƍ��W��ۑ�
    {
      //  ���݂̃J�[�\���̈ʒu
      POINT Point;
      GetCursorPos(&Point);

      //  ���݂̃J�[�\���̈ʒu
      const hdx::int2 CursorPos = { static_cast<int>(Point.x), static_cast<int>(Point.y) };

      //  �ړ��ʂ�ۑ�
      Delta_ = CursorPos - Pos_;

      //  ���W��ۑ�
      Pos_ = CursorPos;

      Wheel_ = 0;
    }
  }

  //  ���
  IMouse::~IMouse()
  {
    delete[] InputStatus_;
    InputStatus_ = nullptr;
  }


  //--------------------------------------------------

  //  �{�^���������ꂽ���̏���
  void IMouse::ButtonPressed(MouseButtons Button)
  {
    if (InputStatus_[static_cast<int>(Button)] == InputState::Release)
    {
      InputStatus_[static_cast<int>(Button)] = InputState::Pressed;
    }
  }

  //  �{�^���������ꂽ���̏���
  void IMouse::ButtonReleased(MouseButtons Button)
  {
    if (InputStatus_[static_cast<int>(Button)] == InputState::Press)
    {
      InputStatus_[static_cast<int>(Button)] = InputState::Released;
    }
  }

  //  ������Ă���Ȃ�true��Ԃ�
  bool IMouse::Press(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Press || InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IMouse::Pressed(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Pressed;
  }

  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool IMouse::Released(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Released;
  }

  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool IMouse::Release(int _Number)const
  {
    return InputStatus_[_Number] == InputState::Release || InputStatus_[_Number] == InputState::Released;
  }

  //  ���W���擾
  hdx::int2 IMouse::GetPos()const
  {
    return Pos_;
  }

  //  ���W��ύX
  void IMouse::SetPos(const hdx::int2& _Pos)
  {
    //  �E�B���h�E�̒��S�ɃJ�[�\�����Z�b�g
    SetCursorPos(_Pos.X, _Pos.Y);
  }

  //  �ړ��ʂ��擾
  hdx::int2 IMouse::GetDelta()const
  {
    return Delta_;
  }

  //  �z�C�[���ړ��ʂ��擾
  int IMouse::GetWheel()const
  {
    return Wheel_;
  }

  //  �z�C�[���ړ��ʂ�ύX
  void IMouse::SetWheel(int _Wheel)
  {
    Wheel_ = _Wheel;
  }

  //  �����̃{�^����������Ă����true��Ԃ�
  bool IMouse::AnyButtonPress()const
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Press(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool IMouse::AnyButtonPressed()const
  {
    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Pressed(i))
      {
        return true;
      }
    }

    //  ����������Ă��Ȃ�
    return false;
  }

  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool IMouse::AnyButtonReleased()const
  {
    for (int i = 0; i < kButtonNum; ++i)
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
