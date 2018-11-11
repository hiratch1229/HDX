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
      //  �� �{�^��
      constexpr Button ButtonLeft{ detail::InputDevice::Mouse, 0 };
      //  ��(�z�C�[��) �{�^��
      constexpr Button ButtonCenter{ detail::InputDevice::Mouse, 1 };
      //  �E �{�^��
      constexpr Button ButtonRight{ detail::InputDevice::Mouse, 2 };
      //  X1(�߂�) �{�^��
      constexpr Button ButtonX1{ detail::InputDevice::Mouse, 3 };
      //  X2(�i��) �{�^��
      constexpr Button ButtonX2{ detail::InputDevice::Mouse, 4 };

      //  ���W���擾
      int2 GetPos();
      //  ���W��ύX
      void SetPos(const hdx::int2& _Pos);
      //  �ړ��ʂ��擾
      int2 GetDelta();
      //  �z�C�[���ړ��ʂ��擾
      //  ���̐��F��,���̐��F��O
      int2 GetWheel();

      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress();
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed();
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased();
    };
  }
}
