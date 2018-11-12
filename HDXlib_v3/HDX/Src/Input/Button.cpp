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
      return Engine::GetKeyboard()->Press(Number_);
    case InputDevice::Mouse:
      return Engine::GetMouse()->Press(Number_);
    case InputDevice::XInput:
      return Engine::GetXInput()->Press(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::GetGamepad()->Press(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ğ”»•Ê
  bool Button::Pressed()const
  {
    switch (InputDevice_)
    {
    case InputDevice::Keyboard:
      return Engine::GetKeyboard()->Pressed(Number_);
    case InputDevice::Mouse:
      return Engine::GetMouse()->Pressed(Number_);
    case InputDevice::XInput:
      return Engine::GetXInput()->Pressed(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::GetGamepad()->Pressed(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ğ”»•Ê
  bool Button::Released()const
  {
    switch (InputDevice_)
    {
    case InputDevice::Keyboard:
      return Engine::GetKeyboard()->Released(Number_);
    case InputDevice::Mouse:
      return Engine::GetMouse()->Released(Number_);
    case InputDevice::XInput:
      return Engine::GetXInput()->Released(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::GetGamepad()->Released(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ğ”»•Ê
  bool Button::Release()const
  {
    switch (InputDevice_)
    {
    case InputDevice::Keyboard:
      return Engine::GetKeyboard()->Release(Number_);
    case InputDevice::Mouse:
      return Engine::GetMouse()->Release(Number_);
    case InputDevice::XInput:
      return Engine::GetXInput()->Release(Number_, Index_);
    case InputDevice::Gamepad:
      return Engine::GetGamepad()->Release(Number_, Index_);
    }

    return false;
  }
}
