#pragma once

//  ライブラリ
namespace hdx
{
  class ButtonCombinationAND;
  class ButtonCombinationOR;

  //  入力デバイス
  enum class InputDevice
  {
    None,
    Keyboard,
    Mouse,
    XInput,
    Gamepad,
  };

  //  ボタン
  //  入力状態を表現します
  class Button
  {
    //  入力デバイス
    InputDevice InputDevice_;
    //  それぞれの入力デバイスでボタンの決められた番号
    int Number_;
    //  それぞれの入力デバイスの番号
    int Index_;
  public:
    //  ボタンを作成
    Button() = default;
    //  ボタンを作成
    //  _InputDevice:入力デバイス
    //  _ButtonNumber:それぞれの入力デバイスでボタンの決められた番号
    constexpr Button(InputDevice _InputDevice, int _Number, int _Index = 0)noexcept : InputDevice_(_InputDevice), Number_(_Number), Index_(_Index) {}
  public:
    //  入力状態を判別
    //  押されているならtrueを返す
    bool Press()const;
    //  入力状態を判別
    //  押された瞬間ならtrueを返す
    bool Pressed()const;
    //  入力状態を判別
    //  離された瞬間ならtrueを返す
    bool Released()const;
    //  入力状態を判別
    //  押されていないならtrueを返す
    bool Release()const;
  public:
    //  押されているならtrueを返す
    operator bool()const { return Press(); }
    //  押されていないならtrueを返す
    bool operator !()const { return !Press(); }
    //  2つのキーが同じかどうかを比較します
    //  (true:同じ,false:異なる)
    constexpr bool operator ==(const Button& _Button)const noexcept
    {
      return (InputDevice_ == _Button.InputDevice_ && Index_ == _Button.Index_ && Number_ == _Button.Number_);
    }
    //  2つのキーが異なるかどうかを比較します
    //  (true:異なる,false:同じ)
    constexpr bool operator !=(const Button& _Button)const noexcept
    {
      return !(*this == _Button);
    }
    //  論理積
    constexpr ButtonCombinationAND operator&&(const Button& _Button)const noexcept;
    //  論理和
    constexpr ButtonCombinationOR operator||(const Button& _Button)const noexcept;
  };

  //  ボタンの論理積の組み合わせ
  //  入力状態を表現します
  class ButtonCombinationAND
  {
    Button Button1_, Button2_;
  public:
    //  キーの論理積の組み合わせを作成
    ButtonCombinationAND() = default;
    //  キーの論理積の組み合わせを作成
    //  _Button1,_Button2:組み合わせたいボタン
    constexpr ButtonCombinationAND(const Button& _Button1, const Button& _Button2)noexcept : Button1_(_Button1), Button2_(_Button2) {}
  public:
    //  入力状態を判別
    //  押されているならtrueを返す
    bool Press()const { return Button1_.Press() && Button2_.Press(); }
    //  入力状態を判別
    //  押された瞬間ならtrueを返す
    bool Pressed()const { return Button1_.Pressed() && Button2_.Pressed(); }
    //  入力状態を判別
    //  離された瞬間ならtrueを返す
    bool Released()const { return Button1_.Released() && Button2_.Released(); }
    //  入力状態を判別
    //  押されていないならtrueを返す
    bool Release()const { return Button1_.Release() && Button2_.Release(); }
  public:
    //  押されているならtrueを返す
    operator bool()const { return Press(); }
    //  押されていないならtrueを返す
    bool operator !()const { return !Press(); }
    //  2つのキーが同じかどうかを比較します
    //  (true:同じ,false:異なる)
    constexpr bool operator ==(const ButtonCombinationAND& _ButtonCombinationAND)const noexcept
    {
      return (Button1_ == _ButtonCombinationAND.Button1_ && Button2_ == _ButtonCombinationAND.Button2_);
    }
    //  2つのキーが異なるかどうかを比較します
    //  (true:異なる,false:同じ)
    constexpr bool operator !=(const ButtonCombinationAND& _ButtonCombinationAND)const noexcept
    {
      return !(*this == _ButtonCombinationAND);
    }
  };

  //  論理積
  inline constexpr ButtonCombinationAND Button::operator&&(const Button& _Button)const noexcept
  {
    return{ (*this),_Button };
  }

  //  ボタンの論理和の組み合わせ
  //  入力状態を表現します
  class ButtonCombinationOR
  {
    Button Button1_, Button2_;
  public:
    //  キーの論理和の組み合わせを作成
    ButtonCombinationOR() = default;
    //  キーの論理和の組み合わせを作成
    //  _Button1,_Button2:組み合わせたいボタン
    constexpr ButtonCombinationOR(const Button& _Button1, const Button& _Button2)noexcept : Button1_(_Button1), Button2_(_Button2) {}
  public:
    //  入力状態を判別
    //  押されているならtrueを返す
    bool Press()const { return Button1_.Press() || Button2_.Press(); }
    //  入力状態を判別
    //  押された瞬間ならtrueを返す
    bool Pressed()const { return Button1_.Pressed() || Button2_.Pressed(); }
    //  入力状態を判別
    //  離された瞬間ならtrueを返す
    bool Released()const { return Button1_.Released() || Button2_.Released(); }
    //  入力状態を判別
    //  押されていないならtrueを返す
    bool Release()const { return Button1_.Release() || Button2_.Release(); }
  public:
    //  押されているならtrueを返す
    operator bool()const { return Press(); }
    //  押されていないならtrueを返す
    bool operator !()const { return !Press(); }
    //  2つのキーが同じかどうかを比較します
    //  (true:同じ,false:異なる)
    constexpr bool operator ==(const ButtonCombinationOR& _ButtonCombinationOR)const noexcept
    {
      return (Button1_ == _ButtonCombinationOR.Button1_ && Button2_ == _ButtonCombinationOR.Button2_);
    }
    //  2つのキーが異なるかどうかを比較します
    //  (true:異なる,false:同じ)
    constexpr bool operator !=(const ButtonCombinationOR& _ButtonCombinationOR)const noexcept
    {
      return !(*this == _ButtonCombinationOR);
    }
  };

  //  論理和
  inline constexpr ButtonCombinationOR Button::operator||(const Button& _Button)const noexcept
  {
    return{ (*this),_Button };
  }
}
