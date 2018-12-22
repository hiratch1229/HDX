#pragma once
#include <DirectXMath.h>

//  ���C�u����
namespace hdx
{
  struct float3;

  //  int��3�ۗL
  struct int3
  {
    int X;
    int Y;
    int Z;
  public:
    //  0�ŏ�����
    constexpr int3() : X(0), Y(0), Z(0) {}
    //  int3���쐬
    //  _XYZ:X,Y,Z
    constexpr int3(int _XYZ)noexcept : X(_XYZ), Y(_XYZ), Z(_XYZ) {}
    //  int3���쐬
    //  _X:X
    //  _Y:Y
    //  _Z:Z
    constexpr int3(int _X, int _Y, int _Z)noexcept : X(_X), Y(_Y), Z(_Z) {}
    //  int3���쐬
    //  _int3:�R�s�[����l
    constexpr int3(const int3& _int3)noexcept : X(_int3.X), Y(_int3.Y), Z(_int3.Z) {}
    //  float3���쐬
    //  _float3;�R�s�[����l 
    constexpr int3(const float3& _float3)noexcept;
  public:
    operator DirectX::XMINT3() const
    {
      return DirectX::XMINT3(X, Y, Z);
    }
  public:
    //  ���̂܂܂̒l���擾
    constexpr int3 operator +()const
    {
      return{ X, Y, Z };
    }
    //  �������]�����l���擾
    constexpr int3 operator -()const
    {
      return{ -X, -Y, -Z };
    }
  public:
    //  ���Z
    constexpr int3 operator +(const int3& _int3)const noexcept
    {
      return{ X + _int3.X, Y + _int3.Y, Z + _int3.Z };
    }
    //  ���Z
    constexpr int3 operator -(const int3& _int3)const noexcept
    {
      return{ X - _int3.X, Y - _int3.Y, Z - _int3.Z };
    }
    //  ��Z
    constexpr int3 operator *(const int3& _int3)const noexcept
    {
      return{ X * _int3.X, Y * _int3.Y, Z * _int3.Z };
    }
    //  ���Z
    constexpr int3 operator /(const int3& _int3)const noexcept
    {
      return{ X / _int3.X, Y / _int3.Y, Z / _int3.Z };
    }
    //  ���
    int3& operator =(const int3& _int3)noexcept
    {
      X = _int3.X;
      Y = _int3.Y;
      Z = _int3.Z;

      return *this;
    }
    //  ���Z����
    int3& operator +=(const int3& _int3)noexcept
    {
      X += _int3.X;
      Y += _int3.Y;
      Z += _int3.Z;

      return *this;
    }
    //  ���Z����
    int3& operator -=(const int3& _int3)noexcept
    {
      X -= _int3.X;
      Y -= _int3.Y;
      Z -= _int3.Z;

      return *this;
    }
    //  ��Z����
    int3& operator *=(const int3& _int3)noexcept
    {
      X *= _int3.X;
      Y *= _int3.Y;
      Z *= _int3.Z;

      return *this;
    }
    //  ���Z����
    int3& operator /=(const int3& _int3)noexcept
    {
      X /= _int3.X;
      Y /= _int3.Y;
      Z /= _int3.Z;

      return *this;
    }
  public:
    //  ���Z
    constexpr int3 operator +(int _Value)const noexcept
    {
      return{ X + _Value, Y + _Value, Z + _Value };
    }
    //  ���Z
    constexpr int3 operator -(int _Value)const noexcept
    {
      return{ X - _Value, Y - _Value, Z - _Value };
    }
    //  ��Z
    constexpr int3 operator *(int _Value)const noexcept
    {
      return{ X * _Value, Y * _Value, Z * _Value };;
    }
    //  ���Z
    constexpr int3 operator /(int _Value)const noexcept
    {
      return{ X / _Value, Y / _Value, Z / _Value };
    }
    //  ���
    int3& operator =(int _Value)noexcept
    {
      X = _Value;
      Y = _Value;
      Z = _Value;

      return *this;
    }
    //  ���Z����
    int3& operator +=(int _Value)noexcept
    {
      X += _Value;
      Y += _Value;
      Z += _Value;

      return *this;
    }
    //  ���Z����
    int3& operator -=(int _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;
      Z -= _Value;

      return *this;
    }
    //  ��Z����
    int3& operator *=(int _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;
      Z *= _Value;

      return *this;
    }
    //  ���Z����
    int3& operator /=(int _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;
      Z /= _Value;

      return *this;
    }
  public:
    //  ��r
    constexpr bool operator ==(const int3& _int3)const noexcept
    {
      return (X == _int3.X && Y == _int3.Y && Z == _int3.Z);
    }
    //  ��r
    constexpr bool operator !=(const int3& _int3)const noexcept
    {
      return !(*this == _int3);
    }
  public:
    //  ���Z
    friend constexpr int3 operator +(int _Value, const int3& _int3)noexcept;
    //  ���Z
    friend constexpr int3 operator -(int _Value, const int3& _int3)noexcept;
    //  ��Z
    friend constexpr int3 operator *(int _Value, const int3& _int3)noexcept;
    //  ���Z
    friend constexpr int3 operator /(int _Value, const int3& _int3)noexcept;
    //  ��r
    friend constexpr bool operator ==(int _Value, const int3& _int3)noexcept;
    //  ��r
    friend constexpr bool operator !=(int _Value, const int3& _int3)noexcept;
  };

  //  float��3�ۗL
  struct float3
  {
    float X;
    float Y;
    float Z;
  public:
    //  0�ŏ�����
    constexpr float3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    //  float3���쐬
    //  _XYZ:X,Y,Z
    constexpr float3(float _XYZ)noexcept : X(_XYZ), Y(_XYZ), Z(_XYZ) {}
    //  float3���쐬
    //  _X:X
    //  _Y:Y
    //  _Z:Z
    constexpr float3(float _X, float _Y, float _Z)noexcept : X(_X), Y(_Y), Z(_Z) {}
    //  float3���쐬
    //  _float3:�R�s�[����l
    constexpr float3(const float3& _float3)noexcept : X(_float3.X), Y(_float3.Y), Z(_float3.Z) {}
    //  float3���쐬
      //  _int3:�R�s�[����l
    constexpr float3(const int3& _int3)noexcept : X(static_cast<float>(_int3.X)), Y(static_cast<float>(_int3.Y)), Z(static_cast<float>(_int3.Z)) {}
  public:
    operator DirectX::XMFLOAT3() const
    {
      return DirectX::XMFLOAT3(X, Y, Z);
    }
  public:
    //  ���̂܂܂̒l���擾
    constexpr float3 operator +()const
    {
      return{ X, Y, Z };
    }
    //  �������]�����l���擾
    constexpr float3 operator -()const
    {
      return{ -X, -Y, -Z };
    }
  public:
    //  ���Z
    constexpr float3 operator +(const float3& _float3)const noexcept
    {
      return{ X + _float3.X, Y + _float3.Y, Z + _float3.Z };
    }
    //  ���Z
    constexpr float3 operator -(const float3& _float3)const noexcept
    {
      return{ X - _float3.X, Y - _float3.Y, Z - _float3.Z };
    }
    //  ��Z
    constexpr float3 operator *(const float3& _float3)const noexcept
    {
      return{ X * _float3.X, Y * _float3.Y, Z * _float3.Z };
    }
    //  ���Z
    constexpr float3 operator /(const float3& _float3)const noexcept
    {
      return{ X / _float3.X, Y / _float3.Y, Z / _float3.Z };
    }
    //  ���
    float3& operator =(const float3& _float3)noexcept
    {
      X = _float3.X;
      Y = _float3.Y;
      Z = _float3.Z;

      return *this;
    }
    //  ���Z����
    float3& operator +=(const float3& _float3)noexcept
    {
      X += _float3.X;
      Y += _float3.Y;
      Z += _float3.Z;

      return *this;
    }
    //  ���Z����
    float3& operator -=(const float3& _float3)noexcept
    {
      X -= _float3.X;
      Y -= _float3.Y;
      Z -= _float3.Z;

      return *this;
    }
    //  ��Z����
    float3& operator *=(const float3& _float3)noexcept
    {
      X *= _float3.X;
      Y *= _float3.Y;
      Z *= _float3.Z;

      return *this;
    }
    //  ���Z����
    float3& operator /=(const float3& _float3)noexcept
    {
      X /= _float3.X;
      Y /= _float3.Y;
      Z /= _float3.Z;

      return *this;
    }
  public:
    //  ���Z
    constexpr float3 operator +(float _Value)const noexcept
    {
      return{ X + _Value, Y + _Value, Z + _Value };
    }
    //  ���Z
    constexpr float3 operator -(float _Value)const noexcept
    {
      return{ X - _Value, Y - _Value, Z - _Value };
    }
    //  ��Z
    constexpr float3 operator *(float _Value)const noexcept
    {
      return{ X * _Value, Y * _Value, Z * _Value };;
    }
    //  ���Z
    constexpr float3 operator /(float _Value)const noexcept
    {
      return{ X / _Value, Y / _Value, Z / _Value };
    }
    //  ���
    float3& operator =(float _Value)noexcept
    {
      X = _Value;
      Y = _Value;
      Z = _Value;

      return *this;
    }
    //  ���Z����
    float3& operator +=(float _Value)noexcept
    {
      X += _Value;
      Y += _Value;
      Z += _Value;

      return *this;
    }
    //  ���Z����
    float3& operator -=(float _Value)noexcept
    {
      X -= _Value;
      Y -= _Value;
      Z -= _Value;

      return *this;
    }
    //  ��Z����
    float3& operator *=(float _Value)noexcept
    {
      X *= _Value;
      Y *= _Value;
      Z *= _Value;

      return *this;
    }
    //  ���Z����
    float3& operator /=(float _Value)noexcept
    {
      X /= _Value;
      Y /= _Value;
      Z /= _Value;

      return *this;
    }
  public:
    //  ��r
    constexpr bool operator ==(const float3& _float3)const noexcept
    {
      return (X == _float3.X && Y == _float3.Y && Z == _float3.Z);
    }
    //  ��r
    constexpr bool operator !=(const float3& _float3)const noexcept
    {
      return !(*this == _float3);
    }
  public:
    //  ���Z
    friend constexpr float3 operator +(float _Value, const float3& _float3)noexcept;
    //  ���Z
    friend constexpr float3 operator -(float _Value, const float3& _float3)noexcept;
    //  ��Z
    friend constexpr float3 operator *(float _Value, const float3& _float3)noexcept;
    //  ���Z
    friend constexpr float3 operator /(float _Value, const float3& _float3)noexcept;
    //  ��r
    friend constexpr bool operator ==(float _Value, const float3& _float3)noexcept;
    //  ��r
    friend constexpr bool operator !=(float _Value, const float3& _float3)noexcept;
  };

  //  float3���쐬
  //  _float3;�R�s�[����l 
  inline constexpr int3::int3(const float3& _float3)noexcept
    : X(static_cast<int>(_float3.X)), Y(static_cast<int>(_float3.Y)), Z(static_cast<int>(_float3.Z))
  {

  }
  //  ���Z
  inline constexpr int3 operator +(int _Value, const int3& _int3)noexcept
  {
    return{ _Value + _int3.X, _Value + _int3.Y, _Value + _int3.Z };
  }
  //  ���Z
  inline constexpr int3 operator -(int _Value, const int3& _int3)noexcept
  {
    return{ _Value - _int3.X, _Value - _int3.Y, _Value - _int3.Z };
  }
  //  ��Z
  inline constexpr int3 operator *(int _Value, const int3& _int3)noexcept
  {
    return{ _Value * _int3.X, _Value * _int3.Y, _Value * _int3.Z };
  }
  //  ���Z
  inline constexpr int3 operator /(int _Value, const int3& _int3)noexcept
  {
    return{ _Value / _int3.X, _Value / _int3.Y, _Value / _int3.Z };
  }
  //  ��r
  inline constexpr bool operator ==(int _Value, const int3& _int3)noexcept
  {
    return (_Value == _int3.X && _Value == _int3.Y && _Value == _int3.Z);
  }
  //  ��r
  inline constexpr bool operator !=(int _Value, const int3& _int3)noexcept
  {
    return !(_Value == _int3);
  }

  //  ���Z
  inline constexpr float3 operator +(float _Value, const float3& _float3)noexcept
  {
    return{ _Value + _float3.X, _Value + _float3.Y, _Value + _float3.Z };
  }
  //  ���Z
  inline constexpr float3 operator -(float _Value, const float3& _float3)noexcept
  {
    return{ _Value - _float3.X,_Value - _float3.Y, _Value - _float3.Z };
  }
  //  ��Z
  inline constexpr float3 operator *(float _Value, const float3& _float3)noexcept
  {
    return{ _Value * _float3.X,_Value * _float3.Y, _Value * _float3.Z };
  }
  //  ���Z
  inline constexpr float3 operator /(float _Value, const float3& _float3)noexcept
  {
    return{ _Value / _float3.X,_Value / _float3.Y, _Value / _float3.Z };
  }
  //  ��r
  inline constexpr bool operator ==(float _Value, const float3& _float3)noexcept
  {
    return (_Value == _float3.X && _Value == _float3.Y && _Value == _float3.Z);
  }
  //  ��r
  inline constexpr bool operator !=(float _Value, const float3& _float3)noexcept
  {
    return !(_Value == _float3);
  }
}
