#include "Include/XInput.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/XInput/IXInput.hpp"

#include "Include/Gamepad.hpp"

namespace hdx
{
  namespace Input
  {
    //  ���X�e�B�b�N�̓��͏�Ԃ��擾
    float2 XInput::GetLeftStick(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetLeftStick(Index_, _DeadZone);
    }

    //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
    float2 XInput::GetRightStick(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetRightStick(Index_, _DeadZone);
    }
    //  ���g���K�[�̓��͏�Ԃ��擾
    float XInput::GetLeftTrigger(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetLeftTrigger(Index_, _DeadZone);
    }
    //  �E�g���K�[�̓��͏�Ԃ��擾
    float XInput::GetRightTrigger(float _DeadZone)const
    {
      return Engine::Get<IXInput>()->GetRightTrigger(Index_, _DeadZone);
    }
    //  �����̃{�^����������Ă����true��Ԃ�
    bool XInput::AnyButtonPress()const
    {
      return Engine::Get<IXInput>()->AnyButtonPress(Index_);
    }
    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool XInput::AnyButtonPressed()const
    {
      return Engine::Get<IXInput>()->AnyButtonPressed(Index_);
    }
    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool XInput::AnyButtonReleased()const
    {
      return Engine::Get<IXInput>()->AnyButtonReleased(Index_);
    }
    //  �ڑ�����Ă��邩�m�F
    bool XInput::isConnect()const
    {
      return Engine::Get<IXInput>()->isConnect(Index_);
    }
    //  �R���g���[����U�������܂�
    void XInput::SetVibration(float _Speed)const
    {
      return Engine::Get<IXInput>()->SetVibration(Index_, _Speed);
    }
    //  �R���g���[���̐U�����~�߂܂�
    void XInput::StopVibration()const
    {
      return Engine::Get<IXInput>()->StopVibration(Index_);
    }
  }
}