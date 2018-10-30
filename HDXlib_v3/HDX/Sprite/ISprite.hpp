#pragma once
#include <HDX/Type2.hpp>

struct ID3D11ShaderResourceView;
struct ID3D11Buffer;

namespace detail
{
  class ISprite
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    int GetDammyTextureID();
    int GetTextureID(const char* _FilePath);
    hdx::int2 GetSize(int _ID);
    int InsertTexture(const char* _FilePath, ID3D11ShaderResourceView* _pShaderResourceView, const hdx::int2& _Size);
    ID3D11ShaderResourceView** GetShaderResourceView(int _ID);
    ID3D11Buffer* GetVertexBuffer();
    ID3D11Buffer** GetAddressOfVertexBuffer();
  public:
    ISprite();
    ~ISprite();
  };
}
