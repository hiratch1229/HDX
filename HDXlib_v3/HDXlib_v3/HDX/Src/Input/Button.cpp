#include "../../Include/Button.hpp"

#include "../Engine.hpp"
#include "../Input/Keyboard/IKeyboard.hpp"
#include "../Input/Mouse/IMouse.hpp"
#include "../Input/XInput/IXInput.hpp"
#include "../Input/Gamepad/IGamepad.hpp"

namespace hdx
{
  //  “ü—Íó‘Ô‚ğ”»•Ê
  bool Button::Press()const
  {
    switch (InputDevice_)
    {
    case InputDevice::Keyboard:
      return Engine::Get<IKeyboard>()->Press(Number_);
    case InputDevice::Mouse:
      return Engine::Get<IMouse>()->Press(Number_);
    case InputDevice::XInput:
      return Engine::Get<IXInput>()->Press(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::Get<IGamepad>()->Press(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ğ”»•Ê
  bool Button::Pressed()const
  {
    switch (InputDevice_)
    {
    case InputDevice::Keyboard:
      return Engine::Get<IKeyboard>()->Pressed(Number_);
    case InputDevice::Mouse:
      return Engine::Get<IMouse>()->Pressed(Number_);
    case InputDevice::XInput:
      return Engine::Get<IXInput>()->Pressed(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::Get<IGamepad>()->Pressed(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ğ”»•Ê
  bool Button::Released()const
  {
    switch (InputDevice_)
    {
    case InputDevice::Keyboard:
      return Engine::Get<IKeyboard>()->Released(Number_);
    case InputDevice::Mouse:
      return Engine::Get<IMouse>()->Released(Number_);
    case InputDevice::XInput:
      return Engine::Get<IXInput>()->Released(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::Get<IGamepad>()->Released(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ğ”»•Ê
  bool Button::Release()const
  {
    switch (InputDevice_)
    {
    case InputDevice::Keyboard:
      return Engine::Get<IKeyboard>()->Release(Number_);
    case InputDevice::Mouse:
      return Engine::Get<IMouse>()->Release(Number_);
    case InputDevice::XInput:
      return Engine::Get<IXInput>()->Release(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::Get<IGamepad>()->Release(Number_, Index_);
    }

    return false;
  }
}
