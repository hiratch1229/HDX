#pragma once
#include "Include/PixelShader.hpp"

struct ID3D11Device;
struct ID3D11PixelShader;

class IPixelShader
{
  static constexpr char* kDefault2DFilePath = "SpritePS.cso";
  static constexpr char* kDefault3DFilePath = "ModelPS.cso";
public:
  int Create(const char* _FilePath);
  hdx::PixelShader CreateDefault2D();
  hdx::PixelShader CreateDefault3D();
public:
  ID3D11PixelShader* GetPixeShader(const hdx::PixelShader& _PixelShader);
public:
  void Initialize(ID3D11Device* _pDevice);
};
