#include <HDX/Input/Gamepad/Gamepad.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/System/System.hpp>

//  ���C�u����
namespace hdx
{
  //���͌n
  namespace Input
  {
    //  �{�^�����擾
    Button Gamepad::GetButton(int _Number)const
    {
      return detail::System::Get()->GetGamepad()->GetButton(Index_, _Number);
    }

    //  ���X�e�B�b�N�̓��͏�Ԃ��擾
    float2 Gamepad::GetLeftStick(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetLeftStick(Index_, _DeadZone);
    }

    //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
    float2 Gamepad::GetRightStick(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetRightStick(Index_, _DeadZone);
    }

    //  ���g���K�[�̓��͏�Ԃ��擾
    float Gamepad::GetLeftTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetLeftTrigger(Index_, _DeadZone);
    }

    //  �E�g���K�[�̓��͏�Ԃ��擾
    float Gamepad::GetRightTrigger(float _DeadZone)const
    {
      return detail::System::Get()->GetGamepad()->GetRightTrigger(Index_, _DeadZone);
    }

    //  �ڑ�����Ă��邩�m�F
    bool Gamepad::isConnect()const
    {
      return detail::System::Get()->GetGamepad()->isConnect(Index_);
    }

    //  �R���g���[����U�������܂�
    void Gamepad::SetVibration(float _Speed)const
    {
      return detail::System::Get()->GetGamepad()->SetVibration(Index_, _Speed);
    }

    //  �R���g���[���̐U�����~�߂܂�
    void Gamepad::StopVibration()const
    {
      return detail::System::Get()->GetGamepad()->StopVibration(Index_);
    }
  }
}
