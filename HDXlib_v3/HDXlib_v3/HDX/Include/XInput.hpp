#pragma once
#include "Button.hpp"
#include "Type2.hpp"

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    class XInput
    {
      //  �g���{�^��
      enum Buttons
      {
        Up,
        Down,
        Left,
        Right,
        Start,
        Back,
        LeftStick,
        RightStick,
        LeftShoulder,
        RightShoulder,
        A,
        B,
        X,
        Y,
      };
    private:
      const int Index_;
    public:
      //  �Q�[���p�b�h���쐬
      //  _Index:�Q�[���p�b�h�̔ԍ�
      constexpr XInput(int _Index)noexcept : Index_(_Index),
        ButtonUp(InputDevice::XInput, Buttons::Up, _Index),
        ButtonDown(InputDevice::XInput, Buttons::Down, _Index),
        ButtonLeft(InputDevice::XInput, Buttons::Left, _Index),
        ButtonRight(InputDevice::XInput, Buttons::Right, _Index),
        ButtonStart(InputDevice::XInput, Buttons::Start, _Index),
        ButtonSelect(InputDevice::XInput, Buttons::Back, _Index),
        ButtonLeftStick(InputDevice::XInput, Buttons::LeftStick, _Index),
        ButtonRightStick(InputDevice::XInput, Buttons::RightStick, _Index),
        ButtonLB(InputDevice::XInput, Buttons::LeftShoulder, _Index),
        ButtonRB(InputDevice::XInput, Buttons::RightShoulder, _Index),
        ButtonA(InputDevice::XInput, Buttons::A, _Index),
        ButtonB(InputDevice::XInput, Buttons::B, _Index),
        ButtonX(InputDevice::XInput, Buttons::X, _Index),
        ButtonY(InputDevice::XInput, Buttons::Y, _Index)
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
      constexpr bool operator==(const XInput& _XInput)const { return Index_ == _XInput.Index_; }
      constexpr bool operator!=(const XInput& _XInput)const { return !((*this) == _XInput); }
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
      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress()const;
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed()const;
      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased()const;
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
