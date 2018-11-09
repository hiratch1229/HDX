#include <HDX/Input/Keyboard/Keyboard.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>

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
