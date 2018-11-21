#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <SimpleMath.h>

#include "Color.hpp"
#include "Type2.hpp"
#include "Type3.hpp"
#include "ConstantBuffer.hpp"

namespace hdx
{
  class VertexShader;
  class PixelShader;

  class GeometricPrimitive
  {
  protected:
    struct Vertex3D
    {
      float3 Position;
      float3 Normal;
      float2 Texcoord;
    };
  private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView_;
  protected:
    void CreateBuffers(Vertex3D Vertices[], int VerticesNum, UINT Indices[], int IndicesNum);
  public:
    GeometricPrimitive(const char* _FilePath);
    virtual ~GeometricPrimitive();
    //void Render(const DirectX::XMFLOAT4X4& _WorldViewProjection, const DirectX::XMFLOAT4X4& _World, const DirectX::XMFLOAT4& _LightDirection, const ColorF& _MaterialColor = ColorF(1.0f, 1.0f, 1.0f, 1.0f), bool isWireFrame = false, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr)const;
    //void Render(const ConstantBuffer& _ConstantBuffer, bool isWireFrame = false, const VertexShader* _pVertexShader = nullptr, const PixelShader* _pPixelShader = nullptr)const;
  };

  class Rectangle : public GeometricPrimitive
  {
  public:
    Rectangle(const char* _FilePath = "");
  };

  class Cube : public GeometricPrimitive
  {
  public:
    Cube(const char* _FilePath = "");
  };

  class Cylinder : public GeometricPrimitive
  {
  public:
    Cylinder(UINT Slices, const char* _FilePath = "");
  };

  //class Sphere : public GeometricPrimitive
  //{
  //public:
  //  Sphere(UINT Slices, UINT Stacks, const char* _FilePath = "");
  //};
  //
  //class Capsule : public GeometricPrimitive
  //{
  //public:
  //  Capsule(UINT Slices, UINT Stacks, const char* _FilePath = "");
  //};
}
