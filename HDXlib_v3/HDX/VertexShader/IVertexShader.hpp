#pragma once

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
  public:
    IVertexShader();
    ~IVertexShader();
    int Create(const char* _FilePath, const hdx::InputElementDesc _InputElementDescs[], unsigned int _NumElements);
    ID3D11InputLayout* GetInputLayout(int _ID);
    ID3D11VertexShader* GetVertexShader(int _ID);
  };
}