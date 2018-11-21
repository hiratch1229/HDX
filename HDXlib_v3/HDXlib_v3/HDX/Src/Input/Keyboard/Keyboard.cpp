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
        return Engine::Get<IKeyboard>()->AnyKeyPress();
      }
      //  何かのキーが押されたならtrueを返す
      bool AnyKeyPressed()
      {
        return Engine::Get<IKeyboard>()->AnyKeyPressed();
      }
      //  何かのキーが離されたならtrueを返す
      bool AnyKeyReleased()
      {
        return Engine::Get<IKeyboard>()->AnyKeyReleased();
      }
    }
  }
}
