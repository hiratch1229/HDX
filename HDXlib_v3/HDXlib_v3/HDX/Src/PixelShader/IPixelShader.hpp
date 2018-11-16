#pragma once
#include "../../Include/PixelShader.hpp"

struct ID3D11PixelShader;

class IPixelShader
{
  static constexpr char* kDefault2DFilePath = "SpritePS.cso";
public:
  hdx::PixelShader CreateDefault2D();
  int Create(const char* _FilePath);
  ID3D11PixelShader* GetPixeShader(const hdx::PixelShader& _PixelShader);
public:
  IPixelShader() = default;
};
