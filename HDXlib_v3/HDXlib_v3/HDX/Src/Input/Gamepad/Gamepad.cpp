#include "Include/Gamepad.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/Gamepad/IGamepad.hpp"

#include "Include/Constants.hpp"

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  �{�^�����擾
    Button Gamepad::GetButton(UINT _Number)const
    {
      return Engine::Get<IGamepad>()->GetButton(Index_, _Number);
    }
    //  ���X�e�B�b�N�̓��͏�Ԃ��擾
    float2 Gamepad::GetLeftStick(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetLeftStick(Index_, _DeadZone);
    }
    //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
    float2 Gamepad::GetRightStick(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetRightStick(Index_, _DeadZone);
    }
    //  ���g���K�[�̓��͏�Ԃ��擾
    float Gamepad::GetLeftTrigger(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetLeftTrigger(Index_, _DeadZone);
    }
    //  �E�g���K�[�̓��͏�Ԃ��擾
    float Gamepad::GetRightTrigger(float _DeadZone)const
    {
      return Engine::Get<IGamepad>()->GetRightTrigger(Index_, _DeadZone);
    }
    //  �����̃{�^����������Ă����true��Ԃ�
    bool Gamepad::AnyButtonPress()const
    {
      return Engine::Get<IGamepad>()->AnyButtonPress(Index_);
    }
    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool Gamepad::AnyButtonPressed()const
    {
      return Engine::Get<IGamepad>()->AnyButtonPressed(Index_);
    }
    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool Gamepad::AnyButtonReleased()const
    {
      return Engine::Get<IGamepad>()->AnyButtonReleased(Index_);
    }
    //  �ڑ�����Ă��邩�m�F
    bool Gamepad::isConnect()const
    {
      return Engine::Get<IGamepad>()->isConnect(Index_);
    }
    //  �{�^���̐����擾
    int Gamepad::GetButtonNum()const
    {
      return Engine::Get<IGamepad>()->GetButtonNum(Index_);
    }
    //  �R���g���[����U�������܂�
    void Gamepad::SetVibration(float _Speed)const
    {
      return Engine::Get<IGamepad>()->SetVibration(Index_, _Speed);
    }
    //  �R���g���[���̐U�����~�߂܂�
    void Gamepad::StopVibration()const
    {
      return Engine::Get<IGamepad>()->StopVibration(Index_);
    }
  }
}
