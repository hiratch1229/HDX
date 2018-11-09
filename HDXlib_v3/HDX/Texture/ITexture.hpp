#pragma once
//#include <HDX/Type2.hpp>

struct ID3D11ShaderResourceView;
struct ID3D11Buffer;

namespace hdx
{
  struct int2;
  class RenderTarget;
}

namespace detail
{
  class ITexture
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    int GetDummyTextureID();
    int GetTextureID(const char* _FilePath);
    const hdx::int2& GetSize(int _ID);
    int InsertTexture(const char* _FilePath, ID3D11ShaderResourceView* _pShaderResourceView, const hdx::int2& _Size);
    int CreateTexture(const hdx::int2& _Size);
    ID3D11ShaderResourceView** GetShaderResourceView(int _ID);
    ID3D11Buffer* GetVertexBuffer();
    ID3D11Buffer** GetAddressOfVertexBuffer();
    void SetShaderResouceView(const hdx::RenderTarget& _RenderTarget, ID3D11ShaderResourceView* _pShaderResouceView);
  public:
    ITexture();
    ~ITexture();
  };
}
