#pragma once
#include "../../Include/Type2.hpp"
#include "../../Include/Type3.hpp"
#include "../../Include/Types.hpp"
#include "../../Include/Color.hpp"
#include "../../Include/Constants.hpp"

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
}

struct Vertex
{
  hdx::float3 Position;
  hdx::float3 Normal;
  hdx::float2 Texcoord;
  float BoneWeights[hdx::kMaxBoneInfluences] = { 1.0f };
  int BoneIndices[hdx::kMaxBoneInfluences] = {};
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

struct SkeletalAnimation : public std::vector<Skeletal>
{
  float SamplingTime = 1 / 24.0f;
  float AnimationTick = 0.0f;
};

struct Mesh
{
  Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
  Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
  std::vector<Subset> Subsets;
  DirectX::XMFLOAT4X4 GlobalTransform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
  SkeletalAnimation SkeletalAnimation;
};

struct ModelData
{
  std::vector<Mesh> Meshes;
  std::vector<BoneInfluencePerControlPoint> BoneInfluences;
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
  void Initialize();
};
