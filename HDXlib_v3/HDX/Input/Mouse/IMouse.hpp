#pragma once
#include <HDX/Singleton.hpp>
#include <HDX/Type2.hpp>

namespace detail
{
  enum class InputState;

  //  マウスで使うボタン
  enum class MouseButtons
  {
    Left,
    Middle,
    Right,
    X1,
    X2,

    Num //  個数
  };

  //  マウス
  class IMouse : public hdx::Singleton<IMouse>
  {
    //  使用されるボタンの個数
    static constexpr int kButtonNum = static_cast<int>(MouseButtons::Num);
  private:
    //  入力状態
    InputState* InputStatus_;
    //  座標
    hdx::int2 Pos_;
    //  移動量
    hdx::int2 Delta_;
    //  ホイール移動量
    int Wheel_;
  public:
    //  ボタンが押された時の処理
    void ButtonPressed(MouseButtons Button);
    //  ボタンが離された時の処理
    void ButtonReleased(MouseButtons Button);
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
    //  座標を取得
    hdx::int2 GetPos()const;
    //  座標を変更
    void SetPos(const hdx::int2& _Pos);
    //  移動量を取得
    hdx::int2 GetDelta()const;
    //  ホイール移動量を取得
    int GetWheel()const;
    //  ホイール移動量を変更
    void SetWheel(int _Wheel);
  public:
    //  何かのボタンが押されていればtrueを返す
    bool AnyButtonPress()const;
    //  何かのボタンが押されたならtrueを返す
    bool AnyButtonPressed()const;
    //  何かのボタンが離されたならtrueを返す
    bool AnyButtonReleased()const;
  public:
    //  初期化
    IMouse();
    //  状態の更新
    void Update();
    //  解放
    ~IMouse();
  };
}
