#pragma once

struct ID3D11ShaderResourceView;
struct ID3D11Buffer;

namespace hdx
{
  struct int2;
  class RenderTarget;
}

class ITexture
{
public:
  static constexpr int kDummyTextureID = 0;
  static constexpr int kDummyTextureSize = 1;
public:
  int Load(const char* _FilePath);
  int Add(const hdx::int2& _Size);
  const hdx::int2& GetSize(int _ID);
  ID3D11ShaderResourceView** GetShaderResourceView(int _ID);
  void SetShaderResouceView(const hdx::RenderTarget& _RenderTarget, ID3D11ShaderResourceView* _pShaderResouceView);
public:
  ITexture();
public:
  void Initialize();
};
