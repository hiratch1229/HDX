#pragma once
#include "Include/Model.hpp"

#include "Src/Constants.hpp"

#include <d3d11.h>
#include <wrl.h>

struct Vertex
{
  hdx::float3 Position;
  hdx::float3 Normal;
  hdx::float2 Texcoord;
  float BoneWeights[kModelBoneInfluencesMaxNum] = { 1.0f };
  int BoneIndices[kModelBoneInfluencesMaxNum] = {};
};
struct Material
{
  hdx::ColorF Color = { 0.8f,0.8f,0.8f,1.0f };
  int TextureID = -1;
};
struct Subset
{
  UINT IndexStart = 0;  //  Start number of index buffer
  UINT IndexCount = 0;  //  number of vertices(indices)
  Material Diffuse;

  bool operator<(const Subset& _Subset)const
  {
    return Diffuse.TextureID < _Subset.Diffuse.TextureID;
  }
};
struct Bone
{
  DirectX::XMFLOAT4X4 Offset;
  DirectX::XMFLOAT4X4 Pose;
};
struct BoneInfluence
{
  int Index;    //  index of bone
  float Weight; //  weight of bone
};

using BoneInfluencePerControlPoint = std::vector<BoneInfluence>;
using Skeletal = std::vector<Bone>;
using SkeletalAnimation = std::vector<Skeletal>;

struct Mesh
{
  Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
  Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
  std::vector<Subset> Subsets;
  DirectX::XMFLOAT4X4 GlobalTransform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
  std::vector<SkeletalAnimation> SkeletalAnimations;
};

struct ModelData
{
  std::vector<Mesh> Meshes;
  std::vector<hdx::float3> Vertices;
  std::vector<UINT> Indices;
  hdx::float3 Scale;
};

class IModel
{
public:
  static IModel* Create();

  IModel() = default;

  virtual ~IModel() = default;

  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual void ModelUpdate(int _ID, float _DeltaTime, hdx::MotionData* _pMotionData) = 0;

  virtual int Load(const char* _FilePath) = 0;

  virtual int Load(const hdx::Rectangle& _Rectangle) = 0;

  virtual int Load(const hdx::Cube& _Cube) = 0;

  virtual int Load(const hdx::Cylinder& _Cylinder) = 0;

  virtual int Load(const hdx::Sphere& _Sphere) = 0;

  virtual int Load(const hdx::Capsule& _Capsule) = 0;

  virtual const ModelData& GetModelData(int _ID) = 0;

  virtual const std::vector<hdx::float3>& GetVertices(int _ID) = 0;

  virtual const std::vector<UINT>& GetIndices(int _ID) = 0;

  virtual const hdx::float3& GetScale(int _ID) = 0;

  virtual float GetFrame(int _ID, int _MotionNumber) = 0;
};
