#pragma once
#include <DirectXMath.h>

//  ƒ‰ƒCƒuƒ‰ƒŠ
namespace hdx
{
  struct float3;

  //  int‚ğ3‚Â•Û—L
  struct int3
  {
    int X;
    int Y;
    int Z;
  public:
    //  0‚Å‰Šú‰»
    constexpr int3() : X(0), Y(0), Z(0) {}
    //  int3‚ğì¬
    //  _XYZ:X,Y,Z
    constexpr int3(int _XYZ)noexcept : X(_XYZ), Y(_XYZ), Z(_XYZ) {}
    //  int3‚ğì¬
    //  _X:X
    //  _Y:Y
    //  _Z:Z
    constexpr int3(int _X, int _Y, int _Z)noexcept : X(_X), Y(_Y), Z(_Z) {}
    //  int3‚ğì¬
    //  _int3:ƒRƒs[‚·‚é’l
    constexpr int3(const int3& _int3)noexcept : X(_int3.X), Y(_int3.Y), Z(_int3.Z) {}
    //  float3‚ğì¬
    //  _float3;ƒRƒs[‚·‚é’l 
    constexpr int3(const float3& _float3)noexcept;
  public:
    operator DirectX::XMINT3() const
    {
      return DirectX::XMINT3(X, Y, Z);
    }
  public:
    //  ‚»‚Ì‚Ü‚Ü‚Ì’l‚ğæ“¾
    constexpr int3 operator +()const
    {
      return{ X, Y, Z };
    }
    //  •„†”½“]‚µ‚½’l‚ğæ“¾
    constexpr int3 operator -()const
    {
      return{ -X, -Y, -Z };
    }
  public:
    //  ‰ÁZ
    constexpr int3 operator +(const int3& _int3)const noexcept
    {
      return{ X + _int3.X, Y + _int3.Y, Z + _int3.Z };
    }
    //  Œ¸Z
    constexpr int3 operator -(const int3& _int3)const noexcept
    {
      return{ X - _int3.X, Y - _int3.Y, Z - _int3.Z };
    }
    //  æZ
    constexpr int3 operator *(const int3& _int3)const noexcept
    {
      return{ X * _int3.X, Y * _int3.Y, Z * _int3.Z };
    }
    //  œZ
    constexpr int3 operator /(const int3& _int3)const noexcept
    {
      return{ X / _int3.X, Y / _int3.Y, Z / _int3.Z };
    }
    //  ‘ã“ü
    int3& operator =(const int3& _int3)noexcept
    {
      X = _int3.X;
      Y = _int3.Y;
      Z = _int3.Z;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    int3& operator +=(const int3& _int3)noexcept
    {
      X += _int3.X;
      Y += _int3.Y;
      Z += _int3.Z;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    int3& operator -=(const int3& _int3)noexcept
    {
      X -= _int3.X;
      Y -= _int3.Y;
      Z -= _int3.Z;

      return *this;
    }
    //  æZŒã‘ã“ü
    int3& operator *=(const int3& _int3)noexcept
    {
      X *= _int3.X;
      Y *= _int3.Y;
      Z *= _int3.Z;

      return *this;
    }
    //  œZŒã‘ã“ü
    int3& operator /=(const int3& _int3)noexcept
    {
      X /= _int3.X;
      Y /= _int3.Y;
      Z /= _int3.Z;

      return *this;
    }
  public:
    //  ‰ÁZ
    constexpr int3 operator +(int _Value)const noexcept
    {
      return{ X + _Value, Y + _Value, Z + _Value };
    }
    //  Œ¸Z
    constexpr int3 operator -(int _Value)const noexcept
    {
      return{ X - _Value, Y - _Value, Z - _Value };
    }
    //  æZ
    constexpr int3 operator *(int _Value)const noexcept
    {
      return{ X * _Value, Y * _Value, Z * _Value };;
    }
    //  œZ
    constexpr int3 operator /(int _Value)const noexcept
    {
      return{ X / _Value, Y / _Value, Z / _Value };
    }
    //  ‘ã“ü
    int3& operator =(int _Value)noexcept
    {
      X = _Value;
      Y = _Value;
      Z = _Value;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    int3& operator +=(int _Value)noexcept
    {
      X += _Value;
      Y += _Value;
      Z += _Value;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    int3& operator -=(int _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;
      Z -= _Value;

      return *this;
    }
    //  æZŒã‘ã“ü
    int3& operator *=(int _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;
      Z *= _Value;

      return *this;
    }
    //  œZŒã‘ã“ü
    int3& operator /=(int _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;
      Z /= _Value;

      return *this;
    }
  public:
    //  ”äŠr
    constexpr bool operator ==(const int3& _int3)const noexcept
    {
      return (X == _int3.X && Y == _int3.Y && Z == _int3.Z);
    }
    //  ”äŠr
    constexpr bool operator !=(const int3& _int3)const noexcept
    {
      return !(*this == _int3);
    }
  public:
    //  ‰ÁZ
    friend constexpr int3 operator +(int _Value, const int3& _int3)noexcept;
    //  Œ¸Z
    friend constexpr int3 operator -(int _Value, const int3& _int3)noexcept;
    //  æZ
    friend constexpr int3 operator *(int _Value, const int3& _int3)noexcept;
    //  œZ
    friend constexpr int3 operator /(int _Value, const int3& _int3)noexcept;
    //  ”äŠr
    friend constexpr bool operator ==(int _Value, const int3& _int3)noexcept;
    //  ”äŠr
    friend constexpr bool operator !=(int _Value, const int3& _int3)noexcept;
  };

  //  float‚ğ3‚Â•Û—L
  struct float3
  {
    float X;
    float Y;
    float Z;
  public:
    //  0‚Å‰Šú‰»
    constexpr float3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    //  float3‚ğì¬
    //  _XYZ:X,Y,Z
    constexpr float3(float _XYZ)noexcept : X(_XYZ), Y(_XYZ), Z(_XYZ) {}
    //  float3‚ğì¬
    //  _X:X
    //  _Y:Y
    //  _Z:Z
    constexpr float3(float _X, float _Y, float _Z)noexcept : X(_X), Y(_Y), Z(_Z) {}
    //  float3‚ğì¬
    //  _float3:ƒRƒs[‚·‚é’l
    constexpr float3(const float3& _float3)noexcept : X(_float3.X), Y(_float3.Y), Z(_float3.Z) {}
    //  float3‚ğì¬
      //  _int3:ƒRƒs[‚·‚é’l
    constexpr float3(const int3& _int3)noexcept : X(static_cast<float>(_int3.X)), Y(static_cast<float>(_int3.Y)), Z(static_cast<float>(_int3.Z)) {}
  public:
    operator DirectX::XMFLOAT3() const
    {
      return DirectX::XMFLOAT3(X, Y, Z);
    }
  public:
    //  ‚»‚Ì‚Ü‚Ü‚Ì’l‚ğæ“¾
    constexpr float3 operator +()const
    {
      return{ X, Y, Z };
    }
    //  •„†”½“]‚µ‚½’l‚ğæ“¾
    constexpr float3 operator -()const
    {
      return{ -X, -Y, -Z };
    }
  public:
    //  ‰ÁZ
    constexpr float3 operator +(const float3& _float3)const noexcept
    {
      return{ X + _float3.X, Y + _float3.Y, Z + _float3.Z };
    }
    //  Œ¸Z
    constexpr float3 operator -(const float3& _float3)const noexcept
    {
      return{ X - _float3.X, Y - _float3.Y, Z - _float3.Z };
    }
    //  æZ
    constexpr float3 operator *(const float3& _float3)const noexcept
    {
      return{ X * _float3.X, Y * _float3.Y, Z * _float3.Z };
    }
    //  œZ
    constexpr float3 operator /(const float3& _float3)const noexcept
    {
      return{ X / _float3.X, Y / _float3.Y, Z / _float3.Z };
    }
    //  ‘ã“ü
    float3& operator =(const float3& _float3)noexcept
    {
      X = _float3.X;
      Y = _float3.Y;
      Z = _float3.Z;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    float3& operator +=(const float3& _float3)noexcept
    {
      X += _float3.X;
      Y += _float3.Y;
      Z += _float3.Z;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    float3& operator -=(const float3& _float3)noexcept
    {
      X -= _float3.X;
      Y -= _float3.Y;
      Z -= _float3.Z;

      return *this;
    }
    //  æZŒã‘ã“ü
    float3& operator *=(const float3& _float3)noexcept
    {
      X *= _float3.X;
      Y *= _float3.Y;
      Z *= _float3.Z;

      return *this;
    }
    //  œZŒã‘ã“ü
    float3& operator /=(const float3& _float3)noexcept
    {
      X /= _float3.X;
      Y /= _float3.Y;
      Z /= _float3.Z;

      return *this;
    }
  public:
    //  ‰ÁZ
    constexpr float3 operator +(float _Value)const noexcept
    {
      return{ X + _Value, Y + _Value, Z + _Value };
    }
    //  Œ¸Z
    constexpr float3 operator -(float _Value)const noexcept
    {
      return{ X - _Value, Y - _Value, Z - _Value };
    }
    //  æZ
    constexpr float3 operator *(float _Value)const noexcept
    {
      return{ X * _Value, Y * _Value, Z * _Value };;
    }
    //  œZ
    constexpr float3 operator /(float _Value)const noexcept
    {
      return{ X / _Value, Y / _Value, Z / _Value };
    }
    //  ‘ã“ü
    float3& operator =(float _Value)noexcept
    {
      X = _Value;
      Y = _Value;
      Z = _Value;

      return *this;
    }
    //  ‰ÁZŒã‘ã“ü
    float3& operator +=(float _Value)noexcept
    {
      X += _Value;
      Y += _Value;
      Z += _Value;

      return *this;
    }
    //  Œ¸ZŒã‘ã“ü
    float3& operator -=(float _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;
      Z -= _Value;

      return *this;
    }
    //  æZŒã‘ã“ü
    float3& operator *=(float _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;
      Z *= _Value;

      return *this;
    }
    //  œZŒã‘ã“ü
    float3& operator /=(float _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;
      Z /= _Value;

      return *this;
    }
  public:
    //  ”äŠr
    constexpr bool operator ==(const float3& _float3)const noexcept
    {
      return (X == _float3.X && Y == _float3.Y && Z == _float3.Z);
    }
    //  ”äŠr
    constexpr bool operator !=(const float3& _float3)const noexcept
    {
      return !(*this == _float3);
    }
  public:
    //  ‰ÁZ
    friend constexpr float3 operator +(float _Value, const float3& _float3)noexcept;
    //  Œ¸Z
    friend constexpr float3 operator -(float _Value, const float3& _float3)noexcept;
    //  æZ
    friend constexpr float3 operator *(float _Value, const float3& _float3)noexcept;
    //  œZ
    friend constexpr float3 operator /(float _Value, const float3& _float3)noexcept;
    //  ”äŠr
    friend constexpr bool operator ==(float _Value, const float3& _float3)noexcept;
    //  ”äŠr
    friend constexpr bool operator !=(float _Value, const float3& _float3)noexcept;
  };

  //  float3‚ğì¬
  //  _float3;ƒRƒs[‚·‚é’l 
  inline constexpr int3::int3(const float3& _float3)noexcept
    : X(static_cast<int>(_float3.X)), Y(static_cast<int>(_float3.Y)), Z(static_cast<int>(_float3.Z))
  {

  }
  //  ‰ÁZ
  inline constexpr int3 operator +(int _Value, const int3& _int3)noexcept
  {
    return{ _Value + _int3.X, _Value + _int3.Y, _Value + _int3.Z };
  }
  //  Œ¸Z
  inline constexpr int3 operator -(int _Value, const int3& _int3)noexcept
  {
    return{ _Value - _int3.X, _Value - _int3.Y, _Value - _int3.Z };
  }
  //  æZ
  inline constexpr int3 operator *(int _Value, const int3& _int3)noexcept
  {
    return{ _Value * _int3.X, _Value * _int3.Y, _Value * _int3.Z };
  }
  //  œZ
  inline constexpr int3 operator /(int _Value, const int3& _int3)noexcept
  {
    return{ _Value / _int3.X, _Value / _int3.Y, _Value / _int3.Z };
  }
  //  ”äŠr
  inline constexpr bool operator ==(int _Value, const int3& _int3)noexcept
  {
    return (_Value == _int3.X && _Value == _int3.Y && _Value == _int3.Z);
  }
  //  ”äŠr
  inline constexpr bool operator !=(int _Value, const int3& _int3)noexcept
  {
    return !(_Value == _int3);
  }

  //  ‰ÁZ
  inline constexpr float3 operator +(float _Value, const float3& _float3)noexcept
  {
    return{ _Value + _float3.X, _Value + _float3.Y, _Value + _float3.Z };
  }
  //  Œ¸Z
  inline constexpr float3 operator -(float _Value, const float3& _float3)noexcept
  {
    return{ _Value - _float3.X,_Value - _float3.Y, _Value - _float3.Z };
  }
  //  æZ
  inline constexpr float3 operator *(float _Value, const float3& _float3)noexcept
  {
    return{ _Value * _float3.X,_Value * _float3.Y, _Value * _float3.Z };
  }
  //  œZ
  inline constexpr float3 operator /(float _Value, const float3& _float3)noexcept
  {
    return{ _Value / _float3.X,_Value / _float3.Y, _Value / _float3.Z };
  }
  //  ”äŠr
  inline constexpr bool operator ==(float _Value, const float3& _float3)noexcept
  {
    return (_Value == _float3.X && _Value == _float3.Y && _Value == _float3.Z);
  }
  //  ”äŠr
  inline constexpr bool operator !=(float _Value, const float3& _float3)noexcept
  {
    return !(_Value == _float3);
  }
}
