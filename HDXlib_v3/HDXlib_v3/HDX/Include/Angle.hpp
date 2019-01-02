#pragma once
#include "MathConstants.hpp"

//  ‘O•ûéŒ¾
namespace hdx
{
  class Degree;
}

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  //  ŒÊ“x–@
  //  Šp“x‚ğ-ƒÎ~ƒÎ‚Å•\Œ»‚µ‚Ü‚·
  //  (©“®‚Å³‹K‰»‚³‚ê‚Ü‚·)
  class Radian
  {
    float Value_; //  ’l
  public:
    //  ³‹K‰»(-ƒÎ~ƒÎ‚É‚·‚é)
    static constexpr float Normalize(float _Value)
    {
      return (-Math::PI <= _Value && _Value < Math::PI) ? _Value :
        (_Value - static_cast<int>((_Value + ((_Value < 0.0f) ? -Math::PI : Math::PI)) / Math::TwoPI)*Math::TwoPI);
    }
  public:
    //  0‚Å‰Šú‰»
    constexpr Radian() : Value_(0.0f) {}
    //  Šp“x‚ğì¬
    //  ©“®‚Å³‹K‰»‚³‚ê‚Ü‚·
    //  _Radian:ŒÊ“x–@
    constexpr Radian(float _Radian)noexcept : Value_(Normalize(_Radian)) {}
    //  Šp“x‚ğì¬
    //  ©“®‚Å³‹K‰»‚³‚ê‚Ü‚·
    //  _Radian:ŒÊ“x–@
    constexpr Radian(const Radian& _Radian)noexcept : Value_(Normalize(_Radian.Value_)) {}
    //  Šp“x‚ğì¬
    //  ©“®‚Å³‹K‰»‚³‚ê‚Ü‚·
    //  _Degree:“x”–@
    constexpr Radian(const Degree& _Degree)noexcept;
  public:
    //  floatŒ^‚Åæ“¾
    constexpr float GetValue()const { return Value_; }
  public:
    //  ‚»‚Ì‚Ü‚Ü‚Ì”’l‚ğæ“¾
    constexpr Radian operator +()const
    {
      return{ Value_ };
    }
    //  •„†”½“]‚µ‚½”’l‚ğæ“¾
    constexpr Radian operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  ‰ÁZ
    constexpr Radian operator +(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ + _Radian.Value_);
    }
    //  Œ¸Z
    constexpr Radian operator -(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ - _Radian.Value_);
    }
    //  ‘ã“ü
    Radian& operator =(const Radian& _Radian)noexcept
    {
      Value_ = _Radian.Value_;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    Radian& operator +=(const Radian& _Radian)noexcept
    {
      Value_ += _Radian.Value_;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    Radian& operator -=(const Radian& _Radian)noexcept
    {
      Value_ -= _Radian.Value_;
      return *this;
    }
    //  ”äŠr‰‰Zq
    constexpr bool operator ==(const Radian& _Radian)const noexcept
    {
      return (Value_ == _Radian.Value_);
    }
    //  ”äŠr
    constexpr bool operator !=(const Radian& _Radian)const noexcept
    {
      return !(*this == _Radian);
    }
    //  ”äŠr
    constexpr bool operator <(const Radian& _Radian)const noexcept
    {
      return (Value_ < _Radian.Value_);
    }
    //  ”äŠr
    constexpr bool operator >(const Radian& _Radian)const noexcept
    {
      return (Value_ > _Radian.Value_);
    }
    //  ”äŠr
    constexpr bool operator <=(const Radian& _Radian)const noexcept
    {
      return (Value_ <= _Radian.Value_);
    }
    //  ”äŠr
    constexpr bool operator >=(const Radian& _Radian)const noexcept
    {
      return (Value_ >= _Radian.Value_);
    }
  public:
    //  ‰ÁZ
    constexpr float operator +(float _Radian)const
    {
      return Normalize(Value_ + _Radian);
    }
    //  Œ¸Z
    constexpr float operator -(float _Radian)const
    {
      return Normalize(Value_ - _Radian);
    }
    //  Œ¸Z
    constexpr float operator *(float _Value)const
    {
      return Normalize(Value_ * _Value);
    }
    //  Œ¸Z
    constexpr float operator /(float _Value)const
    {
      return Normalize(Value_ / _Value);
    }
    //  ‘ã“ü
    float operator =(float _Radian)
    {
      return Value_ = _Radian;
    }
    //  ‰ÁZŒã‘ã“ü
    float operator +=(float _Radian)
    {
      return Value_ = Normalize(Value_ + _Radian);
    }
    //  Œ¸ZŒã‘ã“ü
    float operator -=(float _Radian)
    {
      return Value_ = Normalize(Value_ - _Radian);
    }
    //  ”äŠr
    constexpr bool operator ==(float _Radian)const
    {
      return (Value_ == _Radian);
    }
    //  ”äŠr
    constexpr bool operator !=(float _Radian)const
    {
      return !(*this == _Radian);
    }
    //  ”äŠr
    constexpr bool operator <(float _Radian)const
    {
      return (Value_ < _Radian);
    }
    //  ”äŠr
    constexpr bool operator >(float _Radian)const
    {
      return (Value_ > _Radian);
    }
    //  ”äŠr
    constexpr bool operator <=(float _Radian)const
    {
      return (Value_ <= _Radian);
    }
    //  ”äŠr
    constexpr bool operator >=(float _Radian)const
    {
      return (Value_ >= _Radian);
    }
  public:
    //  ‰ÁZ
    friend constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept;
    //  Œ¸Z
    friend constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept;
    //  ”äŠr
    friend constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept;
    //  ”äŠr
    friend constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept;
    //  ”äŠr
    friend constexpr bool operator <(float _Value, const Radian& _Radian)noexcept;
    //  ”äŠr
    friend constexpr bool operator >(float _Value, const Radian& _Radian)noexcept;
    //  ”äŠr
    friend constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept;
    //  ”äŠr
    friend constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept;
  };

  //  “x”–@
  //  Šp“x‚ğ-180~180‚Å•\Œ»‚µ‚Ü‚·
  //  (©“®‚Å³‹K‰»‚³‚ê‚Ü‚·)
  class Degree
  {
    float Value_; //  ’l
  public:
    //  ³‹K‰»(-180~180“x‚É‚·‚é)
    static constexpr float Normalize(float _Value)
    {
      return (-180.0f <= _Value && _Value < 180.0f) ? _Value :
        (_Value - static_cast<int>((_Value + ((_Value < 0.0f) ? -180.0f : 180.0f)) / 360.0f)*360.0f);
    }
  public:
    //  0‚Å‰Šú‰»
    constexpr Degree() : Value_(0.0f) {}
    //  Šp“x‚ğì¬
    //  ©“®‚Å³‹K‰»‚³‚ê‚Ü‚·
    //  _Degree:“x”–@
    constexpr Degree(float _Degree)noexcept : Value_(Normalize(_Degree)) {}
    //  Šp“x‚ğì¬
    //  ©“®‚Å³‹K‰»‚³‚ê‚Ü‚·
    //  _Degree:“x”–@
    constexpr Degree(const Degree& _Degree)noexcept : Value_(Normalize(_Degree.Value_)) {}
    //  Šp“x‚ğì¬
    //  ©“®‚Å³‹K‰»‚³‚ê‚Ü‚·
    //  _Radian:ŒÊ“x–@
    constexpr Degree(const Radian& _Radian)noexcept : Value_(Normalize(Math::ToDegree(_Radian.GetValue()))) {}
  public:
    //  floatŒ^‚Åæ“¾
    constexpr float GetValue()const { return Value_; }
  public:
    //  ‚»‚Ì‚Ü‚Ü‚Ì”’l‚ğæ“¾
    constexpr Degree operator +()const
    {
      return{ Value_ };
    }
    //  •„†”½“]‚µ‚½”’l‚ğæ“¾
    constexpr Degree operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  ‰ÁZ
    constexpr Degree operator +(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ + _Degree.Value_);
    }
    //  ‘ã“ü
    constexpr Degree operator -(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ - _Degree.Value_);
    }
    //  ‘ã“ü
    Degree& operator =(const Degree& _Degree)noexcept
    {
      Value_ = _Degree.Value_;
      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    Degree& operator +=(const Degree& _Degree)noexcept
    {
      Value_ += _Degree.Value_;
      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    Degree& operator -=(const Degree& _Degree)noexcept
    {
      Value_ -= _Degree.Value_;
      return *this;
    }
    //  ‘O’uƒCƒ“ƒNƒŠƒƒ“ƒg
    Degree& operator ++()
    {
      Value_ = Normalize(++Value_);

      return *this;
    }
    //  Œã’uƒCƒ“ƒNƒŠƒƒ“ƒg
    Degree operator ++(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(++Value_);

      return Degree;
    }
    //  ‘O’uƒfƒNƒŠƒƒ“ƒg
    Degree& operator --()
    {
      Value_ = Normalize(--Value_);

      return *this;
    }
    //  Œã’uƒfƒNƒŠƒƒ“ƒg
    Degree operator --(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(--Value_);

      return Degree;
    }
    //  ”äŠr
    constexpr bool operator ==(const Degree& _Degree)const noexcept
    {
      return (Value_ == _Degree.Value_);
    }
    //  ”äŠr
    constexpr bool operator !=(const Degree& _Degree)const noexcept
    {
      return !(*this == _Degree);
    }
    //  ”äŠr
    constexpr bool operator <(const Degree& _Degree)const noexcept
    {
      return (Value_ < _Degree.Value_);
    }
    //  ”äŠr
    constexpr bool operator >(const Degree& _Degree)const noexcept
    {
      return (Value_ > _Degree.Value_);
    }
    //  ”äŠr
    constexpr bool operator <=(const Degree& _Degree)const noexcept
    {
      return (Value_ <= _Degree.Value_);
    }
    //  ”äŠr
    constexpr bool operator >=(const Degree& _Degree)const noexcept
    {
      return (Value_ >= _Degree.Value_);
    }
  public:
    //  ‰ÁZ
    constexpr Degree operator +(float _Degree)const
    {
      return{ Normalize(Value_ + _Degree) };
    }
    //  Œ¸Z
    constexpr Degree operator -(float _Degree)const
    {
      return{ Normalize(Value_ - _Degree) };
    }
    //  ‘ã“ü
    Degree operator =(float _Degree)
    {
      return {Value_ = _Degree};
    }
    //  ‰ÁZŒã‘ã“ü
    Degree operator +=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ + _Degree) };
    }
    //  Œ¸ZŒã‘ã“ü
    Degree operator -=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ - _Degree) };
    }
    //  ”äŠr
    constexpr bool operator ==(float _Degree)const
    {
      return (Value_ == _Degree);
    }
    //  ”äŠr
    constexpr bool operator !=(float _Degree)const
    {
      return !(*this == _Degree);
    }
    //  ”äŠr
    constexpr bool operator <(float _Degree)const
    {
      return (Value_ < _Degree);
    }
    //  ”äŠr
    constexpr bool operator >(float _Degree)const
    {
      return (Value_ > _Degree);
    }
    //  ”äŠr
    constexpr bool operator <=(float _Degree)const
    {
      return (Value_ <= _Degree);
    }
    //  ”äŠr
    constexpr bool operator >=(float _Degree)const
    {
      return (Value_ >= _Degree);
    }
  public:
    //  ‰ÁZ
    friend constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept;
    //  Œ¸Z
    friend constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept;
    //  ”äŠr
    friend constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept;
    //  ”äŠr
    friend constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept;
    //  ”äŠr
    friend constexpr bool operator <(float _Value, const Degree& _Degree)noexcept;
    //  ”äŠr
    friend constexpr bool operator >(float _Value, const Degree& _Degree)noexcept;
    //  ”äŠr
    friend constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept;
    //  ”äŠr
    friend constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept;
  };

  //  Šp“x‚ğì¬
  //  ©“®‚Å³‹K‰»‚³‚ê‚Ü‚·
  //  _Degree:“x”–@
  inline constexpr Radian::Radian(const Degree& _Degree)noexcept
    : Value_(Normalize(Math::ToRadian(_Degree.GetValue())))
  {

  }
  //  ‰ÁZ
  inline constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept
  {
    return _Value + _Radian.Value_;
  }
  //  Œ¸Z
  inline constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept
  {
    return _Value - _Radian.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept
  {
    return _Value == _Radian.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept
  {
    return !(_Value == _Radian);
  }
  //  ”äŠr
  inline constexpr bool operator <(float _Value, const Radian& _Radian)noexcept
  {
    return _Value < _Radian.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator >(float _Value, const Radian& _Radian)noexcept
  {
    return _Value > _Radian.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value <= _Radian.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value >= _Radian.Value_;
  }

  //  ‰ÁZ
  inline constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept
  {
    return _Value + _Degree.Value_;
  }
  //  Œ¸Z
  inline constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept
  {
    return _Value - _Degree.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept
  {
    return _Value == _Degree.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept
  {
    return !(_Value == _Degree);
  }
  //  ”äŠr
  inline constexpr bool operator <(float _Value, const Degree& _Degree)noexcept
  {
    return _Value < _Degree.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator >(float _Value, const Degree& _Degree)noexcept
  {
    return _Value > _Degree.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value <= _Degree.Value_;
  }
  //  ”äŠr
  inline constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value >= _Degree.Value_;
  }
}
