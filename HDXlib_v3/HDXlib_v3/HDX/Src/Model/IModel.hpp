#pragma once
#include "Include/Type2.hpp"
#include "Include/Type3.hpp"
#include "Include/Types.hpp"
#include "Include/Color.hpp"
#include "Include/Constants.hpp"

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <vector>

namespace hdx
{
  struct Rectangle;
  struct Cube;
  struct Cylinder;
  struct Sphere;
  struct Capsule;
  struct MotionData;
}

struct Vertex
{
  hdx::float3 Position;
  hdx::float3 Normal;
  hdx::float2 Texcoord;
  float BoneWeights[hdx::Constants::MaxBoneInfluences] = { 1.0f };
  int BoneIndices[hdx::Constants::MaxBoneInfluences] = {};
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
  DirectX::XMFLOAT4X4 Transform;
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
  float SamplingTime = 1 / 24.0f;
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
  int Load(const char* _FilePath);
  int Load(const hdx::Rectangle& _Rectangle);
  int Load(const hdx::Cube& _Cube);
  int Load(const hdx::Cylinder& _Cylinder);
  int Load(const hdx::Sphere& _Sphere);
  int Load(const hdx::Capsule& _Capsule);
  const ModelData& GetModelData(int _ID);
public:
  IModel();
  ~IModel();
public:
  const std::vector<hdx::float3>& GetVertices(int _ID)const;
  const std::vector<UINT>& GetIndices(int _ID)const;
  const hdx::float3& GetScale(int _ID)const;
public:
  void Initialize(ID3D11Device* _pDevice);
  void ModelUpdate(int _ID, float _DeltaTime, hdx::MotionData* _pMotionData);
};
