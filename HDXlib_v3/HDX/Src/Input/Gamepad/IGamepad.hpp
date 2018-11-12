#pragma once
#include "../../../Include/Button.hpp"
#include "../../../Include/Type2.hpp"
#include "../../../Include/Constants.hpp"

#include "../InputState.hpp"

class IGamepad
{
  static constexpr int kButtonNum = 32;
  static constexpr int kControllerNum = hdx::ControllerMaxNum;
private:
  struct Status
  {
    //  �ڑ����
    bool isConnect = true;
    //  ���͏��
    InputState InputStatus[kButtonNum];
    //  ���̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 LeftStick;
    //  �E�̃A�i���O�X�e�B�b�N�̓��͏��
    hdx::float2 RightStick;
    //  ���̃g���K�[�̓��͏��
    float LeftTrigger;
    //  �E�̃g���K�[�̓��͏��
    float RightTrigger;
  };
private:
  Status Status_[kControllerNum];
public:
  //  ������Ă���Ȃ�true��Ԃ�
  bool Press(int _Number, int _Index)const;
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Pressed(int _Number, int _Index)const;
  //  �����ꂽ�u�ԂȂ�true��Ԃ�
  bool Released(int _Number, int _Index)const;
  //  ������Ă��Ȃ��Ȃ�true��Ԃ�
  bool Release(int _Number, int _Index)const;
public:
  //  �ڑ�����Ă��邩�m�F
  bool isConnect(int _Index)const;
public:
  //  �����̃{�^����������Ă����true��Ԃ�
  bool AnyButtonPress(int _Index)const;
  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool AnyButtonPressed(int _Index)const;
  //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
  bool AnyButtonReleased(int _Index)const;
public:
  //  �{�^�����擾
  hdx::Button GetButton(int _Index, int _Number)const;
public:
  //  ���X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 GetLeftStick(int _Index, float _DeadZone)const;
  //  �E�X�e�B�b�N�̓��͏�Ԃ��擾
  hdx::float2 GetRightStick(int _Index, float _DeadZone)const;
public:
  //  ���g���K�[�̓��͏�Ԃ��擾
  float GetLeftTrigger(int _Index, float _DeadZone)const;
  //  �E�g���K�[�̓��͏�Ԃ��擾
  float GetRightTrigger(int _Index, float _DeadZone)const;
public:
  //  �R���g���[����U�������܂�
  void SetVibration(int _Index, float _Speed)const;
  //  �R���g���[���̐U�����~�߂܂�
  void StopVibration(int _Index)const;
public:
  //  ������
  IGamepad();
  //  ��Ԃ̍X�V
  void Update();
  //  ���
  ~IGamepad();
};
