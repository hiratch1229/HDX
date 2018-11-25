#pragma once
#include "Type3.hpp"
#include "Types.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"

//  ���C�u����
namespace hdx
{
  //  ��`
  struct Rectangle
  {
    hdx::Texture Texture;
  };
  //  ������
  struct Cube
  {
    hdx::Texture Texture;
  };
  //  �~��
  struct Cylinder
  {
    hdx::Texture Texture;
    UINT Slices;
  };
  //  ����
  struct Sphere
  {
    hdx::Texture Texture;
    UINT Slices;
    UINT Stacks;
  };
  //  �J�v�Z��
  struct Capsule
  {
    hdx::Texture Texture;
    UINT Slieces;
    UINT Stacks;
  };

  class Model
  {
    int ID_;
    float Frame_ = 0.0f;
  public:
    int GetID()const { return ID_; }
  public:
    bool operator==(const Model& _Model)const
    {
      return ID_ == _Model.ID_;
    }
    bool operator!=(const Model& _Model)const
    {
      return !((*this) == _Model);
    }
  public:
    Model() = default;
    //  �t�@�C���p�X������쐬
    Model(const char* FilePath);
    //  ��`���쐬
    Model(const Rectangle& _Rectangle);
    //  �����̂��쐬
    Model(const Cube& _Cube);
    //  �~�����쐬
    Model(const Cylinder& _Cylinder);
    //  ���̂��쐬
    Model(const Sphere& _Sphere);
    //  �J�v�Z�����쐬
    Model(const Capsule& _Capsule);
    ~Model() = default;
  public:
    void Draw(const Matrix& _WorldMatrix, const ColorF& _Color = hdx::Palette::White)const;
  };
}
