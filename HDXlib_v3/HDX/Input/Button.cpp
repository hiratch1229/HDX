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
      return detail::Engine::GetKeyboard()->Press(Number_);
    case detail::InputDevice::Mouse:
      return detail::Engine::GetMouse()->Press(Number_);
    case detail::InputDevice::XInput:
      return detail::Engine::GetXInput()->Press(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::Engine::GetGamepad()->Press(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Pressed()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return detail::Engine::GetKeyboard()->Pressed(Number_);
    case detail::InputDevice::Mouse:
      return detail::Engine::GetMouse()->Pressed(Number_);
    case detail::InputDevice::XInput:
      return detail::Engine::GetXInput()->Pressed(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::Engine::GetGamepad()->Pressed(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Released()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return detail::Engine::GetKeyboard()->Released(Number_);
    case detail::InputDevice::Mouse:
      return detail::Engine::GetMouse()->Released(Number_);
    case detail::InputDevice::XInput:
      return detail::Engine::GetXInput()->Released(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::Engine::GetGamepad()->Released(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Release()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return detail::Engine::GetKeyboard()->Release(Number_);
    case detail::InputDevice::Mouse:
      return detail::Engine::GetMouse()->Release(Number_);
    case detail::InputDevice::XInput:
      return detail::Engine::GetXInput()->Release(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::Engine::GetGamepad()->Release(Number_, Index_);
    }

    return false;
  }
}
