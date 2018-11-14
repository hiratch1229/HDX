#pragma once

struct ID3D11RasterizerState;

namespace hdx
{
  class RasterizerState;
}

class IRasterizerState
{
  int Create(const hdx::RasterizerState& _RasterizerState);
public:
  ID3D11RasterizerState* GetRasterizerState(const hdx::RasterizerState& _RasterizerState);
public:
  IRasterizerState();
};
