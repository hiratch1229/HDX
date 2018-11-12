#include "../../../Include/Keyboard.hpp"

#include "../../Engine.hpp"
#include "../../Input/Keyboard/IKeyboard.hpp"

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
        return Engine::GetKeyboard()->AnyKeyPress();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyPressed()
      {
        return Engine::GetKeyboard()->AnyKeyPressed();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyReleased()
      {
        return Engine::GetKeyboard()->AnyKeyReleased();
      }
    }
  }
}
