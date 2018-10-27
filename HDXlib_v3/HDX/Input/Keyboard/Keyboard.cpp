#include <HDX/Input/Keyboard/Keyboard.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/System.hpp>

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
        return detail::System::Get()->GetKeyboard()->AnyKeyPress();
      }
      //  何かのキーが押されたならtrueを返す
      bool AnyKeyPressed()
      {
        return detail::System::Get()->GetKeyboard()->AnyKeyPressed();
      }
      //  何かのキーが離されたならtrueを返す
      bool AnyKeyReleased()
      {
        return detail::System::Get()->GetKeyboard()->AnyKeyReleased();
      }
    }
  }
}
