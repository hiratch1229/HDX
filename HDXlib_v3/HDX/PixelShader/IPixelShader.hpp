#pragma once

struct ID3D11PixelShader;

namespace detail
{
  class IPixelShader
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    int Create(const char* _FilePath);
    ID3D11PixelShader* GetPixeShader(int _ID);
  public:
    IPixelShader();
    ~IPixelShader();
  };
}
