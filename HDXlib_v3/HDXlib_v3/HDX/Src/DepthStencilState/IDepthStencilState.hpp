#pragma once

struct ID3D11Device;
struct ID3D11DepthStencilState;

namespace hdx
{
  class DepthStencilState;
}

class IDepthStencilState
{
  int Create(const hdx::DepthStencilState& _DepthStencilState);
public:
  ID3D11DepthStencilState* GetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState);
public:
  void Initialize(ID3D11Device* _pDevice);
};
