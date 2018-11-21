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
      return Engine::Get<IMouse>()->GetPos();
    }

    //  ���W��ύX
    void Mouse::SetPos(const int2& _Pos)const
    {
      Engine::Get<IMouse>()->SetPos(_Pos);
    }

    //  �ړ��ʂ��擾
    const int2& Mouse::GetDelta()const
    {
      return Engine::Get<IMouse>()->GetDelta();
    }

    //  �z�C�[���ړ��ʂ��擾
    int Mouse::GetWheel()const
    {
      return Engine::Get<IMouse>()->GetWheel();
    }

    //  �����̃{�^����������Ă����true��Ԃ�
    bool Mouse::AnyButtonPress()const
    {
      return Engine::Get<IMouse>()->AnyButtonPress();
    }

    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool Mouse::AnyButtonPressed()const
    {
      return Engine::Get<IMouse>()->AnyButtonPressed();
    }

    //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
    bool Mouse::AnyButtonReleased()const
    {
      return Engine::Get<IMouse>()->AnyButtonReleased();
    }
  }
}
