#pragma once

//  ���C�u����
namespace hdx
{
  class ButtonCombinationAND;
  class ButtonCombinationOR;

  //  ���̓f�o�C�X
  enum class InputDevice
  {
    None,
    Keyboard,
    Mouse,
    XInput,
    Gamepad,
  };

  //  �{�^��
  //  ���͏�Ԃ�\�����܂�
  class Button
  {
    //  ���̓f�o�C�X
    InputDevice InputDevice_;
    //  ���ꂼ��̓��̓f�o�C�X�Ń{�^���̌��߂�ꂽ�ԍ�
    int Number_;
    //  ���ꂼ��̓��̓f�o�C�X�̔ԍ�
    int Index_;
  public:
    //  �{�^�����쐬
    Button() = default;
    //  �{�^�����쐬
    //  _InputDevice:���̓f�o�C�X
    //  _ButtonNumber:���ꂼ��̓��̓f�o�C�X�Ń{�^���̌��߂�ꂽ�ԍ�
    constexpr Button(InputDevice _InputDevice, int _Number, int _Index = 0)noexcept : InputDevice_(_InputDevice), Number_(_Number), Index_(_Index) {}
  public:
    //  ���͏�Ԃ𔻕�
    //  ������Ă���Ȃ�true��Ԃ�
    bool Press()const;
    //  ���͏�Ԃ𔻕�
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Pressed()const;
    //  ���͏�Ԃ𔻕�
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Released()const;
    //  ���͏�Ԃ𔻕�
    //  ������Ă��Ȃ��Ȃ�true��Ԃ�
    bool Release()const;
  public:
    //  ������Ă���Ȃ�true��Ԃ�
    operator bool()const { return Press(); }
    //  ������Ă��Ȃ��Ȃ�true��Ԃ�
    bool operator !()const { return !Press(); }
    //  2�̃L�[���������ǂ������r���܂�
    //  (true:����,false:�قȂ�)
    constexpr bool operator ==(const Button& _Button)const noexcept
    {
      return (InputDevice_ == _Button.InputDevice_ && Index_ == _Button.Index_ && Number_ == _Button.Number_);
    }
    //  2�̃L�[���قȂ邩�ǂ������r���܂�
    //  (true:�قȂ�,false:����)
    constexpr bool operator !=(const Button& _Button)const noexcept
    {
      return !(*this == _Button);
    }
    //  �_����
    constexpr ButtonCombinationAND operator&&(const Button& _Button)const noexcept;
    //  �_���a
    constexpr ButtonCombinationOR operator||(const Button& _Button)const noexcept;
  };

  //  �{�^���̘_���ς̑g�ݍ��킹
  //  ���͏�Ԃ�\�����܂�
  class ButtonCombinationAND
  {
    Button Button1_, Button2_;
  public:
    //  �L�[�̘_���ς̑g�ݍ��킹���쐬
    ButtonCombinationAND() = default;
    //  �L�[�̘_���ς̑g�ݍ��킹���쐬
    //  _Button1,_Button2:�g�ݍ��킹�����{�^��
    constexpr ButtonCombinationAND(const Button& _Button1, const Button& _Button2)noexcept : Button1_(_Button1), Button2_(_Button2) {}
  public:
    //  ���͏�Ԃ𔻕�
    //  ������Ă���Ȃ�true��Ԃ�
    bool Press()const { return Button1_.Press() && Button2_.Press(); }
    //  ���͏�Ԃ𔻕�
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Pressed()const { return Button1_.Pressed() && Button2_.Pressed(); }
    //  ���͏�Ԃ𔻕�
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Released()const { return Button1_.Released() && Button2_.Released(); }
    //  ���͏�Ԃ𔻕�
    //  ������Ă��Ȃ��Ȃ�true��Ԃ�
    bool Release()const { return Button1_.Release() && Button2_.Release(); }
  public:
    //  ������Ă���Ȃ�true��Ԃ�
    operator bool()const { return Press(); }
    //  ������Ă��Ȃ��Ȃ�true��Ԃ�
    bool operator !()const { return !Press(); }
    //  2�̃L�[���������ǂ������r���܂�
    //  (true:����,false:�قȂ�)
    constexpr bool operator ==(const ButtonCombinationAND& _ButtonCombinationAND)const noexcept
    {
      return (Button1_ == _ButtonCombinationAND.Button1_ && Button2_ == _ButtonCombinationAND.Button2_);
    }
    //  2�̃L�[���قȂ邩�ǂ������r���܂�
    //  (true:�قȂ�,false:����)
    constexpr bool operator !=(const ButtonCombinationAND& _ButtonCombinationAND)const noexcept
    {
      return !(*this == _ButtonCombinationAND);
    }
  };

  //  �_����
  inline constexpr ButtonCombinationAND Button::operator&&(const Button& _Button)const noexcept
  {
    return{ (*this),_Button };
  }

  //  �{�^���̘_���a�̑g�ݍ��킹
  //  ���͏�Ԃ�\�����܂�
  class ButtonCombinationOR
  {
    Button Button1_, Button2_;
  public:
    //  �L�[�̘_���a�̑g�ݍ��킹���쐬
    ButtonCombinationOR() = default;
    //  �L�[�̘_���a�̑g�ݍ��킹���쐬
    //  _Button1,_Button2:�g�ݍ��킹�����{�^��
    constexpr ButtonCombinationOR(const Button& _Button1, const Button& _Button2)noexcept : Button1_(_Button1), Button2_(_Button2) {}
  public:
    //  ���͏�Ԃ𔻕�
    //  ������Ă���Ȃ�true��Ԃ�
    bool Press()const { return Button1_.Press() || Button2_.Press(); }
    //  ���͏�Ԃ𔻕�
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Pressed()const { return Button1_.Pressed() || Button2_.Pressed(); }
    //  ���͏�Ԃ𔻕�
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Released()const { return Button1_.Released() || Button2_.Released(); }
    //  ���͏�Ԃ𔻕�
    //  ������Ă��Ȃ��Ȃ�true��Ԃ�
    bool Release()const { return Button1_.Release() || Button2_.Release(); }
  public:
    //  ������Ă���Ȃ�true��Ԃ�
    operator bool()const { return Press(); }
    //  ������Ă��Ȃ��Ȃ�true��Ԃ�
    bool operator !()const { return !Press(); }
    //  2�̃L�[���������ǂ������r���܂�
    //  (true:����,false:�قȂ�)
    constexpr bool operator ==(const ButtonCombinationOR& _ButtonCombinationOR)const noexcept
    {
      return (Button1_ == _ButtonCombinationOR.Button1_ && Button2_ == _ButtonCombinationOR.Button2_);
    }
    //  2�̃L�[���قȂ邩�ǂ������r���܂�
    //  (true:�قȂ�,false:����)
    constexpr bool operator !=(const ButtonCombinationOR& _ButtonCombinationOR)const noexcept
    {
      return !(*this == _ButtonCombinationOR);
    }
  };

  //  �_���a
  inline constexpr ButtonCombinationOR Button::operator||(const Button& _Button)const noexcept
  {
    return{ (*this),_Button };
  }
}
