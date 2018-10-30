#pragma once
#include <HDX/VertexShader/VertexShader.hpp>
#include <HDX/Types.hpp>

struct ID3D11InputLayout;
struct ID3D11VertexShader;

namespace hdx
{
  struct InputElementDesc;
}

namespace detail
{
  class IVertexShader
  {
    class Impl;
  private:
    Impl* pImpl_;
  private:
    static constexpr char* kDefault2DFilePath = "SpriteVS.cso";
  public:
    hdx::VertexShader CreateDefault2D();
    int Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], uint _NumElements);
    ID3D11InputLayout* GetInputLayout(const hdx::VertexShader& _VertexShader);
    ID3D11VertexShader* GetVertexShader(const hdx::VertexShader& _VertexShader);
  public:
    IVertexShader();
    ~IVertexShader();
  };
}