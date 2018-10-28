#pragma once

struct ID3D11BlendState;

namespace hdx
{
  class BlendState;
}

namespace detail
{
  class IBlendState
  {
    class Impl;
  private:
    Impl* pImpl_;
  public:
    IBlendState();
    ~IBlendState();
  public:
    int Create(const hdx::BlendState& _BlendState);
    ID3D11BlendState* GetBlendState(const hdx::BlendState& _BlendState);
  };
}
