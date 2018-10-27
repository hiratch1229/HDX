#pragma once

namespace detail
{
  enum class InputState;

  //  キーボードで使う仮想キー
  enum class KeyboardVirtualKey
  {
    Backspace,
    Tab,
    Enter,
    Shift,
    Control,
    Alt,
    Pause,
    CapsLock,
    Escape,
    Space,
    PageUp,
    PageDown,
    End,
    Home,
    Left,
    Up,
    Right,
    Down,
    PrintScreen,
    Insert,
    Delete,
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    D8,
    D9,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LeftWindows,
    RightWindows,
    NumPad0,
    NumPad1,
    NumPad2,
    NumPad3,
    NumPad4,
    NumPad5,
    NumPad6,
    NumPad7,
    NumPad8,
    NumPad9,
    NumPadMultiply,
    NumPadAdd,
    NumPadEnter,
    NumPadSubtract,
    NumPadDecimal,
    NumPadDivide,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    NumLock,
    LeftShift,
    RightShift,
    LeftControl,
    RightControl,
    LeftAlt,
    RightAlt,

    Num //  個数
  };

  //  キーボードで使う仮想キーの値
  static constexpr int kKeyboardVirtualKeyCode[] = {
    0x08, //  VK_BACK
    0x09, //  VK_TAB
    0x0D, //  VK_RETURN
    0x10, //  VK_SHIFT
    0x11, //  VK_CONTROL
    0x12, //  VK_MENU
    0x13, //  VK_PAUSE
    0x14, //  VK_CAPITAL
    0x1B, //  VK_ESCAPE
    0x20, //  VK_SPACE
    0x21, //  VK_PRIOR
    0x22, //  VK_NEXT
    0x23, //  VK_END
    0x24, //  VK_HOME
    0x25, //  VK_LEFT
    0x26, //  VK_UP
    0x27, //  VK_RIGHT
    0x28, //  VK_DOWN
    0x2C, //  VK_SNAPSHOT
    0x2D, //  VK_INSERT
    0x2E, //  VK_DELETE
    0x30, //  0
    0x31, //  1
    0x32, //  2
    0x33, //  3
    0x34, //  4
    0x35, //  5
    0x36, //  6
    0x37, //  7
    0x38, //  8
    0x39, //  9
    0x41, //  A
    0x42, //  B
    0x43, //  C
    0x44, //  D
    0x45, //  E
    0x46, //  F
    0x47, //  G
    0x48, //  H
    0x49, //  I
    0x4A, //  J
    0x4B, //  K
    0x4C, //  L
    0x4D, //  N
    0x4E, //  M
    0x4F, //  O
    0x50, //  P
    0x51, //  Q
    0x52, //  R
    0x53, //  S
    0x54, //  T
    0x55, //  U
    0x56, //  V
    0x57, //  W
    0x58, //  X
    0x59, //  Y
    0x5A, //  Z
    0x5B, //  VK_LWIN
    0x5C, //  VK_RWIN
    0x60, //  VK_NUMPAD0
    0x61, //  VK_NUMPAD1
    0x62, //  VK_NUMPAD2
    0x63, //  VK_NUMPAD3
    0x64, //  VK_NUMPAD4
    0x65, //  VK_NUMPAD5
    0x66, //  VK_NUMPAD6
    0x67, //  VK_NUMPAD7
    0x68, //  VK_NUMPAD8
    0x69, //  VK_NUMPAD9
    0x6A, //  VK_MULTIPLY
    0x6B, //  VK_ADD
    0x6C, //  VK_SEPARATOR
    0x6D, //  VK_SUBTRACT
    0x6E, //  VK_DECIMAL
    0x6F, //  VK_DIVIDE
    0x70, //  VK_F1
    0x71, //  VK_F2
    0x72, //  VK_F3
    0x73, //  VK_F4
    0x74, //  VK_F5
    0x75, //  VK_F6
    0x76, //  VK_F7
    0x77, //  VK_F8
    0x78, //  VK_F9
    0x79, //  VK_F10
    0x7A, //  VK_F11
    0x7B, //  VK_F12
    0x7C, //  VK_F13
    0x7D, //  VK_F14
    0x7E, //  VK_F15
    0x7F, //  VK_F16
    0x80, //  VK_F17
    0x81, //  VK_F18
    0x82, //  VK_F19
    0x83, //  VK_F20
    0x84, //  VK_F21
    0x85, //  VK_F22
    0x86, //  VK_F23
    0x87, //  VK_F24
    0x90, //  VK_NUMLOCK
    0xA0, //  VK_LSHIFT
    0xA1, //  VK_RSHIFT
    0xA2, //  VK_LCONTROL
    0xA3, //  VK_RCONTROL
    0xA4, //  VK_LMENU
    0xA5, //  VK_RMENU
  };

  //  キーボード
  class IKeyboard 
  {
    //  使用されるキーの個数
    static constexpr int kKeyNum = sizeof(kKeyboardVirtualKeyCode) / sizeof(kKeyboardVirtualKeyCode[0]);
    static_assert(static_cast<int>(KeyboardVirtualKey::Num) == kKeyNum, "Number of KeyboardVirtualKey And kKeyboardVirtualKeyCode matches.");
  private:
    //  入力状態
    InputState* InputStatus_;
  public:
    //  押されているならtrueを返す
    bool Press(int _Number)const;
    //  押された瞬間ならtrueを返す
    bool Pressed(int _Number)const;
    //  離された瞬間ならtrueを返す
    bool Released(int _Number)const;
    //  押されていないならtrueを返す
    bool Release(int _Number)const;
  public:
    //  何かのキーが押されていればtrueを返す
    bool AnyKeyPress()const;
    //  何かのキーが押されたならtrueを返す
    bool AnyKeyPressed()const;
    //  何かのキーが離されたならtrueを返す
    bool AnyKeyReleased()const;
  public:
    //  初期化
    IKeyboard();
    //  状態の更新
    void Update();
    //  解放
    ~IKeyboard();
  };
}
