#pragma once
#include <HDX/Input/Button.hpp>
#include <HDX/Input/InputState.hpp>

//  ���C�u����
namespace hdx
{
  //  ���͌n
  namespace Input
  {
    //  �L�[�{�[�h
    namespace Keyboard
    {
      //  Backspace �L�[
      constexpr Button KeyBackspace{ detail::InputDevice::Keyboard, 0 };
      //  Tab �L�[
      constexpr Button KeyTab{ detail::InputDevice::Keyboard, 1 };
      //  Enter �L�[
      constexpr Button KeyEnter{ detail::InputDevice::Keyboard, 2 };
      //  Shift �L�[
      constexpr Button KeyShift{ detail::InputDevice::Keyboard, 3 };
      //  Ctrl �L�[
      constexpr Button KeyControl{ detail::InputDevice::Keyboard, 4 };
      //  Alt �L�[
      constexpr Button KeyAlt{ detail::InputDevice::Keyboard, 5 };
      //  Pause �L�[
      constexpr Button KeyPause{ detail::InputDevice::Keyboard, 6 };
      //  Cpas Lock �L�[
      constexpr Button KeyCapsLock{ detail::InputDevice::Keyboard, 7 };
      //  Escape �L�[
      constexpr Button KeyEscape{ detail::InputDevice::Keyboard, 8 };
      //  �X�y�[�X �L�[
      constexpr Button KeySpace{ detail::InputDevice::Keyboard, 9 };
      //  PageUp �L�[
      constexpr Button KeyPageUp{ detail::InputDevice::Keyboard, 10 };
      //  PageDown �L�[
      constexpr Button KeyPageDown{ detail::InputDevice::Keyboard, 11 };
      //  End �L�[
      constexpr Button KeyEnd{ detail::InputDevice::Keyboard, 12 };
      //  Home �L�[
      constexpr Button KeyHome{ detail::InputDevice::Keyboard, 13 };
      //  �� �L�[
      constexpr Button KeyLeft{ detail::InputDevice::Keyboard, 14 };
      //  �� �L�[
      constexpr Button KeyUp{ detail::InputDevice::Keyboard, 15 };
      //  �� �L�[
      constexpr Button KeyRight{ detail::InputDevice::Keyboard, 16 };
      //  �� �L�[
      constexpr Button KeyDown{ detail::InputDevice::Keyboard, 17 };
      //  PrintScreen �L�[
      constexpr Button KeyPrintScreen{ detail::InputDevice::Keyboard, 18 };
      //  Insert �L�[
      constexpr Button KeyInsert{ detail::InputDevice::Keyboard, 19 };
      //  Delete �L�[
      constexpr Button KeyDelete{ detail::InputDevice::Keyboard, 20 };
      //  0 �L�[
      constexpr Button Key0{ detail::InputDevice::Keyboard, 21 };
      //  1 �L�[
      constexpr Button Key1{ detail::InputDevice::Keyboard, 22 };
      //  2 �L�[
      constexpr Button Key2{ detail::InputDevice::Keyboard, 23 };
      //  3 �L�[
      constexpr Button Key3{ detail::InputDevice::Keyboard, 24 };
      //  4 �L�[
      constexpr Button Key4{ detail::InputDevice::Keyboard, 25 };
      //  5 �L�[
      constexpr Button Key5{ detail::InputDevice::Keyboard, 26 };
      //  6 �L�[
      constexpr Button Key6{ detail::InputDevice::Keyboard, 27 };
      //  7 �L�[
      constexpr Button Key7{ detail::InputDevice::Keyboard, 28 };
      //  8 �L�[
      constexpr Button Key8{ detail::InputDevice::Keyboard, 29 };
      //  9 �L�[
      constexpr Button Key9{ detail::InputDevice::Keyboard, 30 };
      //  A �L�[
      constexpr Button KeyA{ detail::InputDevice::Keyboard, 31 };
      //  B �L�[
      constexpr Button KeyB{ detail::InputDevice::Keyboard, 32 };
      //  C �L�[
      constexpr Button KeyC{ detail::InputDevice::Keyboard, 33 };
      //  D �L�[
      constexpr Button KeyD{ detail::InputDevice::Keyboard, 34 };
      //  E �L�[
      constexpr Button KeyE{ detail::InputDevice::Keyboard, 35 };
      //  F �L�[
      constexpr Button KeyF{ detail::InputDevice::Keyboard, 36 };
      //  G �L�[
      constexpr Button KeyG{ detail::InputDevice::Keyboard, 37 };
      //  H �L�[
      constexpr Button KeyH{ detail::InputDevice::Keyboard, 38 };
      //  I �L�[
      constexpr Button KeyI{ detail::InputDevice::Keyboard, 39 };
      //  J �L�[
      constexpr Button KeyJ{ detail::InputDevice::Keyboard, 40 };
      //  K �L�[
      constexpr Button KeyK{ detail::InputDevice::Keyboard, 41 };
      //  L �L�[
      constexpr Button KeyL{ detail::InputDevice::Keyboard, 42 };
      //  M �L�[
      constexpr Button KeyM{ detail::InputDevice::Keyboard, 43 };
      //  N �L�[
      constexpr Button KeyN{ detail::InputDevice::Keyboard, 44 };
      //  O �L�[
      constexpr Button KeyO{ detail::InputDevice::Keyboard, 45 };
      //  P �L�[
      constexpr Button KeyP{ detail::InputDevice::Keyboard, 46 };
      //  Q �L�[
      constexpr Button KeyQ{ detail::InputDevice::Keyboard, 47 };
      //  R �L�[
      constexpr Button KeyR{ detail::InputDevice::Keyboard, 48 };
      //  S �L�[
      constexpr Button KeyS{ detail::InputDevice::Keyboard, 49 };
      //  T �L�[
      constexpr Button KeyT{ detail::InputDevice::Keyboard, 50 };
      //  U �L�[
      constexpr Button KeyU{ detail::InputDevice::Keyboard, 51 };
      //  V �L�[
      constexpr Button KeyV{ detail::InputDevice::Keyboard, 52 };
      //  W �L�[
      constexpr Button KeyW{ detail::InputDevice::Keyboard, 53 };
      //  X �L�[
      constexpr Button KeyX{ detail::InputDevice::Keyboard, 54 };
      //  Y �L�[
      constexpr Button KeyY{ detail::InputDevice::Keyboard, 55 };
      //  Z �L�[
      constexpr Button KeyZ{ detail::InputDevice::Keyboard, 56 };
      //  �� Windows �L�[
      constexpr Button KeyLeftWindows{ detail::InputDevice::Keyboard, 57 };
      //  �E Windows �L�[
      constexpr Button KeyRightWindows{ detail::InputDevice::Keyboard, 58 };
      //  �e���L�[ 0 �L�[
      constexpr Button KeyNumPad0{ detail::InputDevice::Keyboard, 59 };
      //  �e���L�[ 1 �L�[
      constexpr Button KeyNumPad1{ detail::InputDevice::Keyboard, 60 };
      //  �e���L�[ 2 �L�[
      constexpr Button KeyNumPad2{ detail::InputDevice::Keyboard, 61 };
      //  �e���L�[ 3 �L�[
      constexpr Button KeyNumPad3{ detail::InputDevice::Keyboard, 62 };
      //  �e���L�[ 4 �L�[
      constexpr Button KeyNumPad4{ detail::InputDevice::Keyboard, 63 };
      //  �e���L�[ 5 �L�[
      constexpr Button KeyNumPad5{ detail::InputDevice::Keyboard, 64 };
      //  �e���L�[ 6 �L�[
      constexpr Button KeyNumPad6{ detail::InputDevice::Keyboard, 65 };
      //  �e���L�[ 7 �L�[
      constexpr Button KeyNumPad7{ detail::InputDevice::Keyboard, 66 };
      //  �e���L�[ 8 �L�[
      constexpr Button KeyNumPad8{ detail::InputDevice::Keyboard, 67 };
      //  �e���L�[ 9 �L�[
      constexpr Button KeyNumPad9{ detail::InputDevice::Keyboard, 68 };
      //  �e���L�[ * �L�[
      constexpr Button KeyNumPadMultiply{ detail::InputDevice::Keyboard, 69 };
      //  �e���L�[ + �L�[
      constexpr Button KeyNumPadAdd{ detail::InputDevice::Keyboard, 70 };
      //  �e���L�[ Enter �L�[
      constexpr Button KeyNumPadEnter{ detail::InputDevice::Keyboard, 71 };
      //  �e���L�[ - �L�[
      constexpr Button KeyNumPadSubtract{ detail::InputDevice::Keyboard, 72 };
      //  �e���L�[ . �L�[
      constexpr Button KeyNumPadDecimal{ detail::InputDevice::Keyboard, 73 };
      //  �e���L�[ / �L�[
      constexpr Button KeyNumPadDivide{ detail::InputDevice::Keyboard, 74 };
      //  F1 �L�[
      constexpr Button KeyF1{ detail::InputDevice::Keyboard, 75 };
      //  F2 �L�[
      constexpr Button KeyF2{ detail::InputDevice::Keyboard, 76 };
      //  F3 �L�[
      constexpr Button KeyF3{ detail::InputDevice::Keyboard, 77 };
      //  F4 �L�[
      constexpr Button KeyF4{ detail::InputDevice::Keyboard, 78 };
      //  F5 �L�[
      constexpr Button KeyF5{ detail::InputDevice::Keyboard, 79 };
      //  F6 �L�[
      constexpr Button KeyF6{ detail::InputDevice::Keyboard, 80 };
      //  F7 �L�[
      constexpr Button KeyF7{ detail::InputDevice::Keyboard, 81 };
      //  F8 �L�[
      constexpr Button KeyF8{ detail::InputDevice::Keyboard, 82 };
      //  F9 �L�[
      constexpr Button KeyF9{ detail::InputDevice::Keyboard, 83 };
      //  F10 �L�[
      constexpr Button KeyF10{ detail::InputDevice::Keyboard, 84 };
      //  F11 �L�[
      constexpr Button KeyF11{ detail::InputDevice::Keyboard, 85 };
      //  F12 �L�[
      constexpr Button KeyF12{ detail::InputDevice::Keyboard, 86 };
      //  F13 �L�[
      constexpr Button KeyF13{ detail::InputDevice::Keyboard, 87 };
      //  F14 �L�[
      constexpr Button KeyF14{ detail::InputDevice::Keyboard, 88 };
      //  F15 �L�[
      constexpr Button KeyF15{ detail::InputDevice::Keyboard, 89 };
      //  F16 �L�[
      constexpr Button KeyF16{ detail::InputDevice::Keyboard, 90 };
      //  F17 �L�[
      constexpr Button KeyF17{ detail::InputDevice::Keyboard, 91 };
      //  F18 �L�[
      constexpr Button KeyF18{ detail::InputDevice::Keyboard, 92 };
      //  F19 �L�[
      constexpr Button KeyF19{ detail::InputDevice::Keyboard, 93 };
      //  F20 �L�[
      constexpr Button KeyF20{ detail::InputDevice::Keyboard, 94 };
      //  F21 �L�[
      constexpr Button KeyF21{ detail::InputDevice::Keyboard, 95 };
      //  F22 �L�[
      constexpr Button KeyF22{ detail::InputDevice::Keyboard, 96 };
      //  F23 �L�[
      constexpr Button KeyF23{ detail::InputDevice::Keyboard, 97 };
      //  F24 �L�[
      constexpr Button KeyF24{ detail::InputDevice::Keyboard, 98 };
      //  NumLock �L�[
      constexpr Button KeyNumLock{ detail::InputDevice::Keyboard, 99 };
      //  �� Shift �L�[
      constexpr Button KeyLeftShift{ detail::InputDevice::Keyboard, 100 };
      //  �E Shift �L�[
      constexpr Button KeyRightShift{ detail::InputDevice::Keyboard, 101 };
      //  �� Control �L�[
      constexpr Button KeyLeftControl{ detail::InputDevice::Keyboard, 102 };
      //  �E Control �L�[
      constexpr Button KeyRightControl{ detail::InputDevice::Keyboard, 103 };
      //  �� Alt �L�[
      constexpr Button KeyLeftAlt{ detail::InputDevice::Keyboard, 104 };
      //  �E Alt �L�[
      constexpr Button KeyRightAlt{ detail::InputDevice::Keyboard, 105 };

      //  �����̃L�[��������Ă����true��Ԃ�
      bool AnyKeyPress();
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyPressed();
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyReleased();
    };
  }
}
