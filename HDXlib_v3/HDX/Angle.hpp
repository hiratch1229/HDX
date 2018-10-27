#pragma once
#include <HDX/MathConstants.hpp>

//  前方宣言
namespace hdx
{
  class Degree;
}

//  ライブラリ
namespace hdx
{
  //  弧度法
  //  角度を-π~πで表現します
  //  (自動で正規化されます)
  class Radian
  {
    float Value_; //  値
  public:
    //  正規化(-π~πにする)
    static constexpr float Normalize(float _Value)
    {
      return (-Math::PI <= _Value && _Value < Math::PI) ? _Value :
        (_Value - static_cast<int>((_Value + ((_Value < 0.0f) ? -Math::PI : Math::PI)) / Math::TwoPI)*Math::TwoPI);
    }
  public:
    //  0で初期化
    constexpr Radian() : Value_(0.0f) {}
    //  角度を作成
    //  自動で正規化されます
    //  _Radian:弧度法
    constexpr Radian(float _Radian)noexcept : Value_(Normalize(_Radian)) {}
    //  角度を作成
    //  自動で正規化されます
    //  _Radian:弧度法
    constexpr Radian(const Radian& _Radian)noexcept : Value_(Normalize(_Radian.Value_)) {}
    //  角度を作成
    //  自動で正規化されます
    //  _Degree:度数法
    constexpr Radian(const Degree& _Degree)noexcept;
  public:
    //  float型で取得
    constexpr float GetValue()const { return Value_; }
  public:
    //  そのままの数値を取得
    constexpr Radian operator +()const
    {
      return{ Value_ };
    }
    //  符号反転した数値を取得
    constexpr Radian operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  加算
    constexpr Radian operator +(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ + _Radian.Value_);
    }
    //  減算
    constexpr Radian operator -(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ - _Radian.Value_);
    }
    //  代入
    Radian& operator =(const Radian& _Radian)noexcept
    {
      Value_ = _Radian.Value_;

      return *this;
    }
    //  加算後代入
    Radian& operator +=(const Radian& _Radian)noexcept
    {
      Value_ += _Radian.Value_;

      return *this;
    }
    //  減算後代入
    Radian& operator -=(const Radian& _Radian)noexcept
    {
      Value_ -= _Radian.Value_;
      return *this;
    }
    //  比較演算子
    constexpr bool operator ==(const Radian& _Radian)const noexcept
    {
      return (Value_ == _Radian.Value_);
    }
    //  比較
    constexpr bool operator !=(const Radian& _Radian)const noexcept
    {
      return !(*this == _Radian);
    }
    //  比較
    constexpr bool operator <(const Radian& _Radian)const noexcept
    {
      return (Value_ < _Radian.Value_);
    }
    //  比較
    constexpr bool operator >(const Radian& _Radian)const noexcept
    {
      return (Value_ > _Radian.Value_);
    }
    //  比較
    constexpr bool operator <=(const Radian& _Radian)const noexcept
    {
      return (Value_ <= _Radian.Value_);
    }
    //  比較
    constexpr bool operator >=(const Radian& _Radian)const noexcept
    {
      return (Value_ >= _Radian.Value_);
    }
  public:
    //  加算
    constexpr float operator +(float _Radian)const
    {
      return Normalize(Value_ + _Radian);
    }
    //  減算
    constexpr float operator -(float _Radian)const
    {
      return Normalize(Value_ - _Radian);
    }
    //  代入
    float operator =(float _Radian)
    {
      return Value_ = _Radian;
    }
    //  加算後代入
    float operator +=(float _Radian)
    {
      return Value_ = Normalize(Value_ + _Radian);
    }
    //  減算後代入
    float operator -=(float _Radian)
    {
      return Value_ = Normalize(Value_ - _Radian);
    }
    //  比較
    constexpr bool operator ==(float _Radian)const
    {
      return (Value_ == _Radian);
    }
    //  比較
    constexpr bool operator !=(float _Radian)const
    {
      return !(*this == _Radian);
    }
    //  比較
    constexpr bool operator <(float _Radian)const
    {
      return (Value_ < _Radian);
    }
    //  比較
    constexpr bool operator >(float _Radian)const
    {
      return (Value_ > _Radian);
    }
    //  比較
    constexpr bool operator <=(float _Radian)const
    {
      return (Value_ <= _Radian);
    }
    //  比較
    constexpr bool operator >=(float _Radian)const
    {
      return (Value_ >= _Radian);
    }
  public:
    //  加算
    friend constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept;
    //  減算
    friend constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept;
    //  比較
    friend constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept;
    //  比較
    friend constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept;
    //  比較
    friend constexpr bool operator <(float _Value, const Radian& _Radian)noexcept;
    //  比較
    friend constexpr bool operator >(float _Value, const Radian& _Radian)noexcept;
    //  比較
    friend constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept;
    //  比較
    friend constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept;
  };

  //  度数法
  //  角度を-180~180で表現します
  //  (自動で正規化されます)
  class Degree
  {
    float Value_; //  値
  public:
    //  正規化(-180~180度にする)
    static constexpr float Normalize(float _Value)
    {
      return (-180.0f <= _Value && _Value < 180.0f) ? _Value :
        (_Value - static_cast<int>((_Value + ((_Value < 0.0f) ? -180.0f : 180.0f)) / 360.0f)*360.0f);
    }
  public:
    //  0で初期化
    constexpr Degree() : Value_(0.0f) {}
    //  角度を作成
    //  自動で正規化されます
    //  _Degree:度数法
    constexpr Degree(float _Degree)noexcept : Value_(Normalize(_Degree)) {}
    //  角度を作成
    //  自動で正規化されます
    //  _Degree:度数法
    constexpr Degree(const Degree& _Degree)noexcept : Value_(Normalize(_Degree.Value_)) {}
    //  角度を作成
    //  自動で正規化されます
    //  _Radian:弧度法
    constexpr Degree(const Radian& _Radian)noexcept : Value_(Normalize(Math::ToDegree(_Radian.GetValue()))) {}
  public:
    //  float型で取得
    constexpr float GetValue()const { return Value_; }
  public:
    //  そのままの数値を取得
    constexpr Degree operator +()const
    {
      return{ Value_ };
    }
    //  符号反転した数値を取得
    constexpr Degree operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  加算
    constexpr Degree operator +(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ + _Degree.Value_);
    }
    //  代入
    constexpr Degree operator -(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ - _Degree.Value_);
    }
    //  代入
    Degree& operator =(const Degree& _Degree)noexcept
    {
      Value_ = _Degree.Value_;
      return *this;
    }
    //  加算後代入
    Degree& operator +=(const Degree& _Degree)noexcept
    {
      Value_ += _Degree.Value_;
      return *this;
    }
    //  減算後代入
    Degree& operator -=(const Degree& _Degree)noexcept
    {
      Value_ -= _Degree.Value_;
      return *this;
    }
    //  前置インクリメント
    Degree& operator ++()
    {
      Value_ = Normalize(++Value_);

      return *this;
    }
    //  後置インクリメント
    Degree operator ++(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(++Value_);

      return Degree;
    }
    //  前置デクリメント
    Degree& operator --()
    {
      Value_ = Normalize(--Value_);

      return *this;
    }
    //  後置デクリメント
    Degree operator --(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(--Value_);

      return Degree;
    }
    //  比較
    constexpr bool operator ==(const Degree& _Degree)const noexcept
    {
      return (Value_ == _Degree.Value_);
    }
    //  比較
    constexpr bool operator !=(const Degree& _Degree)const noexcept
    {
      return !(*this == _Degree);
    }
    //  比較
    constexpr bool operator <(const Degree& _Degree)const noexcept
    {
      return (Value_ < _Degree.Value_);
    }
    //  比較
    constexpr bool operator >(const Degree& _Degree)const noexcept
    {
      return (Value_ > _Degree.Value_);
    }
    //  比較
    constexpr bool operator <=(const Degree& _Degree)const noexcept
    {
      return (Value_ <= _Degree.Value_);
    }
    //  比較
    constexpr bool operator >=(const Degree& _Degree)const noexcept
    {
      return (Value_ >= _Degree.Value_);
    }
  public:
    //  加算
    constexpr Degree operator +(float _Degree)const
    {
      return{ Normalize(Value_ + _Degree) };
    }
    //  減算
    constexpr Degree operator -(float _Degree)const
    {
      return{ Normalize(Value_ - _Degree) };
    }
    //  代入
    Degree operator =(float _Degree)
    {
      return {Value_ = _Degree};
    }
    //  加算後代入
    Degree operator +=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ + _Degree) };
    }
    //  減算後代入
    Degree operator -=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ - _Degree) };
    }
    //  比較
    constexpr bool operator ==(float _Degree)const
    {
      return (Value_ == _Degree);
    }
    //  比較
    constexpr bool operator !=(float _Degree)const
    {
      return !(*this == _Degree);
    }
    //  比較
    constexpr bool operator <(float _Degree)const
    {
      return (Value_ < _Degree);
    }
    //  比較
    constexpr bool operator >(float _Degree)const
    {
      return (Value_ > _Degree);
    }
    //  比較
    constexpr bool operator <=(float _Degree)const
    {
      return (Value_ <= _Degree);
    }
    //  比較
    constexpr bool operator >=(float _Degree)const
    {
      return (Value_ >= _Degree);
    }
  public:
    //  加算
    friend constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept;
    //  減算
    friend constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept;
    //  比較
    friend constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept;
    //  比較
    friend constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept;
    //  比較
    friend constexpr bool operator <(float _Value, const Degree& _Degree)noexcept;
    //  比較
    friend constexpr bool operator >(float _Value, const Degree& _Degree)noexcept;
    //  比較
    friend constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept;
    //  比較
    friend constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept;
  };

  //  角度を作成
  //  自動で正規化されます
  //  _Degree:度数法
  inline constexpr Radian::Radian(const Degree& _Degree)noexcept
    : Value_(Normalize(Math::ToRadian(_Degree.GetValue())))
  {

  }
  //  加算
  inline constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept
  {
    return _Value + _Radian.Value_;
  }
  //  減算
  inline constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept
  {
    return _Value - _Radian.Value_;
  }
  //  比較
  inline constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept
  {
    return _Value == _Radian.Value_;
  }
  //  比較
  inline constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept
  {
    return !(_Value == _Radian);
  }
  //  比較
  inline constexpr bool operator <(float _Value, const Radian& _Radian)noexcept
  {
    return _Value < _Radian.Value_;
  }
  //  比較
  inline constexpr bool operator >(float _Value, const Radian& _Radian)noexcept
  {
    return _Value > _Radian.Value_;
  }
  //  比較
  inline constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value <= _Radian.Value_;
  }
  //  比較
  inline constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value >= _Radian.Value_;
  }

  //  加算
  inline constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept
  {
    return _Value + _Degree.Value_;
  }
  //  減算
  inline constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept
  {
    return _Value - _Degree.Value_;
  }
  //  比較
  inline constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept
  {
    return _Value == _Degree.Value_;
  }
  //  比較
  inline constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept
  {
    return !(_Value == _Degree);
  }
  //  比較
  inline constexpr bool operator <(float _Value, const Degree& _Degree)noexcept
  {
    return _Value < _Degree.Value_;
  }
  //  比較
  inline constexpr bool operator >(float _Value, const Degree& _Degree)noexcept
  {
    return _Value > _Degree.Value_;
  }
  //  比較
  inline constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value <= _Degree.Value_;
  }
  //  比較
  inline constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value >= _Degree.Value_;
  }
}
