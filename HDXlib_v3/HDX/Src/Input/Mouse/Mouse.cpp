#include "../../../Include/Mouse.hpp"

#include "../../Engine/Engine.hpp"
#include "../../Input/Mouse/IMouse.hpp"

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
      int2 GetPos()
      {
        return GetMouse()->GetPos();
      }

      //  ���W��ύX
      void SetPos(const hdx::int2& _Pos)
      {
        GetMouse()->SetPos(_Pos);
      }

      //  �ړ��ʂ��擾
      int2 GetDelta()
      {
        return GetMouse()->GetDelta();
      }

      //  �z�C�[���ړ��ʂ��擾
      int2 GetWheel()
      {
        return GetMouse()->GetWheel();
      }

      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress()
      {
        return GetMouse()->AnyButtonPress();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed()
      {
        return GetMouse()->AnyButtonPressed();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased()
      {
        return GetMouse()->AnyButtonReleased();
      }
    }
  }
}
