#pragma once
#include "Button.hpp"

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
      constexpr Button KeyBackspace{ InputDevice::Keyboard, 0x08 };
      //  Tab �L�[
      constexpr Button KeyTab{ InputDevice::Keyboard, 0x09 };
      //  Enter �L�[
      constexpr Button KeyEnter{ InputDevice::Keyboard, 0x0D };
      //  Shift �L�[
      constexpr Button KeyShift{ InputDevice::Keyboard, 0x10 };
      //  Ctrl �L�[
      constexpr Button KeyControl{ InputDevice::Keyboard, 0x11 };
      //  Alt �L�[
      constexpr Button KeyAlt{ InputDevice::Keyboard, 0x12 };
      //  Pause �L�[
      constexpr Button KeyPause{ InputDevice::Keyboard, 0x13 };
      //  Cpas Lock �L�[
      constexpr Button KeyCapsLock{ InputDevice::Keyboard, 0x14 };
      //  Escape �L�[
      constexpr Button KeyEscape{ InputDevice::Keyboard, 0x1B };
      //  �X�y�[�X �L�[
      constexpr Button KeySpace{ InputDevice::Keyboard, 0x20 };
      //  PageUp �L�[
      constexpr Button KeyPageUp{ InputDevice::Keyboard, 0x21 };
      //  PageDown �L�[
      constexpr Button KeyPageDown{ InputDevice::Keyboard, 0x22 };
      //  End �L�[
      constexpr Button KeyEnd{ InputDevice::Keyboard, 0x23 };
      //  Home �L�[
      constexpr Button KeyHome{ InputDevice::Keyboard, 0x24 };
      //  �� �L�[
      constexpr Button KeyLeft{ InputDevice::Keyboard, 0x25 };
      //  �� �L�[
      constexpr Button KeyUp{ InputDevice::Keyboard, 0x26 };
      //  �� �L�[
      constexpr Button KeyRight{ InputDevice::Keyboard, 0x27 };
      //  �� �L�[
      constexpr Button KeyDown{ InputDevice::Keyboard, 0x28 };
      //  PrintScreen �L�[
      constexpr Button KeyPrintScreen{ InputDevice::Keyboard, 0x2C };
      //  Insert �L�[
      constexpr Button KeyInsert{ InputDevice::Keyboard, 0x2D };
      //  Delete �L�[
      constexpr Button KeyDelete{ InputDevice::Keyboard, 0x2E };
      //  0 �L�[
      constexpr Button Key0{ InputDevice::Keyboard, 0x30 };
      //  1 �L�[
      constexpr Button Key1{ InputDevice::Keyboard, 0x31 };
      //  2 �L�[
      constexpr Button Key2{ InputDevice::Keyboard, 0x32 };
      //  3 �L�[
      constexpr Button Key3{ InputDevice::Keyboard, 0x33 };
      //  4 �L�[
      constexpr Button Key4{ InputDevice::Keyboard, 0x34 };
      //  5 �L�[
      constexpr Button Key5{ InputDevice::Keyboard, 0x35 };
      //  6 �L�[
      constexpr Button Key6{ InputDevice::Keyboard, 0x36 };
      //  7 �L�[
      constexpr Button Key7{ InputDevice::Keyboard, 0x37 };
      //  8 �L�[
      constexpr Button Key8{ InputDevice::Keyboard, 0x38 };
      //  9 �L�[
      constexpr Button Key9{ InputDevice::Keyboard, 0x39 };
      //  A �L�[
      constexpr Button KeyA{ InputDevice::Keyboard, 0x41 };
      //  B �L�[
      constexpr Button KeyB{ InputDevice::Keyboard, 0x42 };
      //  C �L�[
      constexpr Button KeyC{ InputDevice::Keyboard, 0x43 };
      //  D �L�[
      constexpr Button KeyD{ InputDevice::Keyboard, 0x44 };
      //  E �L�[
      constexpr Button KeyE{ InputDevice::Keyboard, 0x45 };
      //  F �L�[
      constexpr Button KeyF{ InputDevice::Keyboard, 0x46 };
      //  G �L�[
      constexpr Button KeyG{ InputDevice::Keyboard, 0x47 };
      //  H �L�[
      constexpr Button KeyH{ InputDevice::Keyboard, 0x48 };
      //  I �L�[
      constexpr Button KeyI{ InputDevice::Keyboard, 0x49 };
      //  J �L�[
      constexpr Button KeyJ{ InputDevice::Keyboard, 0x4A };
      //  K �L�[
      constexpr Button KeyK{ InputDevice::Keyboard, 0x4B };
      //  L �L�[
      constexpr Button KeyL{ InputDevice::Keyboard, 0x4C };
      //  M �L�[
      constexpr Button KeyM{ InputDevice::Keyboard, 0x4D };
      //  N �L�[
      constexpr Button KeyN{ InputDevice::Keyboard, 0x4E };
      //  O �L�[
      constexpr Button KeyO{ InputDevice::Keyboard, 0x4F };
      //  P �L�[
      constexpr Button KeyP{ InputDevice::Keyboard, 0x50 };
      //  Q �L�[
      constexpr Button KeyQ{ InputDevice::Keyboard, 0x51 };
      //  R �L�[
      constexpr Button KeyR{ InputDevice::Keyboard, 0x52 };
      //  S �L�[
      constexpr Button KeyS{ InputDevice::Keyboard, 0x53 };
      //  T �L�[
      constexpr Button KeyT{ InputDevice::Keyboard, 0x54 };
      //  U �L�[
      constexpr Button KeyU{ InputDevice::Keyboard, 0x55 };
      //  V �L�[
      constexpr Button KeyV{ InputDevice::Keyboard, 0x56 };
      //  W �L�[
      constexpr Button KeyW{ InputDevice::Keyboard, 0x57 };
      //  X �L�[
      constexpr Button KeyX{ InputDevice::Keyboard, 0x58 };
      //  Y �L�[
      constexpr Button KeyY{ InputDevice::Keyboard, 0x59 };
      //  Z �L�[
      constexpr Button KeyZ{ InputDevice::Keyboard, 0x5A };
      //  �� Windows �L�[
      constexpr Button KeyLeftWindows{ InputDevice::Keyboard, 0x5B };
      //  �E Windows �L�[
      constexpr Button KeyRightWindows{ InputDevice::Keyboard, 0x5C };
      //  �e���L�[ 0 �L�[
      constexpr Button KeyNumPad0{ InputDevice::Keyboard, 0x60 };
      //  �e���L�[ 1 �L�[
      constexpr Button KeyNumPad1{ InputDevice::Keyboard, 0x61 };
      //  �e���L�[ 2 �L�[
      constexpr Button KeyNumPad2{ InputDevice::Keyboard, 0x62 };
      //  �e���L�[ 3 �L�[
      constexpr Button KeyNumPad3{ InputDevice::Keyboard, 0x63 };
      //  �e���L�[ 4 �L�[
      constexpr Button KeyNumPad4{ InputDevice::Keyboard, 0x64 };
      //  �e���L�[ 5 �L�[
      constexpr Button KeyNumPad5{ InputDevice::Keyboard, 0x65 };
      //  �e���L�[ 6 �L�[
      constexpr Button KeyNumPad6{ InputDevice::Keyboard, 0x66 };
      //  �e���L�[ 7 �L�[
      constexpr Button KeyNumPad7{ InputDevice::Keyboard, 0x67 };
      //  �e���L�[ 8 �L�[
      constexpr Button KeyNumPad8{ InputDevice::Keyboard, 0x68 };
      //  �e���L�[ 9 �L�[
      constexpr Button KeyNumPad9{ InputDevice::Keyboard, 0x69 };
      //  �e���L�[ * �L�[
      constexpr Button KeyNumPadMultiply{ InputDevice::Keyboard, 0x6A };
      //  �e���L�[ + �L�[
      constexpr Button KeyNumPadAdd{ InputDevice::Keyboard, 0x6B };
      //  �e���L�[ Enter �L�[
      constexpr Button KeyNumPadEnter{ InputDevice::Keyboard, 0x6C };
      //  �e���L�[ - �L�[
      constexpr Button KeyNumPadSubtract{ InputDevice::Keyboard, 0x6D };
      //  �e���L�[ . �L�[
      constexpr Button KeyNumPadDecimal{ InputDevice::Keyboard, 0x6E };
      //  �e���L�[ / �L�[
      constexpr Button KeyNumPadDivide{ InputDevice::Keyboard, 0x6F };
      //  F1 �L�[
      constexpr Button KeyF1{ InputDevice::Keyboard, 0x70 };
      //  F2 �L�[
      constexpr Button KeyF2{ InputDevice::Keyboard, 0x71 };
      //  F3 �L�[
      constexpr Button KeyF3{ InputDevice::Keyboard, 0x72 };
      //  F4 �L�[
      constexpr Button KeyF4{ InputDevice::Keyboard, 0x73 };
      //  F5 �L�[
      constexpr Button KeyF5{ InputDevice::Keyboard, 0x74 };
      //  F6 �L�[
      constexpr Button KeyF6{ InputDevice::Keyboard, 0x75 };
      //  F7 �L�[
      constexpr Button KeyF7{ InputDevice::Keyboard, 0x76 };
      //  F8 �L�[
      constexpr Button KeyF8{ InputDevice::Keyboard, 0x77 };
      //  F9 �L�[
      constexpr Button KeyF9{ InputDevice::Keyboard, 0x78 };
      //  F10 �L�[
      constexpr Button KeyF10{ InputDevice::Keyboard, 0x79 };
      //  F11 �L�[
      constexpr Button KeyF11{ InputDevice::Keyboard, 0x7A };
      //  F12 �L�[
      constexpr Button KeyF12{ InputDevice::Keyboard, 0x7B };
      //  F13 �L�[
      constexpr Button KeyF13{ InputDevice::Keyboard, 0x7C };
      //  F14 �L�[
      constexpr Button KeyF14{ InputDevice::Keyboard, 0x7D };
      //  F15 �L�[
      constexpr Button KeyF15{ InputDevice::Keyboard, 0x7E };
      //  F16 �L�[
      constexpr Button KeyF16{ InputDevice::Keyboard, 0x7F };
      //  F17 �L�[
      constexpr Button KeyF17{ InputDevice::Keyboard, 0x80 };
      //  F18 �L�[
      constexpr Button KeyF18{ InputDevice::Keyboard, 0x81 };
      //  F19 �L�[
      constexpr Button KeyF19{ InputDevice::Keyboard, 0x82 };
      //  F20 �L�[
      constexpr Button KeyF20{ InputDevice::Keyboard, 0x83 };
      //  F21 �L�[
      constexpr Button KeyF21{ InputDevice::Keyboard, 0x84 };
      //  F22 �L�[
      constexpr Button KeyF22{ InputDevice::Keyboard, 0x85 };
      //  F23 �L�[
      constexpr Button KeyF23{ InputDevice::Keyboard, 0x86 };
      //  F24 �L�[
      constexpr Button KeyF24{ InputDevice::Keyboard, 0x87 };
      //  NumLock �L�[
      constexpr Button KeyNumLock{ InputDevice::Keyboard, 0x90 };
      //  �� Shift �L�[
      constexpr Button KeyLeftShift{ InputDevice::Keyboard, 0xA0 };
      //  �E Shift �L�[
      constexpr Button KeyRightShift{ InputDevice::Keyboard, 0xA1 };
      //  �� Control �L�[
      constexpr Button KeyLeftControl{ InputDevice::Keyboard, 0xA2 };
      //  �E Control �L�[
      constexpr Button KeyRightControl{ InputDevice::Keyboard, 0xA3 };
      //  �� Alt �L�[
      constexpr Button KeyLeftAlt{ InputDevice::Keyboard, 0xA4 };
      //  �E Alt �L�[
      constexpr Button KeyRightAlt{ InputDevice::Keyboard, 0xA5 };

      //  �����̃L�[��������Ă����true��Ԃ�
      bool AnyKeyPress();
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyPressed();
      //  �����̃L�[�������ꂽ�Ȃ�true��Ԃ�
      bool AnyKeyReleased();
    };
  }
}
