#pragma once
#include <DirectXMath.h>

//  ���C�u����
namespace hdx
{
  //template <class Type>
  //struct Type2
  //{
  //  Type x, y;
  //public:
  //  constexpr Type2()
  //    : x(static_cast<Type>(0))
  //    , y(static_cast<Type>(0)) {}
  //
  //  constexpr Type2(Type _x, Type _y)
  //    : x(_x)
  //    , y(_y) {}
  //
  //  template <class X, class Y>
  //  constexpr Type2(X _x, Y _y)
  //    : x(static_cast<Type>(_x))
  //    , y(static_cast<Type>(_y)) {}
  //
  //  template <class T>
  //  constexpr Type2(const Type2<T>& _v)
  //    : x(static_cast<Type>(_v.x))
  //    , y(static_cast<Type>(_v.y)) {}
  //public:
  //  constexpr bool operator==(const Type2& _v)const { return x == _v.x && y == _v.y; }
  //
  //  constexpr bool operator!=(const Type2& _v)const { return !(*this == _v); }
  //
  //  constexpr Type2 operator+()const { return *this; }
  //
  //  constexpr Type2 operator-()const { return{ -x, -y }; }
  //
  //  constexpr Type2 operator+(const Type2& _v)const { return{ x + _v.x, y + _v.y }; }
  //
  //  constexpr Type2 operator-(const Type2& _v)const { return{ x - _v.x, y - _v.y }; }
  //
  //  constexpr Type2 operator*(Type _s)const { return{ x*_s, y*_s }; }
  //
  //  constexpr Type2 operator*(const Type2& _v)const { return{ x*_v.x, y*_v.y }; }
  //
  //  constexpr Type2 operator/(Type _s)const { return{ x / _s, y / _s }; }
  //
  //  Type2 operator+=(const Type2& _v) { x += _v.x; y += _v.y; return *this; }
  //
  //  Type2 operator-=(const Type2& _v) { x -= _v.x; y -= _v.y; return *this; }
  //
  //  Type2 operator*=(Type _s) { x *= _s; y *= _s; return *this; }
  //
  //  Type2 operator/=(Type _s) { x /= _s; y /= _s; return *this; }
  //};
  //
  //using int2 = Type2<int>;
  //using float2 = Type2<float>;

  struct float2;

  //  int��2�ۗL
  struct int2
  {
    int X;
    int Y;
  public:
    //  0�ŏ�����
    constexpr int2() : X(0), Y(0) {}
    //  int2���쐬
    //  _XY:X,Y
    constexpr int2(int _XY)noexcept : X(_XY), Y(_XY) {}
    //  int2���쐬
    //  _X:X
    //  _Y:Y
    constexpr int2(int _X, int _Y)noexcept : X(_X), Y(_Y) {}
    //  float2���쐬
    //  _int2:�R�s�[����l
    constexpr int2(const int2& _int2)noexcept : X(_int2.X), Y(_int2.Y) {}
    //  float2���쐬
    //  _float2:�R�s�[����F
    constexpr int2(const float2& _float2)noexcept;
  public:
    operator DirectX::XMINT2() const
    {
      return DirectX::XMINT2(X, Y);
    }
  public:
    //  ���̂܂܂̒l���擾
    constexpr int2 operator +()const
    {
      return{ X,Y };
    }
    //  �������]�����l���擾
    constexpr int2 operator -()const
    {
      return{ -X,-Y };
    }
  public:
    //  ���Z
    constexpr int2 operator +(const int2& _int2)const noexcept
    {
      return{ X + _int2.X, Y + _int2.Y };
    }
    //  ���Z
    constexpr int2 operator -(const int2& _int2)const noexcept
    {
      return{ X - _int2.X, Y - _int2.Y };
    }
    //  ��Z
    constexpr int2 operator *(const int2& _int2)const noexcept
    {
      return{ X * _int2.X, Y * _int2.Y };
    }
    //  ���Z
    constexpr int2 operator /(const int2& _int2)const noexcept
    {
      return{ X / _int2.X, Y / _int2.Y };
    }
    //  ���
    int2& operator =(const int2& _int2)noexcept
    {
      X = _int2.X;
      Y = _int2.Y;

      return *this;
    }
    //  ���Z����
    int2& operator +=(const int2& _int2)noexcept
    {
      X += _int2.X;
      Y += _int2.Y;

      return *this;
    }
    //  ���Z����
    int2& operator -=(const int2& _int2)noexcept
    {
      X -= _int2.X;
      Y -= _int2.Y;

      return *this;
    }
    //  ��Z����
    int2& operator *=(const int2& _int2)noexcept
    {
      X *= _int2.X;
      Y *= _int2.Y;

      return *this;
    }
    //  ���Z����
    int2& operator /=(const int2& _int2)noexcept
    {
      X /= _int2.X;
      Y /= _int2.Y;

      return *this;
    }
  public:
    //  ���Z
    constexpr int2 operator +(int _Value)const noexcept
    {
      return{ X + _Value, Y + _Value };
    }
    constexpr int2 operator +(float _Value)const noexcept
    {
      return{ static_cast<int>(X + _Value), static_cast<int>(Y + _Value) };
    }
    //  ���Z
    constexpr int2 operator -(int _Value)const noexcept
    {
      return{ X - _Value, Y - _Value };
    }
    constexpr int2 operator -(float _Value)const noexcept
    {
      return{ static_cast<int>(X - _Value), static_cast<int>(Y - _Value) };
    }
    //  ��Z
    constexpr int2 operator *(int _Value)const noexcept
    {
      return{ X * _Value, Y * _Value };
    }
    constexpr int2 operator *(float _Value)const noexcept
    {
      return{ static_cast<int>(X * _Value), static_cast<int>(Y * _Value) };
    }
    //  ���Z
    constexpr int2 operator /(int _Value)const noexcept
    {
      return{ X / _Value, Y / _Value };
    }
    constexpr int2 operator /(float _Value)const noexcept
    {
      return{ static_cast<int>(X / _Value), static_cast<int>(Y / _Value) };
    }
    //  ���
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
    //  ���Z����
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
    //  ���Z����
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
    //  ��Z����
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
    //  ���Z����
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
    //  ��r
    constexpr bool operator ==(const int2& _int2)const noexcept
    {
      return (X == _int2.X && Y == _int2.Y);
    }
    //  ��r
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

  //  float��2�ۗL
  struct float2
  {
    float X;
    float Y;
  public:
    //  0�ŏ�����
    constexpr float2() : X(0.0f), Y(0.0f) {}
    //  float2���쐬
    //  _XY:X,Y
    constexpr float2(int _XY)noexcept : X(static_cast<float>(_XY)), Y(static_cast<float>(_XY)) {}
    //  float2���쐬
    //  _XY:X,Y
    constexpr float2(float _XY)noexcept : X(_XY), Y(_XY) {}
    //  float2���쐬
    //  _X:X
    //  _Y:Y
    constexpr float2(int _X, int _Y)noexcept : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)) {}
    //  float2���쐬
    //  _X:X
    //  _Y:Y
    constexpr float2(float _X, float _Y)noexcept : X(_X), Y(_Y) {}
    //  float2���쐬
    //  _float2:�R�s�[����l
    constexpr float2(const float2& _float2)noexcept : X(_float2.X), Y(_float2.Y) {}
    //  float2���쐬
    //  _int2;�R�s�[����l
    constexpr float2(const int2& _int2)noexcept : X(static_cast<float>(_int2.X)), Y(static_cast<float>(_int2.Y)) {}
  public:
    operator DirectX::XMFLOAT2() const
    {
      return DirectX::XMFLOAT2(X, Y);
    }
  public:
    //  ���̂܂܂̒l���擾
    constexpr float2 operator +()const
    {
      return{ X,Y };
    }
    //  �������]�����l���擾
    constexpr float2 operator -()const
    {
      return{ -X,-Y };
    }
  public:
    //  ���Z
    constexpr float2 operator +(const float2& _float2)const noexcept
    {
      return{ X + _float2.X, Y + _float2.Y };
    }
    //  ���Z
    constexpr float2 operator -(const float2& _float2)const noexcept
    {
      return{ X - _float2.X, Y - _float2.Y };
    }
    //  ��Z
    constexpr float2 operator *(const float2& _float2)const noexcept
    {
      return{ X * _float2.X, Y * _float2.Y };
    }
    //  ���Z
    constexpr float2 operator /(const float2& _float2)const noexcept
    {
      return{ X / _float2.X, Y / _float2.Y };
    }
    //  ���
    float2& operator =(const float2& _float2)noexcept
    {
      X = _float2.X;
      Y = _float2.Y;

      return *this;
    }
    //  ���Z����
    float2& operator +=(const float2& _float2)noexcept
    {
      X += _float2.X;
      Y += _float2.Y;

      return *this;
    }
    //  ���Z����
    float2& operator -=(const float2& _float2)noexcept
    {
      X -= _float2.X;
      Y -= _float2.Y;

      return *this;
    }
    //  ��Z����
    float2& operator *=(const float2& _float2)noexcept
    {
      X *= _float2.X;
      Y *= _float2.Y;

      return *this;
    }
    //  ���Z����
    float2& operator /=(const float2& _float2)noexcept
    {
      X /= _float2.X;
      Y /= _float2.Y;

      return *this;
    }
  public:
    //  ���Z
    constexpr float2 operator +(int _Value)const noexcept
    {
      return{ X + _Value, Y + _Value };
    }
    //  ���Z
    constexpr float2 operator +(float _Value)const noexcept
    {
      return{ X + _Value, Y + _Value };
    }
    //  ���Z
    constexpr float2 operator -(int _Value)const noexcept
    {
      return{ X - _Value, Y - _Value };
    }
    //  ���Z
    constexpr float2 operator -(float _Value)const noexcept
    {
      return{ X - _Value, Y - _Value };
    }
    //  ��Z
    constexpr float2 operator *(int _Value)const noexcept
    {
      return{ X * _Value, Y * _Value };
    }
    //  ��Z
    constexpr float2 operator *(float _Value)const noexcept
    {
      return{ X * _Value, Y * _Value };
    }
    //  ���Z
    constexpr float2 operator /(int _Value)const noexcept
    {
      return{ X / _Value, Y / _Value };
    }
    //  ���Z
    constexpr float2 operator /(float _Value)const noexcept
    {
      return{ X / _Value, Y / _Value };
    }
    //  ���
    float2& operator =(float _Value)noexcept
    {
      X = _Value;
      Y = _Value;

      return *this;
    }
    //  ���Z����
    float2& operator +=(float _Value)noexcept
    {
      X += _Value;
      Y += _Value;

      return *this;
    }
    //  ���Z����
    float2& operator -=(float _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;

      return *this;
    }
    //  ��Z����
    float2& operator *=(float _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;

      return *this;
    }
    //  ���Z����
    float2& operator /=(float _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;

      return *this;
    }
  public:
    //  ��r
    constexpr bool operator ==(const float2& _float2)const noexcept
    {
      return (X == _float2.X && Y == _float2.Y);
    }
    //  ��r
    constexpr bool operator !=(const float2& _float2)const noexcept
    {
      return !(*this == _float2);
    }
  public:
    //  ���Z
    friend constexpr float2 operator +(float _Value, const float2& _float2)noexcept;
    //  ���Z
    friend constexpr float2 operator -(float _Value, const float2& _float2)noexcept;
    //  ��Z
    friend constexpr float2 operator *(float _Value, const float2& _float2)noexcept;
    //  ���Z
    friend constexpr float2 operator /(float _Value, const float2& _float2)noexcept;
    //  ��r
    friend constexpr bool operator ==(float _Value, const float2& _float2)noexcept;
    //  ��r
    friend constexpr bool operator !=(float _Value, const float2& _float2)noexcept;
  };

  //  float2���쐬
  //  _float2:�R�s�[����l
  inline constexpr int2::int2(const float2& _float2)noexcept
    : X(static_cast<int>(_float2.X)), Y(static_cast<int>(_float2.Y))
  {

  }
  //  ���Z
  inline constexpr int2 operator +(int _Value, const int2& _int2)noexcept
  {
    return{ _Value + _int2.X, _Value + _int2.Y };
  }
  inline constexpr int2 operator +(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value + _int2.X), static_cast<int>(_Value + _int2.Y) };
  }
  //  ���Z
  inline constexpr int2 operator -(int _Value, const int2& _int2)noexcept
  {
    return{ _Value - _int2.X, _Value - _int2.Y };
  }
  inline constexpr int2 operator -(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value - _int2.X), static_cast<int>(_Value - _int2.Y) };
  }
  //  ��Z
  inline constexpr int2 operator *(int _Value, const int2& _int2)noexcept
  {
    return{ _Value * _int2.X,_Value * _int2.Y };
  }
  inline constexpr int2 operator *(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value * _int2.X), static_cast<int>(_Value * _int2.Y) };
  }
  //  ���Z
  inline constexpr int2 operator /(int _Value, const int2& _int2)noexcept
  {
    return{ _Value / _int2.X,_Value / _int2.Y };
  }
  inline constexpr int2 operator /(float _Value, const int2& _int2)noexcept
  {
    return{ static_cast<int>(_Value / _int2.X), static_cast<int>(_Value / _int2.Y) };
  }
  //  ��r
  inline constexpr bool operator ==(int _Value, const int2& _int2)noexcept
  {
    return (_Value == _int2.X && _Value == _int2.Y);
  }
  inline constexpr bool operator ==(float _Value, const int2& _int2)noexcept
  {
    return (_Value == _int2.X && _Value == _int2.Y);
  }
  //  ��r
  inline constexpr bool operator !=(int _Value, const int2& _int2)noexcept
  {
    return !(_Value == _int2);
  }
  inline constexpr bool operator !=(float _Value, const int2& _int2)noexcept
  {
    return !(_Value == _int2);
  }

  //  ���Z
  inline constexpr float2 operator +(float _Value, const float2& _float2)noexcept
  {
    return{ _Value + _float2.X,_Value + _float2.Y };
  }
  //  ���Z
  inline constexpr float2 operator -(float _Value, const float2& _float2)noexcept
  {
    return{ _Value - _float2.X,_Value - _float2.Y };
  }
  //  ��Z
  inline constexpr float2 operator *(float _Value, const float2& _float2)noexcept
  {
    return{ _Value * _float2.X,_Value * _float2.Y };
  }
  //  ���Z
  inline constexpr float2 operator /(float _Value, const float2& _float2)noexcept
  {
    return{ _Value / _float2.X,_Value / _float2.Y };
  }
  //  ��r
  inline constexpr bool operator ==(float _Value, const float2& _float2)noexcept
  {
    return (_Value == _float2.X && _Value == _float2.Y);
  }
  //  ��r
  inline constexpr bool operator !=(float _Value, const float2& _float2)noexcept
  {
    return !(_Value == _float2);
  }
}
