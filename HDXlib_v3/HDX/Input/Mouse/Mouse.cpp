#include <HDX/Input/Mouse/Mouse.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/System/System.hpp>

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
        return detail::System::Get()->GetMouse()->GetPos();
      }

      //  ���W��ύX
      void SetPos(const hdx::int2& _Pos)
      {
        detail::System::Get()->GetMouse()->SetPos(_Pos);
      }

      //  �ړ��ʂ��擾
      int2 GetDelta()
      {
        return detail::System::Get()->GetMouse()->GetDelta();
      }

      //  �z�C�[���ړ��ʂ��擾
      int2 GetWheel()
      {
        return detail::System::Get()->GetMouse()->GetWheel();
      }

      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress()
      {
        return detail::System::Get()->GetMouse()->AnyButtonPress();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed()
      {
        return detail::System::Get()->GetMouse()->AnyButtonPressed();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased()
      {
        return detail::System::Get()->GetMouse()->AnyButtonReleased();
      }
    }
  }
}
