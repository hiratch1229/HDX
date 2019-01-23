#pragma once
#include "IXInput.hpp"

#include "Src/Input/InputState.hpp"
#include "Include/Constants.hpp"

class CXInput : public IXInput
{
  struct Status
  {
    //  接続状態
    bool isConnect;
    //  入力状態
    InputState InputStatus[kButtonNum];
    //  左のアナログスティックの入力状態
    hdx::float2 LeftStick;
    //  右のアナログスティックの入力状態
    hdx::float2 RightStick;
    //  左のトリガーの入力状態
    float LeftTrigger;
    //  右のトリガーの入力状態
    float RightTrigger;
  };
private:
  Status Status_[kControllerNum];
private:
  bool isWithinRange(int _Index)const
  {
    return (Status_[_Index].isConnect && 0 <= _Index && _Index < kControllerNum);
  }
  bool isWithinRange(int _Number, int _Index)const
  {
    return (Status_[_Index].isConnect && 0 <= _Number && _Number < kButtonNum && 0 <= _Index && _Index < kControllerNum);
  }
public:
  ~CXInput();

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

    //  何も離されていない
    return false;
  }

  hdx::float2 GetLeftStick(int _Index, float _DeadZone)const override;

  hdx::float2 GetRightStick(int _Index, float _DeadZone)const override;

  float GetLeftTrigger(int _Index, float _DeadZone)const override;

  float GetRightTrigger(int _Index, float _DeadZone)const override;

  void SetVibration(int _Index, float _Speed)const override;

  void StopVibration(int _Index)const override;
};
