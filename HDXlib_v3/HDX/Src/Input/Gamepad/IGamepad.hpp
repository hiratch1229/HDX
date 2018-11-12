#pragma once
#include "../../../Include/Button.hpp"
#include "../../../Include/Type2.hpp"
#include "../../../Include/Constants.hpp"

#include "../InputState.hpp"

class IGamepad
{
  static constexpr int kButtonNum = 32;
  static constexpr int kControllerNum = hdx::ControllerMaxNum;
private:
  struct Status
  {
    //  接続状態
    bool isConnect = true;
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
  //  接続されているか確認
  bool isConnect(int _Index)const;
public:
  //  何かのボタンが押されていればtrueを返す
  bool AnyButtonPress(int _Index)const;
  //  何かのボタンが押されたならtrueを返す
  bool AnyButtonPressed(int _Index)const;
  //  何かのボタンが離されたならtrueを返す
  bool AnyButtonReleased(int _Index)const;
public:
  //  ボタンを取得
  hdx::Button GetButton(int _Index, int _Number)const;
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
  //  コントローラを振動させます
  void SetVibration(int _Index, float _Speed)const;
  //  コントローラの振動を止めます
  void StopVibration(int _Index)const;
public:
  //  初期化
  IGamepad();
  //  状態の更新
  void Update();
  //  解放
  ~IGamepad();
};
