#pragma once
#include <HDX/Input/Button.hpp>
#include <HDX/Type2.hpp>

#include <Windows.h>

namespace detail
{
  class IGamepad 
  {
    struct Impl;
  private:
    Impl* pImpl_;
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
    //  �ڑ�����Ă��邩�m�F
    bool isConnect(int _Index)const;
    //  �R���g���[����U�������܂�
    void SetVibration(int _Index, float _Speed)const;
    //  �R���g���[���̐U�����~�߂܂�
    void StopVibration(int _Index)const;
  public:
    //  DirectInput�̍쐬
    void CreateDirectInputDevice(const GUID& GuidProductFromDirectInput);
  public:
    //  ������
    IGamepad();

    void Initialize();
    //  ��Ԃ̍X�V
    void Update();
    //  ���
    ~IGamepad();
  };
}
