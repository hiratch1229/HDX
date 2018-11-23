#pragma once

//  ���C�u����
namespace hdx
{
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
    constexpr float2(float _XY)noexcept : X(_XY), Y(_XY) {}
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
