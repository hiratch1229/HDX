#pragma once
#include "Include/PixelShader.hpp"

#include <d3d11.h>

class IPixelShader
{
public:
  static IPixelShader* Create();

  IPixelShader() = default;

  virtual ~IPixelShader() = default;

  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual int Create(const char* _FilePath) = 0;

  virtual hdx::PixelShader CreateGUI() = 0;

  virtual hdx::PixelShader CreateDefault2D() = 0;

  virtual hdx::PixelShader CreateDefault3D() = 0;

  virtual ID3D11PixelShader* GetPixeShader(const hdx::PixelShader& _PixelShader) = 0;
};
