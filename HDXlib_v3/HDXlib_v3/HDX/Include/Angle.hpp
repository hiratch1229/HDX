#pragma once
#include "MathConstants.hpp"

//  ëOï˚êÈåæ
namespace hdx
{
  class Degree;
}

//  ÉâÉCÉuÉâÉä
namespace hdx
{
  //  å ìxñ@
  //  äpìxÇ-ÉŒ~ÉŒÇ≈ï\åªÇµÇ‹Ç∑
  //  (é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑)
  class Radian
  {
    float Value_; //  íl
  public:
    //  ê≥ãKâª(-ÉŒ~ÉŒÇ…Ç∑ÇÈ)
    static constexpr float Normalize(float _Value)
    {
      while (_Value > Math::PI) _Value -= Math::PI;
      while (_Value < Math::PI) _Value += Math::PI;

      return _Value;
    }
  public:
    //  0Ç≈èâä˙âª
    constexpr Radian() : Value_(0.0f) {}
    //  äpìxÇçÏê¨
    //  é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑
    //  _Radian:å ìxñ@
    constexpr Radian(float _Radian)noexcept : Value_(Normalize(_Radian)) {}
    //  äpìxÇçÏê¨
    //  é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑
    //  _Radian:å ìxñ@
    constexpr Radian(const Radian& _Radian)noexcept : Value_(Normalize(_Radian.Value_)) {}
    //  äpìxÇçÏê¨
    //  é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑
    //  _Degree:ìxêîñ@
    constexpr Radian(const Degree& _Degree)noexcept;
  public:
    //  floatå^Ç≈éÊìæ
    constexpr float GetValue()const { return Value_; }
  public:
    //  ÇªÇÃÇ‹Ç‹ÇÃêîílÇéÊìæ
    constexpr Radian operator +()const
    {
      return{ Value_ };
    }
    //  ïÑçÜîΩì]ÇµÇΩêîílÇéÊìæ
    constexpr Radian operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  â¡éZ
    constexpr Radian operator +(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ + _Radian.Value_);
    }
    //  å∏éZ
    constexpr Radian operator -(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ - _Radian.Value_);
    }
    //  ë„ì¸
    Radian& operator =(const Radian& _Radian)noexcept
    {
      Value_ = _Radian.Value_;

      return *this;
    }
    //  â¡éZå„ë„ì¸
    Radian& operator +=(const Radian& _Radian)noexcept
    {
      Value_ += _Radian.Value_;

      return *this;
    }
    //  å∏éZå„ë„ì¸
    Radian& operator -=(const Radian& _Radian)noexcept
    {
      Value_ -= _Radian.Value_;
      return *this;
    }
    //  î‰ärââéZéq
    constexpr bool operator ==(const Radian& _Radian)const noexcept
    {
      return (Value_ == _Radian.Value_);
    }
    //  î‰är
    constexpr bool operator !=(const Radian& _Radian)const noexcept
    {
      return !(*this == _Radian);
    }
    //  î‰är
    constexpr bool operator <(const Radian& _Radian)const noexcept
    {
      return (Value_ < _Radian.Value_);
    }
    //  î‰är
    constexpr bool operator >(const Radian& _Radian)const noexcept
    {
      return (Value_ > _Radian.Value_);
    }
    //  î‰är
    constexpr bool operator <=(const Radian& _Radian)const noexcept
    {
      return (Value_ <= _Radian.Value_);
    }
    //  î‰är
    constexpr bool operator >=(const Radian& _Radian)const noexcept
    {
      return (Value_ >= _Radian.Value_);
    }
  public:
    //  â¡éZ
    constexpr float operator +(float _Radian)const
    {
      return Normalize(Value_ + _Radian);
    }
    //  å∏éZ
    constexpr float operator -(float _Radian)const
    {
      return Normalize(Value_ - _Radian);
    }
    //  å∏éZ
    constexpr float operator *(float _Value)const
    {
      return Normalize(Value_ * _Value);
    }
    //  å∏éZ
    constexpr float operator /(float _Value)const
    {
      return Normalize(Value_ / _Value);
    }
    //  ë„ì¸
    float operator =(float _Radian)
    {
      return Value_ = _Radian;
    }
    //  â¡éZå„ë„ì¸
    float operator +=(float _Radian)
    {
      return Value_ = Normalize(Value_ + _Radian);
    }
    //  å∏éZå„ë„ì¸
    float operator -=(float _Radian)
    {
      return Value_ = Normalize(Value_ - _Radian);
    }
    //  î‰är
    constexpr bool operator ==(float _Radian)const
    {
      return (Value_ == _Radian);
    }
    //  î‰är
    constexpr bool operator !=(float _Radian)const
    {
      return !(*this == _Radian);
    }
    //  î‰är
    constexpr bool operator <(float _Radian)const
    {
      return (Value_ < _Radian);
    }
    //  î‰är
    constexpr bool operator >(float _Radian)const
    {
      return (Value_ > _Radian);
    }
    //  î‰är
    constexpr bool operator <=(float _Radian)const
    {
      return (Value_ <= _Radian);
    }
    //  î‰är
    constexpr bool operator >=(float _Radian)const
    {
      return (Value_ >= _Radian);
    }
  public:
    //  â¡éZ
    friend constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept;
    //  å∏éZ
    friend constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept;
    //  î‰är
    friend constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept;
    //  î‰är
    friend constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept;
    //  î‰är
    friend constexpr bool operator <(float _Value, const Radian& _Radian)noexcept;
    //  î‰är
    friend constexpr bool operator >(float _Value, const Radian& _Radian)noexcept;
    //  î‰är
    friend constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept;
    //  î‰är
    friend constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept;
  };

  //  ìxêîñ@
  //  äpìxÇ-180~180Ç≈ï\åªÇµÇ‹Ç∑
  //  (é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑)
  class Degree
  {
    float Value_; //  íl
  public:
    //  ê≥ãKâª(-180~180ìxÇ…Ç∑ÇÈ)
    static constexpr float Normalize(float _Value)
    {
      while (_Value > 180.0f) _Value -= 180.0f;
      while (_Value < 180.0f) _Value += 180.0f;

      return _Value;
    }
  public:
    //  0Ç≈èâä˙âª
    constexpr Degree() : Value_(0.0f) {}
    //  äpìxÇçÏê¨
    //  é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑
    //  _Degree:ìxêîñ@
    constexpr Degree(float _Degree)noexcept : Value_(Normalize(_Degree)) {}
    //  äpìxÇçÏê¨
    //  é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑
    //  _Degree:ìxêîñ@
    constexpr Degree(const Degree& _Degree)noexcept : Value_(Normalize(_Degree.Value_)) {}
    //  äpìxÇçÏê¨
    //  é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑
    //  _Radian:å ìxñ@
    constexpr Degree(const Radian& _Radian)noexcept : Value_(Normalize(Math::ToDegree(_Radian.GetValue()))) {}
  public:
    //  floatå^Ç≈éÊìæ
    constexpr float GetValue()const { return Value_; }
  public:
    //  ÇªÇÃÇ‹Ç‹ÇÃêîílÇéÊìæ
    constexpr Degree operator +()const
    {
      return{ Value_ };
    }
    //  ïÑçÜîΩì]ÇµÇΩêîílÇéÊìæ
    constexpr Degree operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  â¡éZ
    constexpr Degree operator +(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ + _Degree.Value_);
    }
    //  ë„ì¸
    constexpr Degree operator -(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ - _Degree.Value_);
    }
    //  ë„ì¸
    Degree& operator =(const Degree& _Degree)noexcept
    {
      Value_ = _Degree.Value_;
      return *this;
    }
    //  â¡éZå„ë„ì¸
    Degree& operator +=(const Degree& _Degree)noexcept
    {
      Value_ += _Degree.Value_;
      return *this;
    }
    //  å∏éZå„ë„ì¸
    Degree& operator -=(const Degree& _Degree)noexcept
    {
      Value_ -= _Degree.Value_;
      return *this;
    }
    //  ëOíuÉCÉìÉNÉäÉÅÉìÉg
    Degree& operator ++()
    {
      Value_ = Normalize(++Value_);

      return *this;
    }
    //  å„íuÉCÉìÉNÉäÉÅÉìÉg
    Degree operator ++(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(++Value_);

      return Degree;
    }
    //  ëOíuÉfÉNÉäÉÅÉìÉg
    Degree& operator --()
    {
      Value_ = Normalize(--Value_);

      return *this;
    }
    //  å„íuÉfÉNÉäÉÅÉìÉg
    Degree operator --(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(--Value_);

      return Degree;
    }
    //  î‰är
    constexpr bool operator ==(const Degree& _Degree)const noexcept
    {
      return (Value_ == _Degree.Value_);
    }
    //  î‰är
    constexpr bool operator !=(const Degree& _Degree)const noexcept
    {
      return !(*this == _Degree);
    }
    //  î‰är
    constexpr bool operator <(const Degree& _Degree)const noexcept
    {
      return (Value_ < _Degree.Value_);
    }
    //  î‰är
    constexpr bool operator >(const Degree& _Degree)const noexcept
    {
      return (Value_ > _Degree.Value_);
    }
    //  î‰är
    constexpr bool operator <=(const Degree& _Degree)const noexcept
    {
      return (Value_ <= _Degree.Value_);
    }
    //  î‰är
    constexpr bool operator >=(const Degree& _Degree)const noexcept
    {
      return (Value_ >= _Degree.Value_);
    }
  public:
    //  â¡éZ
    constexpr Degree operator +(float _Degree)const
    {
      return{ Normalize(Value_ + _Degree) };
    }
    //  å∏éZ
    constexpr Degree operator -(float _Degree)const
    {
      return{ Normalize(Value_ - _Degree) };
    }
    //  ë„ì¸
    Degree operator =(float _Degree)
    {
      return {Value_ = _Degree};
    }
    //  â¡éZå„ë„ì¸
    Degree operator +=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ + _Degree) };
    }
    //  å∏éZå„ë„ì¸
    Degree operator -=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ - _Degree) };
    }
    //  î‰är
    constexpr bool operator ==(float _Degree)const
    {
      return (Value_ == _Degree);
    }
    //  î‰är
    constexpr bool operator !=(float _Degree)const
    {
      return !(*this == _Degree);
    }
    //  î‰är
    constexpr bool operator <(float _Degree)const
    {
      return (Value_ < _Degree);
    }
    //  î‰är
    constexpr bool operator >(float _Degree)const
    {
      return (Value_ > _Degree);
    }
    //  î‰är
    constexpr bool operator <=(float _Degree)const
    {
      return (Value_ <= _Degree);
    }
    //  î‰är
    constexpr bool operator >=(float _Degree)const
    {
      return (Value_ >= _Degree);
    }
  public:
    //  â¡éZ
    friend constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept;
    //  å∏éZ
    friend constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept;
    //  î‰är
    friend constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept;
    //  î‰är
    friend constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept;
    //  î‰är
    friend constexpr bool operator <(float _Value, const Degree& _Degree)noexcept;
    //  î‰är
    friend constexpr bool operator >(float _Value, const Degree& _Degree)noexcept;
    //  î‰är
    friend constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept;
    //  î‰är
    friend constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept;
  };

  //  äpìxÇçÏê¨
  //  é©ìÆÇ≈ê≥ãKâªÇ≥ÇÍÇ‹Ç∑
  //  _Degree:ìxêîñ@
  inline constexpr Radian::Radian(const Degree& _Degree)noexcept
    : Value_(Normalize(Math::ToRadian(_Degree.GetValue())))
  {

  }
  //  â¡éZ
  inline constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept
  {
    return _Value + _Radian.Value_;
  }
  //  å∏éZ
  inline constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept
  {
    return _Value - _Radian.Value_;
  }
  //  î‰är
  inline constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept
  {
    return _Value == _Radian.Value_;
  }
  //  î‰är
  inline constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept
  {
    return !(_Value == _Radian);
  }
  //  î‰är
  inline constexpr bool operator <(float _Value, const Radian& _Radian)noexcept
  {
    return _Value < _Radian.Value_;
  }
  //  î‰är
  inline constexpr bool operator >(float _Value, const Radian& _Radian)noexcept
  {
    return _Value > _Radian.Value_;
  }
  //  î‰är
  inline constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value <= _Radian.Value_;
  }
  //  î‰är
  inline constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value >= _Radian.Value_;
  }

  //  â¡éZ
  inline constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept
  {
    return _Value + _Degree.Value_;
  }
  //  å∏éZ
  inline constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept
  {
    return _Value - _Degree.Value_;
  }
  //  î‰är
  inline constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept
  {
    return _Value == _Degree.Value_;
  }
  //  î‰är
  inline constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept
  {
    return !(_Value == _Degree);
  }
  //  î‰är
  inline constexpr bool operator <(float _Value, const Degree& _Degree)noexcept
  {
    return _Value < _Degree.Value_;
  }
  //  î‰är
  inline constexpr bool operator >(float _Value, const Degree& _Degree)noexcept
  {
    return _Value > _Degree.Value_;
  }
  //  î‰är
  inline constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value <= _Degree.Value_;
  }
  //  î‰är
  inline constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value >= _Degree.Value_;
  }
}
