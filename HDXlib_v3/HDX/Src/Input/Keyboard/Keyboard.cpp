#include "../../../Include/Keyboard.hpp"

#include "../../Engine.hpp"
#include "../../Input/Keyboard/IKeyboard.hpp"

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    //  キーボード
    namespace Keyboard
    {
      //  何かのキーが押されていればtrueを返す
      bool AnyKeyPress()
      {
        return Engine::GetKeyboard()->AnyKeyPress();
      }
      //  何かのキーが押されたならtrueを返す
      bool AnyKeyPressed()
      {
        return Engine::GetKeyboard()->AnyKeyPressed();
      }
      //  何かのキーが離されたならtrueを返す
      bool AnyKeyReleased()
      {
        return Engine::GetKeyboard()->AnyKeyReleased();
      }
    }
  }
}
