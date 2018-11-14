#pragma once

struct ID3D11SamplerState;

namespace hdx
{
  class SamplerState;
}

class ISamplerState
{
  int Create(const hdx::SamplerState& _SamplerState);
public:
  ID3D11SamplerState** GetSamplerState(const hdx::SamplerState& _SamplerState);
public:
  ISamplerState();
};
