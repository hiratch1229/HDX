#pragma once
#include "Button.hpp"

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
      constexpr Button KeyBackspace{ InputDevice::Keyboard, 0x08 };
      //  Tab キー
      constexpr Button KeyTab{ InputDevice::Keyboard, 0x09 };
      //  Enter キー
      constexpr Button KeyEnter{ InputDevice::Keyboard, 0x0D };
      //  Shift キー
      constexpr Button KeyShift{ InputDevice::Keyboard, 0x10 };
      //  Ctrl キー
      constexpr Button KeyControl{ InputDevice::Keyboard, 0x11 };
      //  Alt キー
      constexpr Button KeyAlt{ InputDevice::Keyboard, 0x12 };
      //  Pause キー
      constexpr Button KeyPause{ InputDevice::Keyboard, 0x13 };
      //  Cpas Lock キー
      constexpr Button KeyCapsLock{ InputDevice::Keyboard, 0x14 };
      //  Escape キー
      constexpr Button KeyEscape{ InputDevice::Keyboard, 0x1B };
      //  スペース キー
      constexpr Button KeySpace{ InputDevice::Keyboard, 0x20 };
      //  PageUp キー
      constexpr Button KeyPageUp{ InputDevice::Keyboard, 0x21 };
      //  PageDown キー
      constexpr Button KeyPageDown{ InputDevice::Keyboard, 0x22 };
      //  End キー
      constexpr Button KeyEnd{ InputDevice::Keyboard, 0x23 };
      //  Home キー
      constexpr Button KeyHome{ InputDevice::Keyboard, 0x24 };
      //  ← キー
      constexpr Button KeyLeft{ InputDevice::Keyboard, 0x25 };
      //  ↑ キー
      constexpr Button KeyUp{ InputDevice::Keyboard, 0x26 };
      //  → キー
      constexpr Button KeyRight{ InputDevice::Keyboard, 0x27 };
      //  ↓ キー
      constexpr Button KeyDown{ InputDevice::Keyboard, 0x28 };
      //  PrintScreen キー
      constexpr Button KeyPrintScreen{ InputDevice::Keyboard, 0x2C };
      //  Insert キー
      constexpr Button KeyInsert{ InputDevice::Keyboard, 0x2D };
      //  Delete キー
      constexpr Button KeyDelete{ InputDevice::Keyboard, 0x2E };
      //  0 キー
      constexpr Button Key0{ InputDevice::Keyboard, 0x30 };
      //  1 キー
      constexpr Button Key1{ InputDevice::Keyboard, 0x31 };
      //  2 キー
      constexpr Button Key2{ InputDevice::Keyboard, 0x32 };
      //  3 キー
      constexpr Button Key3{ InputDevice::Keyboard, 0x33 };
      //  4 キー
      constexpr Button Key4{ InputDevice::Keyboard, 0x34 };
      //  5 キー
      constexpr Button Key5{ InputDevice::Keyboard, 0x35 };
      //  6 キー
      constexpr Button Key6{ InputDevice::Keyboard, 0x36 };
      //  7 キー
      constexpr Button Key7{ InputDevice::Keyboard, 0x37 };
      //  8 キー
      constexpr Button Key8{ InputDevice::Keyboard, 0x38 };
      //  9 キー
      constexpr Button Key9{ InputDevice::Keyboard, 0x39 };
      //  A キー
      constexpr Button KeyA{ InputDevice::Keyboard, 0x41 };
      //  B キー
      constexpr Button KeyB{ InputDevice::Keyboard, 0x42 };
      //  C キー
      constexpr Button KeyC{ InputDevice::Keyboard, 0x43 };
      //  D キー
      constexpr Button KeyD{ InputDevice::Keyboard, 0x44 };
      //  E キー
      constexpr Button KeyE{ InputDevice::Keyboard, 0x45 };
      //  F キー
      constexpr Button KeyF{ InputDevice::Keyboard, 0x46 };
      //  G キー
      constexpr Button KeyG{ InputDevice::Keyboard, 0x47 };
      //  H キー
      constexpr Button KeyH{ InputDevice::Keyboard, 0x48 };
      //  I キー
      constexpr Button KeyI{ InputDevice::Keyboard, 0x49 };
      //  J キー
      constexpr Button KeyJ{ InputDevice::Keyboard, 0x4A };
      //  K キー
      constexpr Button KeyK{ InputDevice::Keyboard, 0x4B };
      //  L キー
      constexpr Button KeyL{ InputDevice::Keyboard, 0x4C };
      //  M キー
      constexpr Button KeyM{ InputDevice::Keyboard, 0x4D };
      //  N キー
      constexpr Button KeyN{ InputDevice::Keyboard, 0x4E };
      //  O キー
      constexpr Button KeyO{ InputDevice::Keyboard, 0x4F };
      //  P キー
      constexpr Button KeyP{ InputDevice::Keyboard, 0x50 };
      //  Q キー
      constexpr Button KeyQ{ InputDevice::Keyboard, 0x51 };
      //  R キー
      constexpr Button KeyR{ InputDevice::Keyboard, 0x52 };
      //  S キー
      constexpr Button KeyS{ InputDevice::Keyboard, 0x53 };
      //  T キー
      constexpr Button KeyT{ InputDevice::Keyboard, 0x54 };
      //  U キー
      constexpr Button KeyU{ InputDevice::Keyboard, 0x55 };
      //  V キー
      constexpr Button KeyV{ InputDevice::Keyboard, 0x56 };
      //  W キー
      constexpr Button KeyW{ InputDevice::Keyboard, 0x57 };
      //  X キー
      constexpr Button KeyX{ InputDevice::Keyboard, 0x58 };
      //  Y キー
      constexpr Button KeyY{ InputDevice::Keyboard, 0x59 };
      //  Z キー
      constexpr Button KeyZ{ InputDevice::Keyboard, 0x5A };
      //  左 Windows キー
      constexpr Button KeyLeftWindows{ InputDevice::Keyboard, 0x5B };
      //  右 Windows キー
      constexpr Button KeyRightWindows{ InputDevice::Keyboard, 0x5C };
      //  テンキー 0 キー
      constexpr Button KeyNumPad0{ InputDevice::Keyboard, 0x60 };
      //  テンキー 1 キー
      constexpr Button KeyNumPad1{ InputDevice::Keyboard, 0x61 };
      //  テンキー 2 キー
      constexpr Button KeyNumPad2{ InputDevice::Keyboard, 0x62 };
      //  テンキー 3 キー
      constexpr Button KeyNumPad3{ InputDevice::Keyboard, 0x63 };
      //  テンキー 4 キー
      constexpr Button KeyNumPad4{ InputDevice::Keyboard, 0x64 };
      //  テンキー 5 キー
      constexpr Button KeyNumPad5{ InputDevice::Keyboard, 0x65 };
      //  テンキー 6 キー
      constexpr Button KeyNumPad6{ InputDevice::Keyboard, 0x66 };
      //  テンキー 7 キー
      constexpr Button KeyNumPad7{ InputDevice::Keyboard, 0x67 };
      //  テンキー 8 キー
      constexpr Button KeyNumPad8{ InputDevice::Keyboard, 0x68 };
      //  テンキー 9 キー
      constexpr Button KeyNumPad9{ InputDevice::Keyboard, 0x69 };
      //  テンキー * キー
      constexpr Button KeyNumPadMultiply{ InputDevice::Keyboard, 0x6A };
      //  テンキー + キー
      constexpr Button KeyNumPadAdd{ InputDevice::Keyboard, 0x6B };
      //  テンキー Enter キー
      constexpr Button KeyNumPadEnter{ InputDevice::Keyboard, 0x6C };
      //  テンキー - キー
      constexpr Button KeyNumPadSubtract{ InputDevice::Keyboard, 0x6D };
      //  テンキー . キー
      constexpr Button KeyNumPadDecimal{ InputDevice::Keyboard, 0x6E };
      //  テンキー / キー
      constexpr Button KeyNumPadDivide{ InputDevice::Keyboard, 0x6F };
      //  F1 キー
      constexpr Button KeyF1{ InputDevice::Keyboard, 0x70 };
      //  F2 キー
      constexpr Button KeyF2{ InputDevice::Keyboard, 0x71 };
      //  F3 キー
      constexpr Button KeyF3{ InputDevice::Keyboard, 0x72 };
      //  F4 キー
      constexpr Button KeyF4{ InputDevice::Keyboard, 0x73 };
      //  F5 キー
      constexpr Button KeyF5{ InputDevice::Keyboard, 0x74 };
      //  F6 キー
      constexpr Button KeyF6{ InputDevice::Keyboard, 0x75 };
      //  F7 キー
      constexpr Button KeyF7{ InputDevice::Keyboard, 0x76 };
      //  F8 キー
      constexpr Button KeyF8{ InputDevice::Keyboard, 0x77 };
      //  F9 キー
      constexpr Button KeyF9{ InputDevice::Keyboard, 0x78 };
      //  F10 キー
      constexpr Button KeyF10{ InputDevice::Keyboard, 0x79 };
      //  F11 キー
      constexpr Button KeyF11{ InputDevice::Keyboard, 0x7A };
      //  F12 キー
      constexpr Button KeyF12{ InputDevice::Keyboard, 0x7B };
      //  F13 キー
      constexpr Button KeyF13{ InputDevice::Keyboard, 0x7C };
      //  F14 キー
      constexpr Button KeyF14{ InputDevice::Keyboard, 0x7D };
      //  F15 キー
      constexpr Button KeyF15{ InputDevice::Keyboard, 0x7E };
      //  F16 キー
      constexpr Button KeyF16{ InputDevice::Keyboard, 0x7F };
      //  F17 キー
      constexpr Button KeyF17{ InputDevice::Keyboard, 0x80 };
      //  F18 キー
      constexpr Button KeyF18{ InputDevice::Keyboard, 0x81 };
      //  F19 キー
      constexpr Button KeyF19{ InputDevice::Keyboard, 0x82 };
      //  F20 キー
      constexpr Button KeyF20{ InputDevice::Keyboard, 0x83 };
      //  F21 キー
      constexpr Button KeyF21{ InputDevice::Keyboard, 0x84 };
      //  F22 キー
      constexpr Button KeyF22{ InputDevice::Keyboard, 0x85 };
      //  F23 キー
      constexpr Button KeyF23{ InputDevice::Keyboard, 0x86 };
      //  F24 キー
      constexpr Button KeyF24{ InputDevice::Keyboard, 0x87 };
      //  NumLock キー
      constexpr Button KeyNumLock{ InputDevice::Keyboard, 0x90 };
      //  左 Shift キー
      constexpr Button KeyLeftShift{ InputDevice::Keyboard, 0xA0 };
      //  右 Shift キー
      constexpr Button KeyRightShift{ InputDevice::Keyboard, 0xA1 };
      //  左 Control キー
      constexpr Button KeyLeftControl{ InputDevice::Keyboard, 0xA2 };
      //  右 Control キー
      constexpr Button KeyRightControl{ InputDevice::Keyboard, 0xA3 };
      //  左 Alt キー
      constexpr Button KeyLeftAlt{ InputDevice::Keyboard, 0xA4 };
      //  右 Alt キー
      constexpr Button KeyRightAlt{ InputDevice::Keyboard, 0xA5 };

      //  何かのキーが押されていればtrueを返す
      bool AnyKeyPress();
      //  何かのキーが押されたならtrueを返す
      bool AnyKeyPressed();
      //  何かのキーが離されたならtrueを返す
      bool AnyKeyReleased();
    };
  }
}
