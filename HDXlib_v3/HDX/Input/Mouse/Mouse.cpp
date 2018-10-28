#include <HDX/Input/Mouse/Mouse.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>

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
        return detail::Engine::GetMouse()->GetPos();
      }

      //  ���W��ύX
      void SetPos(const hdx::int2& _Pos)
      {
        detail::Engine::GetMouse()->SetPos(_Pos);
      }

      //  �ړ��ʂ��擾
      int2 GetDelta()
      {
        return detail::Engine::GetMouse()->GetDelta();
      }

      //  �z�C�[���ړ��ʂ��擾
      int2 GetWheel()
      {
        return detail::Engine::GetMouse()->GetWheel();
      }

      //  �����̃{�^����������Ă����true��Ԃ�
      bool AnyButtonPress()
      {
        return detail::Engine::GetMouse()->AnyButtonPress();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonPressed()
      {
        return detail::Engine::GetMouse()->AnyButtonPressed();
      }

      //  �����̃{�^���������ꂽ�Ȃ�true��Ԃ�
      bool AnyButtonReleased()
      {
        return detail::Engine::GetMouse()->AnyButtonReleased();
      }
    }
  }
}
