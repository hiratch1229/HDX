#include <HDX/Input/Keyboard/Keyboard.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/System.hpp>

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  �L�[�{�[�h
    namespace Keyboard
    {
      //  �����̃L�[��������Ă����true��Ԃ�
      bool AnyKeyPress()
      {
        return detail::System::Get()->GetKeyboard()->AnyKeyPress();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyPressed()
      {
        return detail::System::Get()->GetKeyboard()->AnyKeyPressed();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyReleased()
      {
        return detail::System::Get()->GetKeyboard()->AnyKeyReleased();
      }
    }
  }
}
