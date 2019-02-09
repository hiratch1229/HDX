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

  virtual int Create(const char* _FilePath) = 0;

  virtual hdx::VertexShader CreateGUI(ID3D11InputLayout** _ppInputLayout) = 0;

  virtual hdx::VertexShader CreateDefault2D(ID3D11InputLayout** _ppInputLayout) = 0;

  virtual hdx::VertexShader CreateDefault3D(ID3D11InputLayout** _ppInputLayout) = 0;

  virtual ID3D11VertexShader* GetVertexShader(const hdx::VertexShader& _VertexShader) = 0;
};
