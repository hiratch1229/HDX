#pragma once
#include "../../Include/PixelShader.hpp"

struct ID3D11PixelShader;

class IPixelShader
{
  static constexpr char* kDefault2DFilePath = "SpritePS.cso";
public:
  int Create(const char* _FilePath);
  hdx::PixelShader CreateDefault2D();
public:
  ID3D11PixelShader* GetPixeShader(const hdx::PixelShader& _PixelShader);
public:
  IPixelShader() = default;
public:
  void Initialize();
};
