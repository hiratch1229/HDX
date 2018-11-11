#pragma once
#include "../../../Include/Button.hpp"
#include "../../../Include/Type2.hpp"

namespace detail
{
  //  XInputで使うボタン
  enum class XInputButtons
  {
    Up,
    Down,
    Left,
    Right,
    Start,
    Select,
    LeftStick,
    RightStick,
    LeftShoulder,
    RightShoulder,
    A,
    B,
    X,
    Y,

    Num
  };

  constexpr int kXInputButtonsCode[] = {
    0x0001, //  XINPUT_GAMEPAD_DPAD_UP
    0x0002, //  XINPUT_GAMEPAD_DPAD_DOWN
    0x0004, //  XINPUT_GAMEPAD_DPAD_LEFT
    0x0008, //  XINPUT_GAMEPAD_DPAD_RIGHT
    0x0010, //  XINPUT_GAMEPAD_START
    0x0020, //  XINPUT_GAMEPAD_BACK
    0x0040, //  XINPUT_GAMEPAD_LEFT_THUMB
    0x0080, //  XINPUT_GAMEPAD_RIGHT_THUMB
    0x0100, //  XINPUT_GAMEPAD_LEFT_SHOULDER
    0x0200, //  XINPUT_GAMEPAD_RIGHT_SHOULDER
    0x1000, //  XINPUT_GAMEPAD_A
    0x2000, //  XINPUT_GAMEPAD_B
    0x4000, //  XINPUT_GAMEPAD_X
    0x8000, //  XINPUT_GAMEPAD_Y
  };

  class IXInput
  {
  public:
    static constexpr int kButtonNum = sizeof(kXInputButtonsCode) / sizeof(kXInputButtonsCode[0]);
    static_assert(static_cast<int>(XInputButtons::Num) == kButtonNum, "Number of XInputButtons And kXInputButtonsCode matches.");
  private:
    struct Status;
  private:
    //Status Status_[kMaxControllerNum];
    Status* Status_;
  public:
    //  押されているならtrueを返す
    bool Press(int _Number, int _Index)const;
    //  押された瞬間ならtrueを返す
    bool Pressed(int _Number, int _Index)const;
    //  離された瞬間ならtrueを返す
    bool Released(int _Number, int _Index)const;
    //  押されていないならtrueを返す
    bool Release(int _Number, int _Index)const;
  public:
    //  何かのボタンが押されていればtrueを返す
    bool AnyButtonPress(int _Index)const;
    //  何かのボタンが押されたならtrueを返す
    bool AnyButtonPressed(int _Index)const;
    //  何かのボタンが離されたならtrueを返す
    bool AnyButtonReleased(int _Index)const;
  public:
    //  左スティックの入力状態を取得
    hdx::float2 GetLeftStick(int _Index, float _DeadZone)const;
    //  右スティックの入力状態を取得
    hdx::float2 GetRightStick(int _Index, float _DeadZone)const;
  public:
    //  左トリガーの入力状態を取得
    float GetLeftTrigger(int _Index, float _DeadZone)const;
    //  右トリガーの入力状態を取得
    float GetRightTrigger(int _Index, float _DeadZone)const;
  public:
    //  接続されているか確認
    bool isConnect(int _Index)const;
    //  コントローラを振動させます
    void SetVibration(int _Index, float _Speed)const;
    //  コントローラの振動を止めます
    void StopVibration(int _Index)const;
  public:
    //  初期化
    IXInput();
    //  状態の更新
    void Update();
    //  解放
    ~IXInput();
  };
}
