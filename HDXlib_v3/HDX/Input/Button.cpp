#include <HDX/Input/Button.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>

namespace hdx
{
  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Press()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return GetKeyboard()->Press(Number_);
    case detail::InputDevice::Mouse:
      return GetMouse()->Press(Number_);
    case detail::InputDevice::XInput:
      return GetXInput()->Press(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return GetGamepad()->Press(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Pressed()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return GetKeyboard()->Pressed(Number_);
    case detail::InputDevice::Mouse:
      return GetMouse()->Pressed(Number_);
    case detail::InputDevice::XInput:
      return GetXInput()->Pressed(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return GetGamepad()->Pressed(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Released()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return GetKeyboard()->Released(Number_);
    case detail::InputDevice::Mouse:
      return GetMouse()->Released(Number_);
    case detail::InputDevice::XInput:
      return GetXInput()->Released(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return GetGamepad()->Released(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Release()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return GetKeyboard()->Release(Number_);
    case detail::InputDevice::Mouse:
      return GetMouse()->Release(Number_);
    case detail::InputDevice::XInput:
      return GetXInput()->Release(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return GetGamepad()->Release(Number_, Index_);
    }

    return false;
  }
}
