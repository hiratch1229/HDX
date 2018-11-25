#pragma once
#include "Type3.hpp"
#include "Types.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"

//  ライブラリ
namespace hdx
{
  //  矩形
  struct Rectangle
  {
    hdx::Texture Texture;
  };
  //  立方体
  struct Cube
  {
    hdx::Texture Texture;
  };
  //  円筒
  struct Cylinder
  {
    hdx::Texture Texture;
    UINT Slices;
  };
  //  球体
  struct Sphere
  {
    hdx::Texture Texture;
    UINT Slices;
    UINT Stacks;
  };
  //  カプセル
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
    //  ファイルパスからを作成
    Model(const char* FilePath);
    //  矩形を作成
    Model(const Rectangle& _Rectangle);
    //  立方体を作成
    Model(const Cube& _Cube);
    //  円筒を作成
    Model(const Cylinder& _Cylinder);
    //  球体を作成
    Model(const Sphere& _Sphere);
    //  カプセルを作成
    Model(const Capsule& _Capsule);
    ~Model() = default;
  public:
    void Draw(const Matrix& _WorldMatrix, const ColorF& _Color = hdx::Palette::White)const;
  };
}
