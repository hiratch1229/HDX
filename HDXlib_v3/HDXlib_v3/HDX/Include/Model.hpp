#pragma once
#include "Type3.hpp"
#include "Types.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"

#include <vector>

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

  //  ���[�V�������
  struct MotionData
  {
    float Frame;  //  �t���[����
    UINT Number;  //  ���[�V�����ԍ�
  };

  struct MotionBlendData : public MotionData
  {
    float BlendRate; // ��������
  public:
    MotionBlendData() = default;

    MotionBlendData(const MotionData& _MotionData, float _BlendRate)
      : BlendRate(_BlendRate)
    {
      Frame = _MotionData.Frame;
      Number = _MotionData.Number;
    }
    MotionBlendData(const MotionData& _MotionData)
    {
      Frame = _MotionData.Frame;
      Number = _MotionData.Number;
    }
    const MotionBlendData& operator=(const MotionData& _MotionData)
    {
      Frame = _MotionData.Frame;
      Number = _MotionData.Number;

      return *this;
    }
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
    void Update(float _DeltaTime, MotionData* _pMotionData)const;
    //  �`��
    void Draw(const Matrix& _WorldMatrix, const ColorF& _Color = hdx::Palette::White)const;
    //  ���[�V�����L��`��
    void Draw(const Matrix& _WorldMatrix, const MotionData& _MotionData, const ColorF& _Color = hdx::Palette::White)const;
    //  ���[�V�����u�����h�L��`��
    void Draw(const Matrix& _WorldMatrix,const std::vector<MotionBlendData>& _MotionBlendDatas, const ColorF& _Color = hdx::Palette::White)const;
  };
}
