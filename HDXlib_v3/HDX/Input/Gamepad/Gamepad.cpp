#include <HDX/Input/Gamepad/Gamepad.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/Constants.hpp>

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  �{�^�����擾
    Button Gamepad::GetButton(int _Number)const
    {
      return GetGamepad()->GetButton(Index_, _Number);
    }

    //  ���X�e�B�b�N�̓��͏�Ԃ��擾
    float2 Gamepad::GetLeftStick(float _DeadZone)const
    {
      return GetGamepad()->GetLeftStick(Index_, _DeadZone);
    }

    //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
    float2 Gamepad::GetRightStick(float _DeadZone)const
    {
      return GetGamepad()->GetRightStick(Index_, _DeadZone);
    }

    //  ���g���K�[�̓��͏�Ԃ��擾
    float Gamepad::GetLeftTrigger(float _DeadZone)const
    {
      return GetGamepad()->GetLeftTrigger(Index_, _DeadZone);
    }

    //  �E�g���K�[�̓��͏�Ԃ��擾
    float Gamepad::GetRightTrigger(float _DeadZone)const
    {
      return GetGamepad()->GetRightTrigger(Index_, _DeadZone);
    }

    //  �ڑ�����Ă��邩�m�F
    bool Gamepad::isConnect()const
    {
      return GetGamepad()->isConnect(Index_);
    }

    //  �R���g���[����U�������܂�
    void Gamepad::SetVibration(float _Speed)const
    {
      return GetGamepad()->SetVibration(Index_, _Speed);
    }

    //  �R���g���[���̐U�����~�߂܂�
    void Gamepad::StopVibration()const
    {
      return GetGamepad()->StopVibration(Index_);
    }
  }
}
