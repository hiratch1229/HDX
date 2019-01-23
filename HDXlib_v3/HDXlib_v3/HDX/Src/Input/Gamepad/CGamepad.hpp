#pragma once
#include "IGamepad.hpp"

#include "Include/Type2.hpp"
#include "Include/Types.hpp"
#include "Include/Constants.hpp"
#include "Src/Input/InputState.hpp"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>
#include <vector>
#include <memory>

class CGamepad : public IGamepad
{
  enum class PovDirection
  {
    Up,
    Down,
    Left,
    Right,

    Num
  };
private:
  static constexpr UINT kPovDirectionNum = static_cast<UINT>(PovDirection::Num);
  static constexpr UINT kButtonNum = 32 + kPovDirectionNum;
  static constexpr UINT kControllerNum = (hdx::Constants::ControllerMaxNum < 4) ? hdx::Constants::ControllerMaxNum : 4;
  static constexpr int kStickMaxValue = 10000;
  static constexpr int kTriggerMaxValue = 65535;
private:
  struct Status
  {
    //  接続状態
    bool isConnect = false;
    //  入力状態
    InputState* InputStatus;
    //  左のアナログスティックの入力状態
    hdx::float2 LeftStick;
    //  右のアナログスティックの入力状態
    hdx::float2 RightStick;
    //  左のトリガーの入力状態
    float LeftTrigger;
    //  右のトリガーの入力状態
    float RightTrigger;
    //  ボタン数
    int ButtonNum = 0;
  };
  struct DirectInputData
  {
    //  ジョイスティック
    LPDIRECTINPUTDEVICE8 pJoyStick;
    //  振動エフェクト
    LPDIRECTINPUTEFFECT pEffect;
  };
private:
  Status Status_[kControllerNum];
  //  DirectInputの数
  int DirectInputNum_ = 0;
  //  XInputの数
  int XInputNum_ = 0;
  //  コントローラの数
  int ControllerNum_ = 0;
  //  現在のジョイスティック数
  int DeviceNum_ = 0;
  //  
  Microsoft::WRL::ComPtr<IDirectInput8W> pDirectInput_;

  std::unique_ptr<DirectInputData[]> pDirectInputDatas_;

  HWND hWnd_;
  //  XInput判別用リスト
  std::vector<LONG> XInputList_;
  //  DirectInputコントローラのID
  std::vector<UINT> JoyIDList_;
private:
  bool isWithinRange(int _Index)const
  {
    return (0 <= _Index && _Index < kControllerNum && Status_[_Index].isConnect);
  }
  bool isWithinRange(int _Number, int _Index)const
  {
    return (0 <= _Index && _Index < kControllerNum && Status_[_Index].isConnect && 0 <= _Number && _Number < Status_[_Index].ButtonNum);
  }
public:
public:
  CGamepad();

  ~CGamepad();

  void Initialize(const HWND& _hWnd)override;

  void CreateDirectInputDevice(const GUID& GuidProductFromDirectInput)override;

  void Update()override;

  bool Press(int _Number, int _Index)const override
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Press() : false;
  }

  bool Pressed(int _Number, int _Index)const override
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Pressed() : false;
  }

  bool Released(int _Number, int _Index)const override
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Released() : false;
  }

  bool Release(int _Number, int _Index)const override
  {
    return isWithinRange(_Number, _Index) ? Status_[_Index].InputStatus[_Number].Release() : false;
  }

  bool isConnect(int _Index)const override
  {
    return isWithinRange(_Index) ? Status_[_Index].isConnect : false;
  }

  int GetButtonNum(int _Index)const override
  {
    return isWithinRange(_Index) ? Status_[_Index].ButtonNum : 0;
  }

  bool AnyButtonPress(int _Index)const override
  {
    if (!(isWithinRange(_Index))) return false;

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

  bool AnyButtonPressed(int _Index)const override
  {
    if (!(isWithinRange(_Index))) return false;

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

  bool AnyButtonReleased(int _Index)const override
  {
    if (!(isWithinRange(_Index))) return false;

    for (int i = 0; i < kButtonNum; ++i)
    {
      if (Released(i, _Index))
      {
        return true;
      }
    }

    //  何も押されていない
    return false;
  }

  hdx::Button GetButton(int _Index, int _Number)const override
  {
    return isWithinRange(_Index) ? hdx::Button(hdx::InputDevice::Gamepad, _Number, _Index) : hdx::Button();
  }

  hdx::float2 GetLeftStick(int _Index, float _DeadZone)const override;

  hdx::float2 GetRightStick(int _Index, float _DeadZone)const override;

  float GetLeftTrigger(int _Index, float _DeadZone)const override;

  float GetRightTrigger(int _Index, float _DeadZone)const;

  void SetVibration(int _Index, float _Speed)const;

  void StopVibration(int _Index)const override;
};
