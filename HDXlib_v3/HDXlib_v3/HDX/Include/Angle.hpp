#pragma once
#include "MathConstants.hpp"

//  �O���錾
namespace hdx
{
  class Degree;
}

//  ���C�u����
namespace hdx
{
  //  �ʓx�@
  //  �p�x��-��~�΂ŕ\�����܂�
  //  (�����Ő��K������܂�)
  class Radian
  {
    float Value_; //  �l
  public:
    //  ���K��(-��~�΂ɂ���)
    static constexpr float Normalize(float _Value)
    {
      return (-Math::PI <= _Value && _Value < Math::PI) ? _Value :
        (_Value - static_cast<int>((_Value + ((_Value < 0.0f) ? -Math::PI : Math::PI)) / Math::TwoPI)*Math::TwoPI);
    }
  public:
    //  0�ŏ�����
    constexpr Radian() : Value_(0.0f) {}
    //  �p�x���쐬
    //  �����Ő��K������܂�
    //  _Radian:�ʓx�@
    constexpr Radian(float _Radian)noexcept : Value_(Normalize(_Radian)) {}
    //  �p�x���쐬
    //  �����Ő��K������܂�
    //  _Radian:�ʓx�@
    constexpr Radian(const Radian& _Radian)noexcept : Value_(Normalize(_Radian.Value_)) {}
    //  �p�x���쐬
    //  �����Ő��K������܂�
    //  _Degree:�x���@
    constexpr Radian(const Degree& _Degree)noexcept;
  public:
    //  float�^�Ŏ擾
    constexpr float GetValue()const { return Value_; }
  public:
    //  ���̂܂܂̐��l���擾
    constexpr Radian operator +()const
    {
      return{ Value_ };
    }
    //  �������]�������l���擾
    constexpr Radian operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  ���Z
    constexpr Radian operator +(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ + _Radian.Value_);
    }
    //  ���Z
    constexpr Radian operator -(const Radian& _Radian)const noexcept
    {
      return Normalize(Value_ - _Radian.Value_);
    }
    //  ���
    Radian& operator =(const Radian& _Radian)noexcept
    {
      Value_ = _Radian.Value_;

      return *this;
    }
    //  ���Z����
    Radian& operator +=(const Radian& _Radian)noexcept
    {
      Value_ += _Radian.Value_;

      return *this;
    }
    //  ���Z����
    Radian& operator -=(const Radian& _Radian)noexcept
    {
      Value_ -= _Radian.Value_;
      return *this;
    }
    //  ��r���Z�q
    constexpr bool operator ==(const Radian& _Radian)const noexcept
    {
      return (Value_ == _Radian.Value_);
    }
    //  ��r
    constexpr bool operator !=(const Radian& _Radian)const noexcept
    {
      return !(*this == _Radian);
    }
    //  ��r
    constexpr bool operator <(const Radian& _Radian)const noexcept
    {
      return (Value_ < _Radian.Value_);
    }
    //  ��r
    constexpr bool operator >(const Radian& _Radian)const noexcept
    {
      return (Value_ > _Radian.Value_);
    }
    //  ��r
    constexpr bool operator <=(const Radian& _Radian)const noexcept
    {
      return (Value_ <= _Radian.Value_);
    }
    //  ��r
    constexpr bool operator >=(const Radian& _Radian)const noexcept
    {
      return (Value_ >= _Radian.Value_);
    }
  public:
    //  ���Z
    constexpr float operator +(float _Radian)const
    {
      return Normalize(Value_ + _Radian);
    }
    //  ���Z
    constexpr float operator -(float _Radian)const
    {
      return Normalize(Value_ - _Radian);
    }
    //  ���Z
    constexpr float operator *(float _Value)const
    {
      return Normalize(Value_ * _Value);
    }
    //  ���Z
    constexpr float operator /(float _Value)const
    {
      return Normalize(Value_ / _Value);
    }
    //  ���
    float operator =(float _Radian)
    {
      return Value_ = _Radian;
    }
    //  ���Z����
    float operator +=(float _Radian)
    {
      return Value_ = Normalize(Value_ + _Radian);
    }
    //  ���Z����
    float operator -=(float _Radian)
    {
      return Value_ = Normalize(Value_ - _Radian);
    }
    //  ��r
    constexpr bool operator ==(float _Radian)const
    {
      return (Value_ == _Radian);
    }
    //  ��r
    constexpr bool operator !=(float _Radian)const
    {
      return !(*this == _Radian);
    }
    //  ��r
    constexpr bool operator <(float _Radian)const
    {
      return (Value_ < _Radian);
    }
    //  ��r
    constexpr bool operator >(float _Radian)const
    {
      return (Value_ > _Radian);
    }
    //  ��r
    constexpr bool operator <=(float _Radian)const
    {
      return (Value_ <= _Radian);
    }
    //  ��r
    constexpr bool operator >=(float _Radian)const
    {
      return (Value_ >= _Radian);
    }
  public:
    //  ���Z
    friend constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept;
    //  ���Z
    friend constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept;
    //  ��r
    friend constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept;
    //  ��r
    friend constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept;
    //  ��r
    friend constexpr bool operator <(float _Value, const Radian& _Radian)noexcept;
    //  ��r
    friend constexpr bool operator >(float _Value, const Radian& _Radian)noexcept;
    //  ��r
    friend constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept;
    //  ��r
    friend constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept;
  };

  //  �x���@
  //  �p�x��-180~180�ŕ\�����܂�
  //  (�����Ő��K������܂�)
  class Degree
  {
    float Value_; //  �l
  public:
    //  ���K��(-180~180�x�ɂ���)
    static constexpr float Normalize(float _Value)
    {
      return (-180.0f <= _Value && _Value < 180.0f) ? _Value :
        (_Value - static_cast<int>((_Value + ((_Value < 0.0f) ? -180.0f : 180.0f)) / 360.0f)*360.0f);
    }
  public:
    //  0�ŏ�����
    constexpr Degree() : Value_(0.0f) {}
    //  �p�x���쐬
    //  �����Ő��K������܂�
    //  _Degree:�x���@
    constexpr Degree(float _Degree)noexcept : Value_(Normalize(_Degree)) {}
    //  �p�x���쐬
    //  �����Ő��K������܂�
    //  _Degree:�x���@
    constexpr Degree(const Degree& _Degree)noexcept : Value_(Normalize(_Degree.Value_)) {}
    //  �p�x���쐬
    //  �����Ő��K������܂�
    //  _Radian:�ʓx�@
    constexpr Degree(const Radian& _Radian)noexcept : Value_(Normalize(Math::ToDegree(_Radian.GetValue()))) {}
  public:
    //  float�^�Ŏ擾
    constexpr float GetValue()const { return Value_; }
  public:
    //  ���̂܂܂̐��l���擾
    constexpr Degree operator +()const
    {
      return{ Value_ };
    }
    //  �������]�������l���擾
    constexpr Degree operator -()const
    {
      return{ -Value_ };
    }
  public:
    //  ���Z
    constexpr Degree operator +(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ + _Degree.Value_);
    }
    //  ���
    constexpr Degree operator -(const Degree& _Degree)const noexcept
    {
      return Normalize(Value_ - _Degree.Value_);
    }
    //  ���
    Degree& operator =(const Degree& _Degree)noexcept
    {
      Value_ = _Degree.Value_;
      return *this;
    }
    //  ���Z����
    Degree& operator +=(const Degree& _Degree)noexcept
    {
      Value_ += _Degree.Value_;
      return *this;
    }
    //  ���Z����
    Degree& operator -=(const Degree& _Degree)noexcept
    {
      Value_ -= _Degree.Value_;
      return *this;
    }
    //  �O�u�C���N�������g
    Degree& operator ++()
    {
      Value_ = Normalize(++Value_);

      return *this;
    }
    //  ��u�C���N�������g
    Degree operator ++(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(++Value_);

      return Degree;
    }
    //  �O�u�f�N�������g
    Degree& operator --()
    {
      Value_ = Normalize(--Value_);

      return *this;
    }
    //  ��u�f�N�������g
    Degree operator --(int)
    {
      Degree Degree = *this;
      Value_ = Normalize(--Value_);

      return Degree;
    }
    //  ��r
    constexpr bool operator ==(const Degree& _Degree)const noexcept
    {
      return (Value_ == _Degree.Value_);
    }
    //  ��r
    constexpr bool operator !=(const Degree& _Degree)const noexcept
    {
      return !(*this == _Degree);
    }
    //  ��r
    constexpr bool operator <(const Degree& _Degree)const noexcept
    {
      return (Value_ < _Degree.Value_);
    }
    //  ��r
    constexpr bool operator >(const Degree& _Degree)const noexcept
    {
      return (Value_ > _Degree.Value_);
    }
    //  ��r
    constexpr bool operator <=(const Degree& _Degree)const noexcept
    {
      return (Value_ <= _Degree.Value_);
    }
    //  ��r
    constexpr bool operator >=(const Degree& _Degree)const noexcept
    {
      return (Value_ >= _Degree.Value_);
    }
  public:
    //  ���Z
    constexpr Degree operator +(float _Degree)const
    {
      return{ Normalize(Value_ + _Degree) };
    }
    //  ���Z
    constexpr Degree operator -(float _Degree)const
    {
      return{ Normalize(Value_ - _Degree) };
    }
    //  ���
    Degree operator =(float _Degree)
    {
      return {Value_ = _Degree};
    }
    //  ���Z����
    Degree operator +=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ + _Degree) };
    }
    //  ���Z����
    Degree operator -=(float _Degree)
    {
      return{ Value_ = Normalize(Value_ - _Degree) };
    }
    //  ��r
    constexpr bool operator ==(float _Degree)const
    {
      return (Value_ == _Degree);
    }
    //  ��r
    constexpr bool operator !=(float _Degree)const
    {
      return !(*this == _Degree);
    }
    //  ��r
    constexpr bool operator <(float _Degree)const
    {
      return (Value_ < _Degree);
    }
    //  ��r
    constexpr bool operator >(float _Degree)const
    {
      return (Value_ > _Degree);
    }
    //  ��r
    constexpr bool operator <=(float _Degree)const
    {
      return (Value_ <= _Degree);
    }
    //  ��r
    constexpr bool operator >=(float _Degree)const
    {
      return (Value_ >= _Degree);
    }
  public:
    //  ���Z
    friend constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept;
    //  ���Z
    friend constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept;
    //  ��r
    friend constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept;
    //  ��r
    friend constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept;
    //  ��r
    friend constexpr bool operator <(float _Value, const Degree& _Degree)noexcept;
    //  ��r
    friend constexpr bool operator >(float _Value, const Degree& _Degree)noexcept;
    //  ��r
    friend constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept;
    //  ��r
    friend constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept;
  };

  //  �p�x���쐬
  //  �����Ő��K������܂�
  //  _Degree:�x���@
  inline constexpr Radian::Radian(const Degree& _Degree)noexcept
    : Value_(Normalize(Math::ToRadian(_Degree.GetValue())))
  {

  }
  //  ���Z
  inline constexpr Radian operator +(float _Value, const Radian& _Radian)noexcept
  {
    return _Value + _Radian.Value_;
  }
  //  ���Z
  inline constexpr Radian operator -(float _Value, const Radian& _Radian)noexcept
  {
    return _Value - _Radian.Value_;
  }
  //  ��r
  inline constexpr bool operator ==(float _Value, const Radian& _Radian)noexcept
  {
    return _Value == _Radian.Value_;
  }
  //  ��r
  inline constexpr bool operator !=(float _Value, const Radian& _Radian)noexcept
  {
    return !(_Value == _Radian);
  }
  //  ��r
  inline constexpr bool operator <(float _Value, const Radian& _Radian)noexcept
  {
    return _Value < _Radian.Value_;
  }
  //  ��r
  inline constexpr bool operator >(float _Value, const Radian& _Radian)noexcept
  {
    return _Value > _Radian.Value_;
  }
  //  ��r
  inline constexpr bool operator <=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value <= _Radian.Value_;
  }
  //  ��r
  inline constexpr bool operator >=(float _Value, const Radian& _Radian)noexcept
  {
    return _Value >= _Radian.Value_;
  }

  //  ���Z
  inline constexpr Degree operator +(float _Value, const Degree& _Degree)noexcept
  {
    return _Value + _Degree.Value_;
  }
  //  ���Z
  inline constexpr Degree operator -(float _Value, const Degree& _Degree)noexcept
  {
    return _Value - _Degree.Value_;
  }
  //  ��r
  inline constexpr bool operator ==(float _Value, const Degree& _Degree)noexcept
  {
    return _Value == _Degree.Value_;
  }
  //  ��r
  inline constexpr bool operator !=(float _Value, const Degree& _Degree)noexcept
  {
    return !(_Value == _Degree);
  }
  //  ��r
  inline constexpr bool operator <(float _Value, const Degree& _Degree)noexcept
  {
    return _Value < _Degree.Value_;
  }
  //  ��r
  inline constexpr bool operator >(float _Value, const Degree& _Degree)noexcept
  {
    return _Value > _Degree.Value_;
  }
  //  ��r
  inline constexpr bool operator <=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value <= _Degree.Value_;
  }
  //  ��r
  inline constexpr bool operator >=(float _Value, const Degree& _Degree)noexcept
  {
    return _Value >= _Degree.Value_;
  }
}
