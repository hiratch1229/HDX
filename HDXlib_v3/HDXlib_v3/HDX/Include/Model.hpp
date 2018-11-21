//#pragma once
//#include <d3d11.h>
//#include <wrl.h>
//#include <SimpleMath.h>
//#include <vector>
//
//#include "Color.hpp"
//#include "Type2.hpp"
//#include "Type3.hpp"
//#include "ConstantBuffer.hpp"
//
//namespace hdx
//{
//  class VertexShader;
//  class PixelShader;
//
//  class Model
//  {
//    struct Vertex3D
//    {
//      float3 Position;
//      float3 Normal;
//      float2 Texcoord;
//    };
//    struct Subset
//    {
//      std::wstring UseMtl;
//      UINT IndexStart = 0;
//      UINT IndexCount = 0;
//    };
//    struct Material
//    {
//      std::wstring NewMtl;
//      DirectX::XMFLOAT3 Ka = { 0.2f,0.2f,0.2f };
//      DirectX::XMFLOAT3 Kd = { 0.8f,0.8f,0.8f };
//      DirectX::XMFLOAT3 Ks = { 1.0f,1.0f,1.0f };
//      UINT illum = 1;
//      std::wstring map_Kd;
//      Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView_;
//    };
//  private:
//    Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;
//    Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer_;
//  private:
//    std::vector<Subset> Subsets;
//    std::vector<Material> Materials;
//    hdx::float3 Scale_;
//  private:
//    void Load(const wchar_t* FilePath, std::vector<Vertex3D>* Vertices, std::vector<UINT>* Indices, bool VCoordingFlip);
//    void CreateBuffers(Vertex3D Vertices[], int VerticesNum, UINT Indices[], int IndicesNum);
//  public:
//    hdx::float3 GetScale()const { return Scale_; }
//  public:
//    Model(const char* FilePath, bool VCoordingFlip = false);
//    ~Model();
//    //void Render(const DirectX::XMFLOAT4X4& _WorldViewProjection, const DirectX::XMFLOAT4X4& _World, const DirectX::XMFLOAT4& _LightDirection, const ColorF& _MaterialColor = { 1.0f,1.0f,1.0f,1.0f }, bool isWireFrame = false, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr)const;
//    void Render(const ConstantBuffer& _ConstantBuffer, bool isWireFrame = false, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr)const;
//  };
//}

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
