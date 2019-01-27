#pragma once
#include "IPixelShader.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>

class CPixelShader : public IPixelShader
{
  static constexpr char* kDefault2DFilePath = "DATA/Shader/SpritePS.cso";
  static constexpr char* kDefault3DFilePath = "DATA/Shader/ModelPS.cso";
private:
  NumberMap<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> PixelShaderMap_;
  ID3D11Device* pDevice_ = nullptr;
public:
  virtual void Initialize(ID3D11Device* _pDevice);

  virtual int Create(const char* _FilePath);

  virtual hdx::PixelShader CreateDefault2D();

  virtual hdx::PixelShader CreateDefault3D();

  virtual ID3D11PixelShader* GetPixeShader(const hdx::PixelShader& _PixelShader);
};
