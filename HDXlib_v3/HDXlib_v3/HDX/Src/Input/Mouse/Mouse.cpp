#include "../../../Include/Mouse.hpp"

#include "../../Engine.hpp"
#include "../../Input/Mouse/IMouse.hpp"

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  ���W���擾
    const int2& Mouse::GetPos()const
    {
      return Engine::GetMouse()->GetPos();
    }

    //  ���W��ύX
    void Mouse::SetPos(const int2& _Pos)const
    {
      Engine::GetMouse()->SetPos(_Pos);
    }

    //  �ړ��ʂ��擾
    const int2& Mouse::GetDelta()const
    {
      return Engine::GetMouse()->GetDelta();
    }

    //  �z�C�[���ړ��ʂ��擾
    int Mouse::GetWheel()const
    {
      return Engine::GetMouse()->GetWheel();
    }

    //  �����̃{�^����������Ă����true��Ԃ�
    bool Mouse::AnyButtonPress()const
    {
      return Engine::GetMouse()->AnyButtonPress();
    }

    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool Mouse::AnyButtonPressed()const
    {
      return Engine::GetMouse()->AnyButtonPressed();
    }

    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool Mouse::AnyButtonReleased()const
    {
      return Engine::GetMouse()->AnyButtonReleased();
    }
  }
}
