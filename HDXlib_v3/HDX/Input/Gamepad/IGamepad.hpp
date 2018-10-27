#pragma once
#include <HDX/Input/Button.hpp>
#include <HDX/Type2.hpp>

#include <Windows.h>

namespace detail
{
  class IGamepad 
  {
    struct Impl;
  private:
    Impl* pImpl_;
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
    //  接続されているか確認
    bool isConnect(int _Index)const;
    //  コントローラを振動させます
    void SetVibration(int _Index, float _Speed)const;
    //  コントローラの振動を止めます
    void StopVibration(int _Index)const;
  public:
    //  DirectInputの作成
    void CreateDirectInputDevice(const GUID& GuidProductFromDirectInput);
  public:
    //  初期化
    IGamepad();

    void Initialize();
    //  状態の更新
    void Update();
    //  解放
    ~IGamepad();
  };
}
