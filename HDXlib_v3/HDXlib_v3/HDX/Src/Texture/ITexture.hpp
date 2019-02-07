#pragma once
#include "Include/Type2.hpp"
#include "Include/RenderTarget.hpp"

#include <d3d11.h>

class ITexture
{
public:
  static constexpr int kDummyTextureID = 0;
  static constexpr hdx::int2 kDummyTextureSize = hdx::int2(1, 1);
public:
  static ITexture* Create();

  ITexture() = default;

  virtual ~ITexture() = default;

  virtual void Initialize(ID3D11Device* _pDevice, IDXGISwapChain* _pSwapChain) = 0;

  virtual int Load(const char* _FilePath) = 0;

  virtual int Add(const hdx::int2& _Size) = 0;

  virtual const hdx::int2& GetSize(int _ID) = 0;

  virtual ID3D11ShaderResourceView* GetShaderResourceView(int _ID) = 0;

  virtual void SetShaderResouceView(const hdx::RenderTarget& _RenderTarget, ID3D11ShaderResourceView* _pShaderResouceView) = 0;
};
