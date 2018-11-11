#include "../../../Include/Keyboard.hpp"

#include "../../Engine/Engine.hpp"
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
        return GetKeyboard()->AnyKeyPress();
      }
      //  何かのキーが押されたならtrueを返す
      bool AnyKeyPressed()
      {
        return GetKeyboard()->AnyKeyPressed();
      }
      //  何かのキーが離されたならtrueを返す
      bool AnyKeyReleased()
      {
        return GetKeyboard()->AnyKeyReleased();
      }
    }
  }
}
