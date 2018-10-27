#pragma once
#include <HDX/Input/Button.hpp>
#include <HDX/Input/InputState.hpp>

//  ライブラリ
namespace hdx
{
  //  入力系
  namespace Input
  {
    //  キーボード
    namespace Keyboard
    {
      //  Backspace キー
      constexpr Button KeyBackspace{ detail::InputDevice::Keyboard, 0 };
      //  Tab キー
      constexpr Button KeyTab{ detail::InputDevice::Keyboard, 1 };
      //  Enter キー
      constexpr Button KeyEnter{ detail::InputDevice::Keyboard, 2 };
      //  Shift キー
      constexpr Button KeyShift{ detail::InputDevice::Keyboard, 3 };
      //  Ctrl キー
      constexpr Button KeyControl{ detail::InputDevice::Keyboard, 4 };
      //  Alt キー
      constexpr Button KeyAlt{ detail::InputDevice::Keyboard, 5 };
      //  Pause キー
      constexpr Button KeyPause{ detail::InputDevice::Keyboard, 6 };
      //  Cpas Lock キー
      constexpr Button KeyCapsLock{ detail::InputDevice::Keyboard, 7 };
      //  Escape キー
      constexpr Button KeyEscape{ detail::InputDevice::Keyboard, 8 };
      //  スペース キー
      constexpr Button KeySpace{ detail::InputDevice::Keyboard, 9 };
      //  PageUp キー
      constexpr Button KeyPageUp{ detail::InputDevice::Keyboard, 10 };
      //  PageDown キー
      constexpr Button KeyPageDown{ detail::InputDevice::Keyboard, 11 };
      //  End キー
      constexpr Button KeyEnd{ detail::InputDevice::Keyboard, 12 };
      //  Home キー
      constexpr Button KeyHome{ detail::InputDevice::Keyboard, 13 };
      //  ← キー
      constexpr Button KeyLeft{ detail::InputDevice::Keyboard, 14 };
      //  ↑ キー
      constexpr Button KeyUp{ detail::InputDevice::Keyboard, 15 };
      //  → キー
      constexpr Button KeyRight{ detail::InputDevice::Keyboard, 16 };
      //  ↓ キー
      constexpr Button KeyDown{ detail::InputDevice::Keyboard, 17 };
      //  PrintScreen キー
      constexpr Button KeyPrintScreen{ detail::InputDevice::Keyboard, 18 };
      //  Insert キー
      constexpr Button KeyInsert{ detail::InputDevice::Keyboard, 19 };
      //  Delete キー
      constexpr Button KeyDelete{ detail::InputDevice::Keyboard, 20 };
      //  0 キー
      constexpr Button Key0{ detail::InputDevice::Keyboard, 21 };
      //  1 キー
      constexpr Button Key1{ detail::InputDevice::Keyboard, 22 };
      //  2 キー
      constexpr Button Key2{ detail::InputDevice::Keyboard, 23 };
      //  3 キー
      constexpr Button Key3{ detail::InputDevice::Keyboard, 24 };
      //  4 キー
      constexpr Button Key4{ detail::InputDevice::Keyboard, 25 };
      //  5 キー
      constexpr Button Key5{ detail::InputDevice::Keyboard, 26 };
      //  6 キー
      constexpr Button Key6{ detail::InputDevice::Keyboard, 27 };
      //  7 キー
      constexpr Button Key7{ detail::InputDevice::Keyboard, 28 };
      //  8 キー
      constexpr Button Key8{ detail::InputDevice::Keyboard, 29 };
      //  9 キー
      constexpr Button Key9{ detail::InputDevice::Keyboard, 30 };
      //  A キー
      constexpr Button KeyA{ detail::InputDevice::Keyboard, 31 };
      //  B キー
      constexpr Button KeyB{ detail::InputDevice::Keyboard, 32 };
      //  C キー
      constexpr Button KeyC{ detail::InputDevice::Keyboard, 33 };
      //  D キー
      constexpr Button KeyD{ detail::InputDevice::Keyboard, 34 };
      //  E キー
      constexpr Button KeyE{ detail::InputDevice::Keyboard, 35 };
      //  F キー
      constexpr Button KeyF{ detail::InputDevice::Keyboard, 36 };
      //  G キー
      constexpr Button KeyG{ detail::InputDevice::Keyboard, 37 };
      //  H キー
      constexpr Button KeyH{ detail::InputDevice::Keyboard, 38 };
      //  I キー
      constexpr Button KeyI{ detail::InputDevice::Keyboard, 39 };
      //  J キー
      constexpr Button KeyJ{ detail::InputDevice::Keyboard, 40 };
      //  K キー
      constexpr Button KeyK{ detail::InputDevice::Keyboard, 41 };
      //  L キー
      constexpr Button KeyL{ detail::InputDevice::Keyboard, 42 };
      //  M キー
      constexpr Button KeyM{ detail::InputDevice::Keyboard, 43 };
      //  N キー
      constexpr Button KeyN{ detail::InputDevice::Keyboard, 44 };
      //  O キー
      constexpr Button KeyO{ detail::InputDevice::Keyboard, 45 };
      //  P キー
      constexpr Button KeyP{ detail::InputDevice::Keyboard, 46 };
      //  Q キー
      constexpr Button KeyQ{ detail::InputDevice::Keyboard, 47 };
      //  R キー
      constexpr Button KeyR{ detail::InputDevice::Keyboard, 48 };
      //  S キー
      constexpr Button KeyS{ detail::InputDevice::Keyboard, 49 };
      //  T キー
      constexpr Button KeyT{ detail::InputDevice::Keyboard, 50 };
      //  U キー
      constexpr Button KeyU{ detail::InputDevice::Keyboard, 51 };
      //  V キー
      constexpr Button KeyV{ detail::InputDevice::Keyboard, 52 };
      //  W キー
      constexpr Button KeyW{ detail::InputDevice::Keyboard, 53 };
      //  X キー
      constexpr Button KeyX{ detail::InputDevice::Keyboard, 54 };
      //  Y キー
      constexpr Button KeyY{ detail::InputDevice::Keyboard, 55 };
      //  Z キー
      constexpr Button KeyZ{ detail::InputDevice::Keyboard, 56 };
      //  左 Windows キー
      constexpr Button KeyLeftWindows{ detail::InputDevice::Keyboard, 57 };
      //  右 Windows キー
      constexpr Button KeyRightWindows{ detail::InputDevice::Keyboard, 58 };
      //  テンキー 0 キー
      constexpr Button KeyNumPad0{ detail::InputDevice::Keyboard, 59 };
      //  テンキー 1 キー
      constexpr Button KeyNumPad1{ detail::InputDevice::Keyboard, 60 };
      //  テンキー 2 キー
      constexpr Button KeyNumPad2{ detail::InputDevice::Keyboard, 61 };
      //  テンキー 3 キー
      constexpr Button KeyNumPad3{ detail::InputDevice::Keyboard, 62 };
      //  テンキー 4 キー
      constexpr Button KeyNumPad4{ detail::InputDevice::Keyboard, 63 };
      //  テンキー 5 キー
      constexpr Button KeyNumPad5{ detail::InputDevice::Keyboard, 64 };
      //  テンキー 6 キー
      constexpr Button KeyNumPad6{ detail::InputDevice::Keyboard, 65 };
      //  テンキー 7 キー
      constexpr Button KeyNumPad7{ detail::InputDevice::Keyboard, 66 };
      //  テンキー 8 キー
      constexpr Button KeyNumPad8{ detail::InputDevice::Keyboard, 67 };
      //  テンキー 9 キー
      constexpr Button KeyNumPad9{ detail::InputDevice::Keyboard, 68 };
      //  テンキー * キー
      constexpr Button KeyNumPadMultiply{ detail::InputDevice::Keyboard, 69 };
      //  テンキー + キー
      constexpr Button KeyNumPadAdd{ detail::InputDevice::Keyboard, 70 };
      //  テンキー Enter キー
      constexpr Button KeyNumPadEnter{ detail::InputDevice::Keyboard, 71 };
      //  テンキー - キー
      constexpr Button KeyNumPadSubtract{ detail::InputDevice::Keyboard, 72 };
      //  テンキー . キー
      constexpr Button KeyNumPadDecimal{ detail::InputDevice::Keyboard, 73 };
      //  テンキー / キー
      constexpr Button KeyNumPadDivide{ detail::InputDevice::Keyboard, 74 };
      //  F1 キー
      constexpr Button KeyF1{ detail::InputDevice::Keyboard, 75 };
      //  F2 キー
      constexpr Button KeyF2{ detail::InputDevice::Keyboard, 76 };
      //  F3 キー
      constexpr Button KeyF3{ detail::InputDevice::Keyboard, 77 };
      //  F4 キー
      constexpr Button KeyF4{ detail::InputDevice::Keyboard, 78 };
      //  F5 キー
      constexpr Button KeyF5{ detail::InputDevice::Keyboard, 79 };
      //  F6 キー
      constexpr Button KeyF6{ detail::InputDevice::Keyboard, 80 };
      //  F7 キー
      constexpr Button KeyF7{ detail::InputDevice::Keyboard, 81 };
      //  F8 キー
      constexpr Button KeyF8{ detail::InputDevice::Keyboard, 82 };
      //  F9 キー
      constexpr Button KeyF9{ detail::InputDevice::Keyboard, 83 };
      //  F10 キー
      constexpr Button KeyF10{ detail::InputDevice::Keyboard, 84 };
      //  F11 キー
      constexpr Button KeyF11{ detail::InputDevice::Keyboard, 85 };
      //  F12 キー
      constexpr Button KeyF12{ detail::InputDevice::Keyboard, 86 };
      //  F13 キー
      constexpr Button KeyF13{ detail::InputDevice::Keyboard, 87 };
      //  F14 キー
      constexpr Button KeyF14{ detail::InputDevice::Keyboard, 88 };
      //  F15 キー
      constexpr Button KeyF15{ detail::InputDevice::Keyboard, 89 };
      //  F16 キー
      constexpr Button KeyF16{ detail::InputDevice::Keyboard, 90 };
      //  F17 キー
      constexpr Button KeyF17{ detail::InputDevice::Keyboard, 91 };
      //  F18 キー
      constexpr Button KeyF18{ detail::InputDevice::Keyboard, 92 };
      //  F19 キー
      constexpr Button KeyF19{ detail::InputDevice::Keyboard, 93 };
      //  F20 キー
      constexpr Button KeyF20{ detail::InputDevice::Keyboard, 94 };
      //  F21 キー
      constexpr Button KeyF21{ detail::InputDevice::Keyboard, 95 };
      //  F22 キー
      constexpr Button KeyF22{ detail::InputDevice::Keyboard, 96 };
      //  F23 キー
      constexpr Button KeyF23{ detail::InputDevice::Keyboard, 97 };
      //  F24 キー
      constexpr Button KeyF24{ detail::InputDevice::Keyboard, 98 };
      //  NumLock キー
      constexpr Button KeyNumLock{ detail::InputDevice::Keyboard, 99 };
      //  左 Shift キー
      constexpr Button KeyLeftShift{ detail::InputDevice::Keyboard, 100 };
      //  右 Shift キー
      constexpr Button KeyRightShift{ detail::InputDevice::Keyboard, 101 };
      //  左 Control キー
      constexpr Button KeyLeftControl{ detail::InputDevice::Keyboard, 102 };
      //  右 Control キー
      constexpr Button KeyRightControl{ detail::InputDevice::Keyboard, 103 };
      //  左 Alt キー
      constexpr Button KeyLeftAlt{ detail::InputDevice::Keyboard, 104 };
      //  右 Alt キー
      constexpr Button KeyRightAlt{ detail::InputDevice::Keyboard, 105 };

      //  何かのキーが押されていればtrueを返す
      bool AnyKeyPress();
      //  何かのキーが押されたならtrueを返す
      bool AnyKeyPressed();
      //  何かのキーが離されたならtrueを返す
      bool AnyKeyReleased();
    };
  }
}
