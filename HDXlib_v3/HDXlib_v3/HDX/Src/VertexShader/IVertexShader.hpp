#pragma once
#include "Include/VertexShader.hpp"
#include "Include/Types.hpp"

#include <d3d11.h>

class IVertexShader
{
public:
  static IVertexShader* Create();

  IVertexShader() = default;

  virtual ~IVertexShader() = default;

  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual int Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], UINT _NumElements) = 0;

  virtual hdx::VertexShader CreateDefault2D() = 0;

  virtual hdx::VertexShader CreateDefault3D() = 0;

  virtual ID3D11VertexShader* GetVertexShader(const hdx::VertexShader& _VertexShader) = 0;

  virtual ID3D11InputLayout* GetInputLayout(const hdx::VertexShader& _VertexShader) = 0;
};
