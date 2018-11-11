#pragma once
#include "Button.hpp"
#include "Type2.hpp"

#include <Windows.h>

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    class Gamepad
    {
      const int Index_;
    public:
      static constexpr int kMaxButtonNum = 32;
    public:
      //  �Q�[���p�b�h���쐬
      //  _Index:�Q�[���p�b�h�̔ԍ�
      constexpr Gamepad(int _Index)noexcept
        : Index_(_Index)
      {

      }
    public:
      //  �ڑ�����Ă���Ȃ�true��Ԃ�
      operator bool()const { return isConnect(); }
    public:
      //  �{�^�����擾
      //  _Number:�{�^���ԍ�
      Button GetButton(int _Number)const;
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
