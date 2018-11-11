#pragma once
#include "../../../Include/Button.hpp"
#include "../../../Include/Type2.hpp"

namespace detail
{
  //  XInput�Ŏg���{�^��
  enum class XInputButtons
  {
    Up,
    Down,
    Left,
    Right,
    Start,
    Select,
    LeftStick,
    RightStick,
    LeftShoulder,
    RightShoulder,
    A,
    B,
    X,
    Y,

    Num
  };

  constexpr int kXInputButtonsCode[] = {
    0x0001, //  XINPUT_GAMEPAD_DPAD_UP
    0x0002, //  XINPUT_GAMEPAD_DPAD_DOWN
    0x0004, //  XINPUT_GAMEPAD_DPAD_LEFT
    0x0008, //  XINPUT_GAMEPAD_DPAD_RIGHT
    0x0010, //  XINPUT_GAMEPAD_START
    0x0020, //  XINPUT_GAMEPAD_BACK
    0x0040, //  XINPUT_GAMEPAD_LEFT_THUMB
    0x0080, //  XINPUT_GAMEPAD_RIGHT_THUMB
    0x0100, //  XINPUT_GAMEPAD_LEFT_SHOULDER
    0x0200, //  XINPUT_GAMEPAD_RIGHT_SHOULDER
    0x1000, //  XINPUT_GAMEPAD_A
    0x2000, //  XINPUT_GAMEPAD_B
    0x4000, //  XINPUT_GAMEPAD_X
    0x8000, //  XINPUT_GAMEPAD_Y
  };

  class IXInput
  {
  public:
    static constexpr int kButtonNum = sizeof(kXInputButtonsCode) / sizeof(kXInputButtonsCode[0]);
    static_assert(static_cast<int>(XInputButtons::Num) == kButtonNum, "Number of XInputButtons And kXInputButtonsCode matches.");
  private:
    struct Status;
  private:
    //Status Status_[kMaxControllerNum];
    Status* Status_;
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
    //  ������
    IXInput();
    //  ��Ԃ̍X�V
    void Update();
    //  ���
    ~IXInput();
  };
}
