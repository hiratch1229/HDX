#pragma once
#include <DirectXMath.h>

//  ライブラリ
namespace hdx
{
  struct float3;

  //  intを3つ保有
  struct int3
  {
    int X;
    int Y;
    int Z;
  public:
    //  0で初期化
    constexpr int3() : X(0), Y(0), Z(0) {}
    //  int3を作成
    //  _XYZ:X,Y,Z
    constexpr int3(int _XYZ)noexcept : X(_XYZ), Y(_XYZ), Z(_XYZ) {}
    //  int3を作成
    //  _X:X
    //  _Y:Y
    //  _Z:Z
    constexpr int3(int _X, int _Y, int _Z)noexcept : X(_X), Y(_Y), Z(_Z) {}
    //  int3を作成
    //  _int3:コピーする値
    constexpr int3(const int3& _int3)noexcept : X(_int3.X), Y(_int3.Y), Z(_int3.Z) {}
    //  float3を作成
    //  _float3;コピーする値 
    constexpr int3(const float3& _float3)noexcept;
  public:
    operator DirectX::XMINT3() const
    {
      return DirectX::XMINT3(X, Y, Z);
    }
  public:
    //  そのままの値を取得
    constexpr int3 operator +()const
    {
      return{ X, Y, Z };
    }
    //  符号反転した値を取得
    constexpr int3 operator -()const
    {
      return{ -X, -Y, -Z };
    }
  public:
    //  加算
    constexpr int3 operator +(const int3& _int3)const noexcept
    {
      return{ X + _int3.X, Y + _int3.Y, Z + _int3.Z };
    }
    //  減算
    constexpr int3 operator -(const int3& _int3)const noexcept
    {
      return{ X - _int3.X, Y - _int3.Y, Z - _int3.Z };
    }
    //  乗算
    constexpr int3 operator *(const int3& _int3)const noexcept
    {
      return{ X * _int3.X, Y * _int3.Y, Z * _int3.Z };
    }
    //  除算
    constexpr int3 operator /(const int3& _int3)const noexcept
    {
      return{ X / _int3.X, Y / _int3.Y, Z / _int3.Z };
    }
    //  代入
    int3& operator =(const int3& _int3)noexcept
    {
      X = _int3.X;
      Y = _int3.Y;
      Z = _int3.Z;

      return *this;
    }
    //  加算後代入
    int3& operator +=(const int3& _int3)noexcept
    {
      X += _int3.X;
      Y += _int3.Y;
      Z += _int3.Z;

      return *this;
    }
    //  減算後代入
    int3& operator -=(const int3& _int3)noexcept
    {
      X -= _int3.X;
      Y -= _int3.Y;
      Z -= _int3.Z;

      return *this;
    }
    //  乗算後代入
    int3& operator *=(const int3& _int3)noexcept
    {
      X *= _int3.X;
      Y *= _int3.Y;
      Z *= _int3.Z;

      return *this;
    }
    //  除算後代入
    int3& operator /=(const int3& _int3)noexcept
    {
      X /= _int3.X;
      Y /= _int3.Y;
      Z /= _int3.Z;

      return *this;
    }
  public:
    //  加算
    constexpr int3 operator +(int _Value)const noexcept
    {
      return{ X + _Value, Y + _Value, Z + _Value };
    }
    //  減算
    constexpr int3 operator -(int _Value)const noexcept
    {
      return{ X - _Value, Y - _Value, Z - _Value };
    }
    //  乗算
    constexpr int3 operator *(int _Value)const noexcept
    {
      return{ X * _Value, Y * _Value, Z * _Value };;
    }
    //  除算
    constexpr int3 operator /(int _Value)const noexcept
    {
      return{ X / _Value, Y / _Value, Z / _Value };
    }
    //  代入
    int3& operator =(int _Value)noexcept
    {
      X = _Value;
      Y = _Value;
      Z = _Value;

      return *this;
    }
    //  加算後代入
    int3& operator +=(int _Value)noexcept
    {
      X += _Value;
      Y += _Value;
      Z += _Value;

      return *this;
    }
    //  減算後代入
    int3& operator -=(int _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;
      Z -= _Value;

      return *this;
    }
    //  乗算後代入
    int3& operator *=(int _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;
      Z *= _Value;

      return *this;
    }
    //  除算後代入
    int3& operator /=(int _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;
      Z /= _Value;

      return *this;
    }
  public:
    //  比較
    constexpr bool operator ==(const int3& _int3)const noexcept
    {
      return (X == _int3.X && Y == _int3.Y && Z == _int3.Z);
    }
    //  比較
    constexpr bool operator !=(const int3& _int3)const noexcept
    {
      return !(*this == _int3);
    }
  public:
    //  加算
    friend constexpr int3 operator +(int _Value, const int3& _int3)noexcept;
    //  減算
    friend constexpr int3 operator -(int _Value, const int3& _int3)noexcept;
    //  乗算
    friend constexpr int3 operator *(int _Value, const int3& _int3)noexcept;
    //  除算
    friend constexpr int3 operator /(int _Value, const int3& _int3)noexcept;
    //  比較
    friend constexpr bool operator ==(int _Value, const int3& _int3)noexcept;
    //  比較
    friend constexpr bool operator !=(int _Value, const int3& _int3)noexcept;
  };

  //  floatを3つ保有
  struct float3
  {
    float X;
    float Y;
    float Z;
  public:
    //  0で初期化
    constexpr float3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    //  float3を作成
    //  _XYZ:X,Y,Z
    constexpr float3(float _XYZ)noexcept : X(_XYZ), Y(_XYZ), Z(_XYZ) {}
    //  float3を作成
    //  _X:X
    //  _Y:Y
    //  _Z:Z
    constexpr float3(float _X, float _Y, float _Z)noexcept : X(_X), Y(_Y), Z(_Z) {}
    //  float3を作成
    //  _float3:コピーする値
    constexpr float3(const float3& _float3)noexcept : X(_float3.X), Y(_float3.Y), Z(_float3.Z) {}
    //  float3を作成
      //  _int3:コピーする値
    constexpr float3(const int3& _int3)noexcept : X(static_cast<float>(_int3.X)), Y(static_cast<float>(_int3.Y)), Z(static_cast<float>(_int3.Z)) {}
  public:
    operator DirectX::XMFLOAT3() const
    {
      return DirectX::XMFLOAT3(X, Y, Z);
    }
  public:
    //  そのままの値を取得
    constexpr float3 operator +()const
    {
      return{ X, Y, Z };
    }
    //  符号反転した値を取得
    constexpr float3 operator -()const
    {
      return{ -X, -Y, -Z };
    }
  public:
    //  加算
    constexpr float3 operator +(const float3& _float3)const noexcept
    {
      return{ X + _float3.X, Y + _float3.Y, Z + _float3.Z };
    }
    //  減算
    constexpr float3 operator -(const float3& _float3)const noexcept
    {
      return{ X - _float3.X, Y - _float3.Y, Z - _float3.Z };
    }
    //  乗算
    constexpr float3 operator *(const float3& _float3)const noexcept
    {
      return{ X * _float3.X, Y * _float3.Y, Z * _float3.Z };
    }
    //  除算
    constexpr float3 operator /(const float3& _float3)const noexcept
    {
      return{ X / _float3.X, Y / _float3.Y, Z / _float3.Z };
    }
    //  代入
    float3& operator =(const float3& _float3)noexcept
    {
      X = _float3.X;
      Y = _float3.Y;
      Z = _float3.Z;

      return *this;
    }
    //  加算後代入
    float3& operator +=(const float3& _float3)noexcept
    {
      X += _float3.X;
      Y += _float3.Y;
      Z += _float3.Z;

      return *this;
    }
    //  減算後代入
    float3& operator -=(const float3& _float3)noexcept
    {
      X -= _float3.X;
      Y -= _float3.Y;
      Z -= _float3.Z;

      return *this;
    }
    //  乗算後代入
    float3& operator *=(const float3& _float3)noexcept
    {
      X *= _float3.X;
      Y *= _float3.Y;
      Z *= _float3.Z;

      return *this;
    }
    //  除算後代入
    float3& operator /=(const float3& _float3)noexcept
    {
      X /= _float3.X;
      Y /= _float3.Y;
      Z /= _float3.Z;

      return *this;
    }
  public:
    //  加算
    constexpr float3 operator +(float _Value)const noexcept
    {
      return{ X + _Value, Y + _Value, Z + _Value };
    }
    //  減算
    constexpr float3 operator -(float _Value)const noexcept
    {
      return{ X - _Value, Y - _Value, Z - _Value };
    }
    //  乗算
    constexpr float3 operator *(float _Value)const noexcept
    {
      return{ X * _Value, Y * _Value, Z * _Value };;
    }
    //  除算
    constexpr float3 operator /(float _Value)const noexcept
    {
      return{ X / _Value, Y / _Value, Z / _Value };
    }
    //  代入
    float3& operator =(float _Value)noexcept
    {
      X = _Value;
      Y = _Value;
      Z = _Value;

      return *this;
    }
    //  加算後代入
    float3& operator +=(float _Value)noexcept
    {
      X += _Value;
      Y += _Value;
      Z += _Value;

      return *this;
    }
    //  減算後代入
    float3& operator -=(float _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;
      Z -= _Value;

      return *this;
    }
    //  乗算後代入
    float3& operator *=(float _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;
      Z *= _Value;

      return *this;
    }
    //  除算後代入
    float3& operator /=(float _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;
      Z /= _Value;

      return *this;
    }
  public:
    //  比較
    constexpr bool operator ==(const float3& _float3)const noexcept
    {
      return (X == _float3.X && Y == _float3.Y && Z == _float3.Z);
    }
    //  比較
    constexpr bool operator !=(const float3& _float3)const noexcept
    {
      return !(*this == _float3);
    }
  public:
    //  加算
    friend constexpr float3 operator +(float _Value, const float3& _float3)noexcept;
    //  減算
    friend constexpr float3 operator -(float _Value, const float3& _float3)noexcept;
    //  乗算
    friend constexpr float3 operator *(float _Value, const float3& _float3)noexcept;
    //  除算
    friend constexpr float3 operator /(float _Value, const float3& _float3)noexcept;
    //  比較
    friend constexpr bool operator ==(float _Value, const float3& _float3)noexcept;
    //  比較
    friend constexpr bool operator !=(float _Value, const float3& _float3)noexcept;
  };

  //  float3を作成
  //  _float3;コピーする値 
  inline constexpr int3::int3(const float3& _float3)noexcept
    : X(static_cast<int>(_float3.X)), Y(static_cast<int>(_float3.Y)), Z(static_cast<int>(_float3.Z))
  {

  }
  //  加算
  inline constexpr int3 operator +(int _Value, const int3& _int3)noexcept
  {
    return{ _Value + _int3.X, _Value + _int3.Y, _Value + _int3.Z };
  }
  //  減算
  inline constexpr int3 operator -(int _Value, const int3& _int3)noexcept
  {
    return{ _Value - _int3.X, _Value - _int3.Y, _Value - _int3.Z };
  }
  //  乗算
  inline constexpr int3 operator *(int _Value, const int3& _int3)noexcept
  {
    return{ _Value * _int3.X, _Value * _int3.Y, _Value * _int3.Z };
  }
  //  除算
  inline constexpr int3 operator /(int _Value, const int3& _int3)noexcept
  {
    return{ _Value / _int3.X, _Value / _int3.Y, _Value / _int3.Z };
  }
  //  比較
  inline constexpr bool operator ==(int _Value, const int3& _int3)noexcept
  {
    return (_Value == _int3.X && _Value == _int3.Y && _Value == _int3.Z);
  }
  //  比較
  inline constexpr bool operator !=(int _Value, const int3& _int3)noexcept
  {
    return !(_Value == _int3);
  }

  //  加算
  inline constexpr float3 operator +(float _Value, const float3& _float3)noexcept
  {
    return{ _Value + _float3.X, _Value + _float3.Y, _Value + _float3.Z };
  }
  //  減算
  inline constexpr float3 operator -(float _Value, const float3& _float3)noexcept
  {
    return{ _Value - _float3.X,_Value - _float3.Y, _Value - _float3.Z };
  }
  //  乗算
  inline constexpr float3 operator *(float _Value, const float3& _float3)noexcept
  {
    return{ _Value * _float3.X,_Value * _float3.Y, _Value * _float3.Z };
  }
  //  除算
  inline constexpr float3 operator /(float _Value, const float3& _float3)noexcept
  {
    return{ _Value / _float3.X,_Value / _float3.Y, _Value / _float3.Z };
  }
  //  比較
  inline constexpr bool operator ==(float _Value, const float3& _float3)noexcept
  {
    return (_Value == _float3.X && _Value == _float3.Y && _Value == _float3.Z);
  }
  //  比較
  inline constexpr bool operator !=(float _Value, const float3& _float3)noexcept
  {
    return !(_Value == _float3);
  }
}
