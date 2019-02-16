#pragma once
#include "IPixelShader.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>

class CPixelShader : public IPixelShader
{
  NumberMap<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> PixelShaderMap_;
  ID3D11Device* pDevice_ = nullptr;
public:
  void Initialize(ID3D11Device* _pDevice)override;

  int Create(const char* _FilePath)override;

  hdx::PixelShader CreateGUI()override;

  hdx::PixelShader CreateDefault2D()override;

  hdx::PixelShader CreateDefault3D()override;

  ID3D11PixelShader* GetPixeShader(const hdx::PixelShader& _PixelShader)override;
};
