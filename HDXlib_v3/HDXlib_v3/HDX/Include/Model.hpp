#pragma once
#include "Type3.hpp"
#include "Types.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"

#include <vector>

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

  //  モーション情報
  struct MotionData
  {
    float Frame;  //  フレーム数
    UINT Number;  //  モーション番号
  public:
    MotionData(float _Frame = 0.0f, UINT _Number = 0) :Frame(_Frame), Number(_Number) {}
  };

  class Model
  {
    int ID_;
  public:
    int GetID()const { return ID_; }
  public:
    const std::vector<hdx::float3>& GetVertices()const;
    const std::vector<UINT>& GetIndices()const;
    const hdx::float3& GetScale()const;
    float GetFrame(int _MotionNumber)const;
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
    void Update(float _DeltaTime, MotionData* _pMotionData)const;
    //  描画
    void Draw(const Matrix& _WorldMatrix, const ColorF& _Color = hdx::Palette::White)const;
    //  モーション有り描画
    void Draw(const Matrix& _WorldMatrix, const MotionData& _MotionData, const ColorF& _Color = hdx::Palette::White)const;
  };
}
