#pragma once

struct ID3D11RasterizerState;

namespace hdx
{
  class RasterizerState;
}

class IRasterizerState
{
  struct Impl;
private:
  Impl* pImpl_;
private:
  int Create(const hdx::RasterizerState& _RasterizerState);
public:
  ID3D11RasterizerState* GetRasterizerState(const hdx::RasterizerState& _RasterizerState);
public:
  IRasterizerState();
  ~IRasterizerState();
};
