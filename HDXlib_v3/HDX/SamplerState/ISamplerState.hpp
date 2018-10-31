#pragma once

struct ID3D11SamplerState;

namespace hdx
{
  class SamplerState;
}

namespace detail
{
  class ISamplerState
  {
    class Impl;
  private:
    Impl* pImpl_;
  private:
    int Create(const hdx::SamplerState& _SamplerState);
  public:
    ID3D11SamplerState** GetSamplerState(const hdx::SamplerState& _SamplerState);
  public:
    ISamplerState();
    ~ISamplerState();
  };
}
