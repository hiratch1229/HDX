#pragma once
#include "Button.hpp"
#include "Type2.hpp"

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  �}�E�X
    namespace Mouse
    {
      //  �g���{�^��
      enum Buttons
      {
        Left,
        Middle,
        Right,
        X1,
        X2
      };

      //  �� �{�^��
      constexpr Button ButtonLeft{ InputDevice::Mouse, Buttons::Left };
      //  ��(�z�C�[��) �{�^��
      constexpr Button ButtonCenter{ InputDevice::Mouse, Buttons::Middle };
      //  �E �{�^��
      constexpr Button ButtonRight{ InputDevice::Mouse, Buttons::Right };
      //  X1(�߂�) �{�^��
      constexpr Button ButtonX1{ InputDevice::Mouse, Buttons::X1 };
      //  X2(�i��) �{�^��
      constexpr Button ButtonX2{ InputDevice::Mouse, Buttons::X2 };

      //  ���W���擾
      const int2& GetPos();
      //  ���W��ύX
      void SetPos(const int2& _Pos);
      //  �ړ��ʂ��擾
      const int2& GetDelta();
      //  �z�C�[���ړ��ʂ��擾
      //  ���̐��F��,���̐��F��O
      const int2& GetWheel();

      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress();
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed();
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased();
    }
  }
}
