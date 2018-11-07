#pragma once

struct ID3D11DepthStencilState;

namespace hdx
{
  class DepthStencilState;
}

namespace detail
{
  class IDepthStencilState
  {
    struct Impl;
  private:
    Impl* pImpl_;
  private:
    int Create(const hdx::DepthStencilState& _DepthStencilState);
  public:
    ID3D11DepthStencilState* GetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState);
  public:
    IDepthStencilState();
    ~IDepthStencilState();
  };
}
