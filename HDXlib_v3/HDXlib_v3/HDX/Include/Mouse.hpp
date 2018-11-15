#pragma once
#include "Button.hpp"

//  ���C�u����
namespace hdx
{
  struct int2;

  //  ���͌n
  namespace Input
  {
    //  �}�E�X
    class Mouse
    {
    public:
      //  �g���{�^��
      enum Buttons
      {
        Left,
        Middle,
        Right,
        X1,
        X2
      };
    public:
      //  �}�E�X���쐬
      constexpr Mouse()
        : ButtonLeft(InputDevice::Mouse, Buttons::Left),
        ButtonCenter(InputDevice::Mouse, Buttons::Middle),
        ButtonRight(InputDevice::Mouse, Buttons::Right),
        ButtonX1(InputDevice::Mouse, Buttons::X1),
        ButtonX2(InputDevice::Mouse, Buttons::X2)
      {

      }
    public:
      //  �� �{�^��
      const Button ButtonLeft;
      //  ��(�z�C�[��) �{�^��
      const Button ButtonCenter;
      //  �E �{�^��
      const Button ButtonRight;
      //  X1(�߂�) �{�^��
      const Button ButtonX1;
      //  X2(�i��) �{�^��
      const Button ButtonX2;
    public:
      //  ���W���擾
      const int2& GetPos()const;
      //  ���W��ύX
      void SetPos(const int2& _Pos)const;
      //  �ړ��ʂ��擾
      const int2& GetDelta()const;
      //  �z�C�[���ړ��ʂ��擾
      //  ���̐��F��,���̐��F��O
      int GetWheel()const;
    public:
      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress()const;
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed()const;
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased()const;
    };
  }
}
