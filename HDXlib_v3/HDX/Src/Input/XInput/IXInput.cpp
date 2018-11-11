#include "IXInput.hpp"

#include "../InputState.hpp"

#include "../../../Include/Math.hpp"

#include <Windows.h>
#include <Xinput.h>

namespace detail
{
  struct IXInput::Status
  {
    bool isConnect_;
    //  入力状態
    InputState InputStatus_[kButtonNum];
    //  左のアナログスティックの入力状態
    hdx::float2 LeftStick_;
    //  右のアナログスティックの入力状態
    hdx::float2 RightStick_;
    //  左のトリガーの入力状態
    float LeftTrigger_;
    //  右のトリガーの入力状態
    float RightTrigger_;
  };

  //  初期化
  IXInput::IXInput()
  {
    Status_ = new Status[XUSER_MAX_COUNT];

    for (int i = 0; i < XUSER_MAX_COUNT; ++i)
    {
      for (int j = 0; j < kButtonNum; ++j)
      {
        Status_[i].InputStatus_[j] = InputState::Released;
      }
    }
  }

  //  更新
  void IXInput::Update()
  {
    for (int i = 0; i < XUSER_MAX_COUNT; ++i)
    {
      XINPUT_STATE State;

      //  接続されていない時
      if (XInputGetState(i, &State) == ERROR_DEVICE_NOT_CONNECTED)
      {
        Status_[i].isConnect_ = false;
        continue;
      }

      auto& Gamepad = State.Gamepad;
      Status_[i].isConnect_ = true;

      for (int j = 0; j < kButtonNum; ++j)
      {
        auto& InputStatus_ = Status_[i].InputStatus_;

        //  状態の補間
        {
          //  押した瞬間
          if (InputStatus_[j] == InputState::Pressed)
          {
            InputStatus_[j] = InputState::Press;
          }
          //  離した瞬間
          else if (InputStatus_[j] == InputState::Released)
          {
            InputStatus_[j] = InputState::Release;
          }
        }

        //  状態を取得
        {
          //  押しているならtrue
          if (Gamepad.wButtons & kXInputButtonsCode[j])
          {
            //  押した瞬間
            if (InputStatus_[j] == InputState::Release)
            {
              InputStatus_[j] = InputState::Pressed;
            }
          }
          else
          {
            //  離した瞬間
            if (InputStatus_[j] == InputState::Press)
            {
              InputStatus_[j] = InputState::Released;
            }
          }

          static constexpr float kAnalogStickMinimumValue = -32768.0f;
          static constexpr float kAnalogStickHalfValue = 65535 * 0.5f;

          Status_[i].LeftStick_ = ((hdx::float2(static_cast<float>(Gamepad.sThumbLX), static_cast<float>(Gamepad.sThumbLY)) - kAnalogStickMinimumValue) / kAnalogStickHalfValue) - 1.0f;
          Status_[i].RightStick_ = ((hdx::float2(static_cast<float>(Gamepad.sThumbRX), static_cast<float>(Gamepad.sThumbRY)) - kAnalogStickMinimumValue) / kAnalogStickHalfValue) - 1.0f;

          static constexpr float kTriggerMaxValue = 255.0f;

          Status_[i].LeftTrigger_ = Gamepad.bLeftTrigger / kTriggerMaxValue;
          Status_[i].RightTrigger_ = Gamepad.bRightTrigger / kTriggerMaxValue;
        }
      }
    }

  }

  //  解放
  IXInput::~IXInput()
  {
    //  振動の停止
    {
      XINPUT_VIBRATION Vibration{ 0, 0 };

      for (int i = 0; i < XUSER_MAX_COUNT; ++i)
      {
        XInputSetState(i, &Vibration);
      }
    }

    delete[] Status_;
    Status_ = nullptr;
  }


  //--------------------------------------------------

  //  押されているならtrueを返す
  bool IXInput::Press(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Press || Status_[_Index].InputStatus_[_Number] == InputState::Pressed;
  }

  //  押された瞬間ならtrueを返す
  bool IXInput::Pressed(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Pressed;
  }

  //  離された瞬間ならtrueを返す
  bool IXInput::Released(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Released;
  }

  //  押されていないならtrueを返す
  bool IXInput::Release(int _Number, int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].InputStatus_[_Number] == InputState::Release || Status_[_Index].InputStatus_[_Number] == InputState::Released;
  }

  //  何かのボタンが押されていればtrueを返す
  bool IXInput::AnyButtonPress(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Press(i, _Index))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }

  //  何かのボタンが押されたならtrueを返す
  bool IXInput::AnyButtonPressed(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Pressed(i, _Index))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }

  //  何かのボタンが離されたならtrueを返す
  bool IXInput::AnyButtonReleased(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Released(i, _Index))
      {
        return true;
      }
    }

    //  何も離されていない
    return false;
  }

  //  左スティックの入力状態を取得
  hdx::float2 IXInput::GetLeftStick(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return hdx::float2(0.0f);

    hdx::float2 Value = Status_[_Index].LeftStick_;

    if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
    if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

    return Value;
  }

  //  右スティックの入力状態を取得
  hdx::float2 IXInput::GetRightStick(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return hdx::float2(0.0f);

    hdx::float2 Value = Status_[_Index].RightStick_;

    if (hdx::Math::GetAbsoluteValue(Value.X) < _DeadZone) Value.X = 0.0f;
    if (hdx::Math::GetAbsoluteValue(Value.Y) < _DeadZone) Value.Y = 0.0f;

    return Value;
  }

  //  左トリガーの入力状態を取得
  float IXInput::GetLeftTrigger(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return 0.0f;

    if (Status_[_Index].LeftTrigger_ < _DeadZone) return 0.0f;

    return Status_[_Index].LeftTrigger_;
  }

  //  右トリガーの入力状態を取得
  float IXInput::GetRightTrigger(int _Index, float _DeadZone)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return 0.0f;

    if (Status_[_Index].RightTrigger_ < _DeadZone) return 0.0f;

    return Status_[_Index].RightTrigger_;
  }

  //  接続されているか確認
  bool IXInput::isConnect(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return false;

    return Status_[_Index].isConnect_;
  }

  //  コントローラを振動させます
  void IXInput::SetVibration(int _Index, float _Speed)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return;

    static constexpr WORD kMaxSpeed = 65534;

    XINPUT_VIBRATION Vibration{ static_cast<WORD>(kMaxSpeed*_Speed),static_cast<WORD>(kMaxSpeed*_Speed) };

    XInputSetState(_Index, &Vibration);
  }

  //  コントローラの振動を止めます
  void IXInput::StopVibration(int _Index)const
  {
    //  対象外
    if (_Index < 0 || _Index > XUSER_MAX_COUNT) return;

    XINPUT_VIBRATION Vibration{ 0, 0 };

    XInputSetState(_Index, &Vibration);
  }
}
