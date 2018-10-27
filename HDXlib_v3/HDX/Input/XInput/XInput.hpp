#pragma once
#include <HDX/Input/Button.hpp>
#include <HDX/Type2.hpp>

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    class XInput
    {
      const int Index_;
    public:
      //  �Q�[���p�b�h���쐬
      //  _Index:�Q�[���p�b�h�̔ԍ�
      constexpr XInput(int _Index)noexcept : Index_(_Index),
        ButtonUp({ detail::InputDevice::XInput, 0, _Index }),
        ButtonDown({ detail::InputDevice::XInput, 1, _Index }),
        ButtonLeft({ detail::InputDevice::XInput, 2, _Index }),
        ButtonRight({ detail::InputDevice::XInput, 3, _Index }),
        ButtonStart({ detail::InputDevice::XInput, 4, _Index }),
        ButtonSelect({ detail::InputDevice::XInput, 5, _Index }),
        ButtonLeftStick({ detail::InputDevice::XInput, 6, _Index }),
        ButtonRightStick({ detail::InputDevice::XInput, 7, _Index }),
        ButtonLB({ detail::InputDevice::XInput, 8, _Index }),
        ButtonRB({ detail::InputDevice::XInput, 9, _Index }),
        ButtonA({ detail::InputDevice::XInput, 10, _Index }),
        ButtonB({ detail::InputDevice::XInput, 11, _Index }),
        ButtonX({ detail::InputDevice::XInput, 12, _Index }),
        ButtonY({ detail::InputDevice::XInput, 13, _Index })
      {

      }
    public:
      //  �\���L�[�� �{�^��
      const Button ButtonUp;
      //  �\���L�[�� �{�^��
      const Button ButtonDown;
      //  �\���L�[�� �{�^��
      const Button ButtonLeft;
      //  �\���L�[�� �{�^��
      const Button ButtonRight;
      //  Start �{�^��
      const Button ButtonStart;
      //  Select(Back,Share) �{�^��
      const Button ButtonSelect;
      //  ���X�e�B�b�N�������� �{�^��
      const Button ButtonLeftStick;
      //  �E�X�e�B�b�N�������� �{�^��
      const Button ButtonRightStick;
      //  LB �{�^��
      const Button ButtonLB;
      //  RB �{�^��
      const Button ButtonRB;
      //  A �{�^��
      const Button ButtonA;
      //  B �{�^��
      const Button ButtonB;
      //  X �{�^��
      const Button ButtonX;
      //  Y �{�^��
      const Button ButtonY;
    public:
      //  �ڑ�����Ă���Ȃ�true��Ԃ�
      operator bool()const { return isConnect(); }
    public:
      //  ���X�e�B�b�N�̓��͏�Ԃ��擾
      //  -1~1�͈̔͂ŕ\������Ă܂�
      float2 GetLeftStick(float _DeadZone = 0.0f)const;
      //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
      //  -1~1�͈̔͂ŕ\������Ă܂�
      float2 GetRightStick(float _DeadZone = 0.0f)const;
      //  ���g���K�[�̓��͏�Ԃ��擾
      //  0-1�͈̔͂ŕ\������܂�
      float GetLeftTrigger(float _DeadZone = 0.0f)const;
      //  �E�g���K�[�̓��͏�Ԃ��擾
      //  0-1�͈̔͂ŕ\������܂�
      float GetRightTrigger(float _DeadZone = 0.0f)const;
      //  �ڑ�����Ă��邩�m�F
      //  �ڑ�����true
      bool isConnect()const;
      //  �R���g���[����U�������܂�
      //  0�͒�~�A1�͍ő呬�x
      void SetVibration(float _Speed)const;
      //  �R���g���[���̐U�����~�߂܂�
      void StopVibration()const;
    };
  }
}
