#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <SimpleMath.h>
#include "Type2.hpp"
#include "Type3.hpp"
#include "Color.hpp"

#include <vector>

namespace fbxsdk
{
  class FbxMesh;
  class FbxTime;
}

namespace hdx
{
  class VertexShader;
  class PixelShader;

  class SkinnedMesh
  {
    static constexpr int kMaxBoneInfluences = 4;
  private:
    struct Vertex3D
    {
      float3 Position;
      float3 Normal;
      float2 Texcoord;
      float BoneWeights[kMaxBoneInfluences] = { 1,0,0,0 };
      int BoneIndices[kMaxBoneInfluences] = {};
    };
    struct Material
    {
      ColorF Color_ = { 0.8f,0.8f,0.8f,1.0f };
      Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView_;
    };
    struct Subset
    {
      UINT IndexStart = 0;  //  Start number of index buffer
      UINT IndexCount = 0;  //  number of vertices(indices)
      Material Diffuse;
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
  private:
    using BoneInfluencePerControlPoint = std::vector<BoneInfluence>;
    using Skeletal = std::vector<Bone>;
  private:
    struct SkeletalAnimation : public std::vector<Skeletal>
    {
      float SamplingTime = 1 / 24.0f;
      float AnimationTick = 0.0f;
    };
  private:
    struct Mesh
    {
      Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
      Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
      std::vector<Subset> Subsets;
      DirectX::XMFLOAT4X4 GlobalTransform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
      //std::vector<Bone> Skeletal;
      SkeletalAnimation SkeletalAnimation;
    };
  public:
    struct ConstantBuffer
    {
      DirectX::XMFLOAT4X4 WorldViewProjection;  //  ワールド・ビュー・プロジェクション合成行列
      DirectX::XMFLOAT4X4 World;                //  ワールド変換行列
      ColorF MaterialColor;                     //  材質色
      DirectX::XMFLOAT4 LightDirection;         //  ライト進行方向

      DirectX::XMFLOAT4X4 BoneTransforms[kMaxBoneInfluences];
    };

  private:
    std::vector<Mesh> Meshes_;
    std::vector<BoneInfluencePerControlPoint> BoneInfluences_;
    DirectX::XMFLOAT4X4 CoordinateConversion = {
      1, 0, 0, 0,
      0, 0, 1, 0,
      0, 1, 0, 0,
      0, 0, 0, 1
    };
  private:
    void CreateBuffers(Vertex3D Vertices[], int VerticesNum, UINT Indices[], int IndicesNum, int Index = 0);
    void FetchBoneInfluences(const fbxsdk::FbxMesh* _pFbxMesh, std::vector<BoneInfluencePerControlPoint>* _Influences);
    void FetchBoneMatrices(const fbxsdk::FbxMesh* _pFbxMesh, std::vector<Bone>& _Skeletal, const fbxsdk::FbxTime& _Time);
    void FetchAnimations(const fbxsdk::FbxMesh* _pFbxMesh, SkeletalAnimation& SkeletalAnimation, UINT _SamplingRate = 0);
  public:
    SkinnedMesh(const char* FilePath);
    ~SkinnedMesh() {}
    void Render(const DirectX::XMFLOAT4X4& _WorldViewProjection, const DirectX::XMFLOAT4X4& _World, const DirectX::XMFLOAT4& _LightDirection, float _ElapsedTime = 0.0f, const ColorF& _MaterialColor = { 1.0f,1.0f,1.0f,1.0f }, bool isWireFrame = false, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr);
  };
}
