#include <HDX/Input/XInput/XInput.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/System/System.hpp>

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  ���X�e�B�b�N�̓��͏�Ԃ��擾
    float2 XInput::GetLeftStick(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetLeftStick(Index_, _DeadZone);
    }

    //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
    float2 XInput::GetRightStick(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetRightStick(Index_, _DeadZone);
    }
    //  ���g���K�[�̓��͏�Ԃ��擾
    float XInput::GetLeftTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetLeftTrigger(Index_, _DeadZone);
    }
    //  �E�g���K�[�̓��͏�Ԃ��擾
    float XInput::GetRightTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetXInput()->GetRightTrigger(Index_, _DeadZone);
    }
    //  �ڑ�����Ă��邩�m�F
    bool XInput::isConnect()const
    {
      return detail::System::Get()->GetXInput()->isConnect(Index_);
    }
    //  �R���g���[����U�������܂�
    void XInput::SetVibration(float _Speed)const
    {
      return detail::System::Get()->GetXInput()->SetVibration(Index_, _Speed);
    }
    //  �R���g���[���̐U�����~�߂܂�
    void XInput::StopVibration()const
    {
      return detail::System::Get()->GetXInput()->StopVibration(Index_);
    }
  }
}