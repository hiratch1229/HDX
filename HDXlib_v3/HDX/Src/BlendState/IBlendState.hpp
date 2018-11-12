#pragma once

struct ID3D11BlendState;

namespace hdx
{
  class BlendState;
}

class IBlendState
{
  struct Impl;
private:
  Impl* pImpl_;
private:
  int Create(const hdx::BlendState& _BlendState);
public:
  ID3D11BlendState* GetBlendState(const hdx::BlendState& _BlendState);
public:
  IBlendState();
  ~IBlendState();
};
