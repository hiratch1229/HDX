#pragma once

struct ID3D11BlendState;

namespace hdx
{
  class BlendState;
}

class IBlendState
{
  int Create(const hdx::BlendState& _BlendState);
public:
  ID3D11BlendState* GetBlendState(const hdx::BlendState& _BlendState);
public:
  IBlendState() = default;
};
