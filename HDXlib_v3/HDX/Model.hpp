#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <SimpleMath.h>
#include <vector>
#include <HDX/Color.hpp>
#include <HDX/Type2.hpp>
#include <HDX/Type3.hpp>
#include <HDX/ConstantBuffer.hpp>

namespace hdx
{
  class VertexShader;
  class PixelShader;

  class Model
  {
    struct Vertex3D
    {
      float3 Position;
      float3 Normal;
      float2 Texcoord;
    };
    struct Subset
    {
      std::wstring UseMtl;
      UINT IndexStart = 0;
      UINT IndexCount = 0;
    };
    struct Material
    {
      std::wstring NewMtl;
      DirectX::XMFLOAT3 Ka = { 0.2f,0.2f,0.2f };
      DirectX::XMFLOAT3 Kd = { 0.8f,0.8f,0.8f };
      DirectX::XMFLOAT3 Ks = { 1.0f,1.0f,1.0f };
      UINT illum = 1;
      std::wstring map_Kd;
      Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView_;
    };
  private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer_;
  private:
    std::vector<Subset> Subsets;
    std::vector<Material> Materials;
    hdx::float3 Scale_;
  private:
    void Load(const wchar_t* FilePath, std::vector<Vertex3D>* Vertices, std::vector<UINT>* Indices, bool VCoordingFlip);
    void CreateBuffers(Vertex3D Vertices[], int VerticesNum, UINT Indices[], int IndicesNum);
  public:
    hdx::float3 GetScale()const { return Scale_; }
  public:
    Model(const char* FilePath, bool VCoordingFlip = false);
    ~Model();
    //void Render(const DirectX::XMFLOAT4X4& _WorldViewProjection, const DirectX::XMFLOAT4X4& _World, const DirectX::XMFLOAT4& _LightDirection, const ColorF& _MaterialColor = { 1.0f,1.0f,1.0f,1.0f }, bool isWireFrame = false, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr)const;
    void Render(const ConstantBuffer& _ConstantBuffer, bool isWireFrame = false, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr)const;
  };
}
