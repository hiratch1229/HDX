#include <HDX/Input/Keyboard/Keyboard.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>

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
        return detail::Engine::GetKeyboard()->AnyKeyPress();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyPressed()
      {
        return detail::Engine::GetKeyboard()->AnyKeyPressed();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyReleased()
      {
        return detail::Engine::GetKeyboard()->AnyKeyReleased();
      }
    }
  }
}
