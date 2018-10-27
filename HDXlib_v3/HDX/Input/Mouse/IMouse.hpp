#pragma once
#include <HDX/Singleton.hpp>
#include <HDX/Type2.hpp>

namespace detail
{
  enum class InputState;

  //  �}�E�X�Ŏg���{�^��
  enum class MouseButtons
  {
    Left,
    Middle,
    Right,
    X1,
    X2,

    Num //  ��
  };

  //  �}�E�X
  class IMouse : public hdx::Singleton<IMouse>
  {
    //  �g�p�����{�^���̌�
    static constexpr int kButtonNum = static_cast<int>(MouseButtons::Num);
  private:
    //  ���͏��
    InputState* InputStatus_;
    //  ���W
    hdx::int2 Pos_;
    //  �ړ���
    hdx::int2 Delta_;
    //  �z�C�[���ړ���
    int Wheel_;
  public:
    //  �{�^���������ꂽ���̏���
    void ButtonPressed(MouseButtons Button);
    //  �{�^���������ꂽ���̏���
    void ButtonReleased(MouseButtons Button);
  public:
    //  ������Ă���Ȃ�true��Ԃ�
    bool Press(int _Number)const;
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Pressed(int _Number)const;
    //  �����ꂽ�u�ԂȂ�true��Ԃ�
    bool Released(int _Number)const;
    //  ������Ă��Ȃ��Ȃ�true��Ԃ�
    bool Release(int _Number)const;
  public:
    //  ���W���擾
    hdx::int2 GetPos()const;
    //  ���W��ύX
    void SetPos(const hdx::int2& _Pos);
    //  �ړ��ʂ��擾
    hdx::int2 GetDelta()const;
    //  �z�C�[���ړ��ʂ��擾
    int GetWheel()const;
    //  �z�C�[���ړ��ʂ�ύX
    void SetWheel(int _Wheel);
  public:
    //  �����̃{�^����������Ă����true��Ԃ�
    bool AnyButtonPress()const;
    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool AnyButtonPressed()const;
    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool AnyButtonReleased()const;
  public:
    //  ������
    IMouse();
    //  ��Ԃ̍X�V
    void Update();
    //  ���
    ~IMouse();
  };
}
