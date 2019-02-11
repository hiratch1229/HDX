#pragma once
#include "Button.hpp"
#include "Type2.hpp"
#include "Types.hpp"

namespace hdx
{
  namespace Input
  {
    class Gamepad
    {
      const int Index_;
    public:
      enum class Buttons
      {
        Up,
        Down,
        Left,
        Right,
      };
      enum class ButtonsForXInput
      {
        Start = 4,
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
      enum class ButtonsForPS
      {
        Square = 4,
        X,
        Circle,
        Triangle,
        L1,
        R1,
        L2,
        R2,
        Share,
        Options,
        L3,
        R3,
        PS,
        TouchPad,
      };
    public:
      static constexpr int kMaxButtonNum = 32;
    public:
      //  �Q�[���p�b�h���쐬
      //  _Index:�Q�[���p�b�h�̔ԍ�
      constexpr Gamepad(int _Index)noexcept : Index_(_Index) {}
    public:
      //  �ڑ�����Ă���Ȃ�true��Ԃ�
      operator bool()const { return isConnect(); }
    public:
      constexpr bool operator==(const Gamepad& _Gamepad)const { return Index_ == _Gamepad.Index_; }
      constexpr bool operator!=(const Gamepad& _Gamepad)const { return !((*this) == _Gamepad); }
    public:
      //  �{�^�����擾
      //  _Number:�{�^���ԍ�
      Button GetButton(UINT _Number)const;
      Button GetButton(Buttons _Number)const { return GetButton(static_cast<UINT>(_Number)); }
      Button GetButton(ButtonsForXInput _Number)const { return GetButton(static_cast<UINT>(_Number)); }
      Button GetButton(ButtonsForPS _Number)const { return GetButton(static_cast<UINT>(_Number)); }
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
      //  �{�^���̐����擾
      int GetButtonNum()const;
      //  �R���g���[����U�������܂�
      //  0�͒�~�A1�͍ő呬�x
      void SetVibration(float _Speed)const;
      //  �R���g���[���̐U�����~�߂܂�
      void StopVibration()const;
    };
  }
}
