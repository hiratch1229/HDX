#include "../../../Include/XInput.hpp"

#include "../../Engine.hpp"
#include "../../Input/XInput/IXInput.hpp"

//  ���C�u����
namespace hdx
{
  //  ���͌n
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