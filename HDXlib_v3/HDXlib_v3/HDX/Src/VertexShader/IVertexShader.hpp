#pragma once
#include "Include/VertexShader.hpp"
#include "Include/Types.hpp"

struct ID3D11Device;
struct ID3D11InputLayout;
struct ID3D11VertexShader;

namespace hdx
{
  class InputElementDesc;
}

class IVertexShader
{
  static constexpr char* kDefault2DFilePath = "SpriteVS.cso";
  static constexpr char* kDefault3DFilePath = "ModelVS.cso";
public:
  int Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], UINT _NumElements);
  hdx::VertexShader CreateDefault2D();
  hdx::VertexShader CreateDefault3D();
public:
  ID3D11InputLayout* GetInputLayout(const hdx::VertexShader& _VertexShader);
  ID3D11VertexShader* GetVertexShader(const hdx::VertexShader& _VertexShader);
public:
  void Initialize(ID3D11Device* _pDevice);
};
