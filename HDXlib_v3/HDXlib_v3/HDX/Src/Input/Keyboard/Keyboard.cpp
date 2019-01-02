#include "Include/Keyboard.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/Keyboard/IKeyboard.hpp"

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
        return Engine::Get<IKeyboard>()->AnyKeyPress();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyPressed()
      {
        return Engine::Get<IKeyboard>()->AnyKeyPressed();
      }
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyReleased()
      {
        return Engine::Get<IKeyboard>()->AnyKeyReleased();
      }
    }
  }
}
