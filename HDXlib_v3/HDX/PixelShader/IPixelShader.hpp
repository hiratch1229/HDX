#pragma once
#include <HDX/PixelShader/PixelShader.hpp>

struct ID3D11PixelShader;

namespace detail
{
  class IPixelShader
  {
    class Impl;
  private:
    Impl* pImpl_;
  private:
    static constexpr char* kDefault2DFilePath = "SpritePS.cso";
  public:
    hdx::PixelShader CreateDefault2D();
    int Create(const char* _FilePath);
    ID3D11PixelShader* GetPixeShader(const hdx::PixelShader& _PixelShader);
  public:
    IPixelShader();
    ~IPixelShader();
  };
}
