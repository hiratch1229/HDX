#pragma once

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  struct float2;

  //  int‚ğ2‚Â•Û—L
  struct int2
  {
    int X;
    int Y;
  public:
    //  0‚Å‰Šú‰»
    constexpr int2() : X(0), Y(0) {}
    //  int2‚ğì¬
    //  _XY:X,Y
    constexpr int2(int _XY)noexcept : X(_XY), Y(_XY) {}
    //  int2‚ğì¬
    //  _X:X
    //  _Y:Y
    constexpr int2(int _X, int _Y)noexcept : X(_X), Y(_Y) {}
    //  float2‚ğì¬
    //  _int2:ƒRƒs[‚·‚é’l
    constexpr int2(const int2& _int2)noexcept : X(_int2.X), Y(_int2.Y) {}
    //  float2‚ğì¬
    //  _float2:ƒRƒs[‚·‚éF
    constexpr int2(const float2& _float2)noexcept;
  public:
    //  ‚»‚Ì‚Ü‚Ü‚Ì’l‚ğæ“¾
    constexpr int2 operator +()const
    {
      return{ X,Y };
    }
    //  •„†”½“]‚µ‚½’l‚ğæ“¾
    constexpr int2 operator -()const
    {
      return{ -X,-Y };
    }
  public:
    //  ‰ÁZ
    constexpr int2 operator +(const int2& _int2)const noexcept
    {
      return{ X + _int2.X, Y + _int2.Y };
    }
    //  Œ¸Z
    constexpr int2 operator -(const int2& _int2)const noexcept
    {
      return{ X - _int2.X, Y - _int2.Y };
    }
    //  æZ
    constexpr int2 operator *(const int2& _int2)const noexcept
    {
      return{ X * _int2.X, Y * _int2.Y };
    }
    //  œZ
    constexpr int2 operator /(const int2& _int2)const noexcept
    {
      return{ X / _int2.X, Y / _int2.Y };
    }
    //  ‘ã“ü
    int2& operator =(const int2& _int2)noexcept
    {
      X = _int2.X;
      Y = _int2.Y;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    int2& operator +=(const int2& _int2)noexcept
    {
      X += _int2.X;
      Y += _int2.Y;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    int2& operator -=(const int2& _int2)noexcept
    {
      X -= _int2.X;
      Y -= _int2.Y;

      return *this;
    }
    //  æZŒã‘ã“ü
    int2& operator *=(const int2& _int2)noexcept
    {
      X *= _int2.X;
      Y *= _int2.Y;

      return *this;
    }
    //  œZŒã‘ã“ü
    int2& operator /=(const int2& _int2)noexcept
    {
      X /= _int2.X;
      Y /= _int2.Y;

      return *this;
    }
  public:
    //  ‰ÁZ
    constexpr int2 operator +(int _Value)const noexcept
    {
      return{ X + _Value, Y + _Value };
    }
    constexpr int2 operator +(float _Value)const noexcept
    {
      return{ static_cast<int>(X + _Value), static_cast<int>(Y + _Value) };
    }
    //  Œ¸Z
    constexpr int2 operator -(int _Value)const noexcept
    {
      return{ X - _Value, Y - _Value };
    }
    constexpr int2 operator -(float _Value)const noexcept
    {
      return{ static_cast<int>(X - _Value), static_cast<int>(Y - _Value) };
    }
    //  æZ
    constexpr int2 operator *(int _Value)const noexcept
    {
      return{ X * _Value, Y * _Value };
    }
    constexpr int2 operator *(float _Value)const noexcept
    {
      return{ static_cast<int>(X * _Value), static_cast<int>(Y * _Value) };
    }
    //  œZ
    constexpr int2 operator /(int _Value)const noexcept
    {
      return{ X / _Value, Y / _Value };
    }
    constexpr int2 operator /(float _Value)const noexcept
    {
      return{ static_cast<int>(X / _Value), static_cast<int>(Y / _Value) };
    }
    //  ‘ã“ü
    int2& operator =(int _Value)noexcept
    {
      X = _Value;
      Y = _Value;

      return *this;
    }
    int2& operator =(float _Value)noexcept
    {
      X = static_cast<int>(_Value);
      Y = static_cast<int>(_Value);

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    int2& operator +=(int _Value)noexcept
    {
      X += _Value;
      Y += _Value;

      return *this;
    }
    int2& operator +=(float _Value)noexcept
    {
      X += static_cast<int>(_Value);
      Y += static_cast<int>(_Value);

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    int2& operator -=(int _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;

      return *this;
    }
    int2& operator -=(float _Value)noexcept
    {
      X -= static_cast<int>(_Value);
      Y -= static_cast<int>(_Value);

      return *this;
    }
    //  æZŒã‘ã“ü
    int2& operator *=(int _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;

      return *this;
    }
    int2& operator *=(float _Value)noexcept
    {
      X *= static_cast<int>(_Value);
      Y *= static_cast<int>(_Value);

      return *this;
    }
    //  œZŒã‘ã“ü
    int2& operator /=(int _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;

      return *this;
    }
    int2& operator /=(float _Value)noexcept
    {
      X /= static_cast<int>(_Value);
      Y /= static_cast<int>(_Value);

      return *this;
    }
  public:
    //  ”äŠr
    constexpr bool operator ==(const int2& _int2)const noexcept
    {
      return (X == _int2.X && Y == _int2.Y);
    }
    //  ”äŠr
    constexpr bool operator !=(const int2& _int2)const noexcept
    {
      return !(*this == _int2);
    }
  public:
    friend constexpr int2 operator +(int _Value, const int2& _int2)noexcept;
    friend constexpr int2 operator +(float _Value, const int2& _int2)noexcept;

    friend constexpr int2 operator -(int _Value, const int2& _int2)noexcept;
    friend constexpr int2 operator -(float _Value, const int2& _int2)noexcept;

    friend constexpr int2 operator *(int _Value, const int2& _int2)noexcept;
    friend constexpr int2 operator *(float _Value, const int2& _int2)noexcept;

    friend constexpr int2 operator /(int _Value, const int2& _int2)noexcept;
    friend constexpr int2 operator /(float _Value, const int2& _int2)noexcept;

    friend constexpr bool operator ==(int _Value, const int2& _int2)noexcept;
    friend constexpr bool operator ==(float _Value, const int2& _int2)noexcept;

    friend constexpr bool operator !=(int _Value, const int2& _int2)noexcept;
    friend constexpr bool operator !=(float _Value, const int2& _int2)noexcept;
  };

  //  float‚ğ2‚Â•Û—L
  struct float2
  {
    float X;
    float Y;
  public:
    //  0‚Å‰Šú‰»
    constexpr float2() : X(0.0f), Y(0.0f) {}
    //  float2‚ğì¬
    //  _XY:X,Y
    constexpr float2(float _XY)noexcept : X(_XY), Y(_XY) {}
    //  float2‚ğì¬
    //  _X:X
    //  _Y:Y
    constexpr float2(float _X, float _Y)noexcept : X(_X), Y(_Y) {}
    //  float2‚ğì¬
    //  _float2:ƒRƒs[‚·‚é’l
    constexpr float2(const float2& _float2)noexcept : X(_float2.X), Y(_float2.Y) {}
    //  float2‚ğì¬
    //  _int2;ƒRƒs[‚·‚é’l
    constexpr float2(const int2& _int2)noexcept : X(static_cast<float>(_int2.X)), Y(static_cast<float>(_int2.Y)) {}
  public:
    //  ‚»‚Ì‚Ü‚Ü‚Ì’l‚ğæ“¾
    constexpr float2 operator +()const
    {
      return{ X,Y };
    }
    //  •„†”½“]‚µ‚½’l‚ğæ“¾
    constexpr float2 operator -()const
    {
      return{ -X,-Y };
    }
  public:
    //  ‰ÁZ
    constexpr float2 operator +(const float2& _float2)const noexcept
    {
      return{ X + _float2.X, Y + _float2.Y };
    }
    //  Œ¸Z
    constexpr float2 operator -(const float2& _float2)const noexcept
    {
      return{ X - _float2.X, Y - _float2.Y };
    }
    //  æZ
    constexpr float2 operator *(const float2& _float2)const noexcept
    {
      return{ X * _float2.X, Y * _float2.Y };
    }
    //  œZ
    constexpr float2 operator /(const float2& _float2)const noexcept
    {
      return{ X / _float2.X, Y / _float2.Y };
    }
    //  ‘ã“ü
    float2& operator =(const float2& _float2)noexcept
    {
      X = _float2.X;
      Y = _float2.Y;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    float2& operator +=(const float2& _float2)noexcept
    {
      X += _float2.X;
      Y += _float2.Y;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    float2& operator -=(const float2& _float2)noexcept
    {
      X -= _float2.X;
      Y -= _float2.Y;

      return *this;
    }
    //  æZŒã‘ã“ü
    float2& operator *=(const float2& _float2)noexcept
    {
      X *= _float2.X;
      Y *= _float2.Y;

      return *this;
    }
    //  œZŒã‘ã“ü
    float2& operator /=(const float2& _float2)noexcept
    {
      X /= _float2.X;
      Y /= _float2.Y;

      return *this;
    }
  public:
    //  ‰ÁZ
    constexpr float2 operator +(int _Value)const noexcept
    {
      return{ X + _Value, Y + _Value };
    }
    //  ‰ÁZ
    constexpr float2 operator +(float _Value)const noexcept
    {
      return{ X + _Value, Y + _Value };
    }
    //  Œ¸Z
    constexpr float2 operator -(int _Value)const noexcept
    {
      return{ X - _Value, Y - _Value };
    }
    //  Œ¸Z
    constexpr float2 operator -(float _Value)const noexcept
    {
      return{ X - _Value, Y - _Value };
    }
    //  æZ
    constexpr float2 operator *(int _Value)const noexcept
    {
      return{ X * _Value, Y * _Value };
    }
    //  æZ
    constexpr float2 operator *(float _Value)const noexcept
    {
      return{ X * _Value, Y * _Value };
    }
    //  œZ
    constexpr float2 operator /(int _Value)const noexcept
    {
      return{ X / _Value, Y / _Value };
    }
    //  œZ
    constexpr float2 operator /(float _Value)const noexcept
    {
      return{ X / _Value, Y / _Value };
    }
    //  ‘ã“ü
    float2& operator =(float _Value)noexcept
    {
      X = _Value;
      Y = _Value;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    float2& operator +=(float _Value)noexcept
    {
      X += _Value;
      Y += _Value;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    float2& operator -=(float _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;

      return *this;
    }
    //  æZŒã‘ã“ü
    float2& operator *=(float _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;

      return *this;
    }
    //  œZŒã‘ã“ü
    float2& operator /=(float _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;

      return *this;
    }
  public:
    //  ”äŠr
    constexpr bool operator ==(const float2& _float2)const noexcept
    {
      return (X == _float2.X && Y == _float2.Y);
    }
    //  ”äŠr
    constexpr bool operator !=(const float2& _float2)const noexcept
    {
      return !(*this == _float2);
    }
  public:
    //  ‰ÁZ
    friend constexpr float2 operator +(float _Value, const float2& _float2)noexcept;
    //  Œ¸Z
    friend constexpr float2 operator -(float _Value, const float2& _float2)noexcept;
    //  æZ
    friend constexpr float2 operator *(float _Value, const float2& _float2)noexcept;
    //  œZ
    friend constexpr float2 operator /(float _Value, const float2& _float2)noexcept;
    //  ”äŠr
    friend constexpr bool operator ==(float _Value, const float2& _float2)noexcept;
    //  ”äŠr
    friend constexpr bool operator !=(float _Value, const float2& _float2)noexcept;
  };

  //  float2‚ğì¬
  //  _float2:ƒRƒs[‚·‚é’l
  inline constexpr int2::int2(const float2& _float2)noexcept
    : X(static_cast<int>(_float2.X)), Y(static_cast<int>(_float2.Y))
  {

  }
  //  ‰ÁZ
  inline constexpr int2 operator +(int _Value, const int2& _int2)noexcept
  {
    return{ _Value + _int2.X, _Value + _int2.Y };
  }
  inline constexpr int2 operator +(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value + _int2.X), static_cast<int>(_Value + _int2.Y) };
  }
  //  Œ¸Z
  inline constexpr int2 operator -(int _Value, const int2& _int2)noexcept
  {
    return{ _Value - _int2.X, _Value - _int2.Y };
  }
  inline constexpr int2 operator -(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value - _int2.X), static_cast<int>(_Value - _int2.Y) };
  }
  //  æZ
  inline constexpr int2 operator *(int _Value, const int2& _int2)noexcept
  {
    return{ _Value * _int2.X,_Value * _int2.Y };
  }
  inline constexpr int2 operator *(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value * _int2.X), static_cast<int>(_Value * _int2.Y) };
  }
  //  œZ
  inline constexpr int2 operator /(int _Value, const int2& _int2)noexcept
  {
    return{ _Value / _int2.X,_Value / _int2.Y };
  }
  inline constexpr int2 operator /(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value / _int2.X), static_cast<int>(_Value / _int2.Y) };
  }
  //  ”äŠr
  inline constexpr bool operator ==(int _Value, const int2& _int2)noexcept
  {
    return (_Value == _int2.X && _Value == _int2.Y);
  }
  inline constexpr bool operator ==(float _Value, const int2& _int2)noexcept
  {
    return (_Value == _int2.X && _Value == _int2.Y);
  }
  //  ”äŠr
  inline constexpr bool operator !=(int _Value, const int2& _int2)noexcept
  {
    return !(_Value == _int2);
  }
  inline constexpr bool operator !=(float _Value, const int2& _int2)noexcept
  {
    return !(_Value == _int2);
  }

  //  ‰ÁZ
  inline constexpr float2 operator +(float _Value, const float2& _float2)noexcept
  {
    return{ _Value + _float2.X,_Value + _float2.Y };
  }
  //  Œ¸Z
  inline constexpr float2 operator -(float _Value, const float2& _float2)noexcept
  {
    return{ _Value - _float2.X,_Value - _float2.Y };
  }
  //  æZ
  inline constexpr float2 operator *(float _Value, const float2& _float2)noexcept
  {
    return{ _Value * _float2.X,_Value * _float2.Y };
  }
  //  œZ
  inline constexpr float2 operator /(float _Value, const float2& _float2)noexcept
  {
    return{ _Value / _float2.X,_Value / _float2.Y };
  }
  //  ”äŠr
  inline constexpr bool operator ==(float _Value, const float2& _float2)noexcept
  {
    return (_Value == _float2.X && _Value == _float2.Y);
  }
  //  ”äŠr
  inline constexpr bool operator !=(float _Value, const float2& _float2)noexcept
  {
    return !(_Value == _float2);
  }
}
