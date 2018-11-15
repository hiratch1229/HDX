#pragma once
#include "../../Include/VertexShader.hpp"
#include "../../Include/Types.hpp"

struct ID3D11InputLayout;
struct ID3D11VertexShader;

namespace hdx
{
  class InputElementDesc;
}

class IVertexShader
{
  static constexpr char* kDefault2DFilePath = "SpriteVS.cso";
public:
  hdx::VertexShader CreateDefault2D();
  int Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], UINT _NumElements);
  ID3D11InputLayout* GetInputLayout(const hdx::VertexShader& _VertexShader);
  ID3D11VertexShader* GetVertexShader(const hdx::VertexShader& _VertexShader);
public:
  IVertexShader();
};
