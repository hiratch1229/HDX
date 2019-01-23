#pragma once
#include "ITexture.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>
#include <wincodec.h>
#include <string>

class CTexture : public ITexture
{
  struct TextureData
  {
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
    hdx::int2 Size;
  };
private:
  ID3D11Device* pDevice_ = nullptr;
  IDXGISwapChain* pSwapChain_ = nullptr;
  Microsoft::WRL::ComPtr<IWICImagingFactory> pFactory_;
  NumberMap<std::string, TextureData> TextureMap_;
  int CreateTextureNum_ = 0;
private:
  int CreateDummyTexture(const hdx::int2& _Size);
public:
  CTexture();

  void Initialize(ID3D11Device* _pDevice, IDXGISwapChain* _pSwapChain)override;

  int Load(const char* _FilePath)override;

  int Add(const hdx::int2& _Size)override;

  const hdx::int2& GetSize(int _ID)override;

  ID3D11ShaderResourceView** GetShaderResourceView(int _ID)override;

  void SetShaderResouceView(const hdx::RenderTarget& _RenderTarget, ID3D11ShaderResourceView* _pShaderResouceView)override;
};
