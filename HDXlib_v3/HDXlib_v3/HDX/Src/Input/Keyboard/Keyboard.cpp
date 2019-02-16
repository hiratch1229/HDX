#include "Include/Keyboard.hpp"

#include "Src/Engine.hpp"
#include "Src/Input/Keyboard/IKeyboard.hpp"

namespace hdx::Input::Keyboard
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
