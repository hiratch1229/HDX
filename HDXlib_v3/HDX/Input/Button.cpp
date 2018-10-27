#include <HDX/Input/Button.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/System/System.hpp>

namespace hdx
{
  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Press()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return detail::System::Get()->GetKeyboard()->Press(Number_);
    case detail::InputDevice::Mouse:
      return detail::System::Get()->GetMouse()->Press(Number_);
    case detail::InputDevice::XInput:
      return detail::System::Get()->GetXInput()->Press(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::System::Get()->GetGamepad()->Press(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Pressed()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return detail::System::Get()->GetKeyboard()->Pressed(Number_);
    case detail::InputDevice::Mouse:
      return detail::System::Get()->GetMouse()->Pressed(Number_);
    case detail::InputDevice::XInput:
      return detail::System::Get()->GetXInput()->Pressed(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::System::Get()->GetGamepad()->Pressed(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Released()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return detail::System::Get()->GetKeyboard()->Released(Number_);
    case detail::InputDevice::Mouse:
      return detail::System::Get()->GetMouse()->Released(Number_);
    case detail::InputDevice::XInput:
      return detail::System::Get()->GetXInput()->Released(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::System::Get()->GetGamepad()->Released(Number_, Index_);
    }

    return false;
  }

  //  “ü—Íó‘Ô‚ð”»•Ê
  bool Button::Release()const
  {
    switch (InputDevice_)
    {
    case detail::InputDevice::Keyboard:
      return detail::System::Get()->GetKeyboard()->Release(Number_);
    case detail::InputDevice::Mouse:
      return detail::System::Get()->GetMouse()->Release(Number_);
    case detail::InputDevice::XInput:
      return detail::System::Get()->GetXInput()->Release(Number_, Index_);
    case detail::InputDevice::Gamepad:
      return detail::System::Get()->GetGamepad()->Release(Number_, Index_);
    }

    return false;
  }
}
