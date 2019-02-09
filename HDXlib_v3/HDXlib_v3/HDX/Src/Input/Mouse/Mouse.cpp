#include "Include/Mouse.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/Mouse/IMouse.hpp"

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  �}�E�X
    namespace Mouse
    {
      //  ���W���擾
      const int2& GetPos()
      {
        return Engine::Get<IMouse>()->GetPos();
      }

      //  ���W��ύX
      void SetPos(const int2& _Pos)
      {
        Engine::Get<IMouse>()->SetPos(_Pos);
      }

      //  �ړ��ʂ��擾
      const int2& GetDelta()
      {
        return Engine::Get<IMouse>()->GetDelta();
      }

      //  �z�C�[���ړ��ʂ��擾
      const int2& GetWheel()
      {
        return Engine::Get<IMouse>()->GetWheel();
      }

      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress()
      {
        return Engine::Get<IMouse>()->AnyButtonPress();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed()
      {
        return Engine::Get<IMouse>()->AnyButtonPressed();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased()
      {
        return Engine::Get<IMouse>()->AnyButtonReleased();
      }
    }
  }
}
