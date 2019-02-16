#pragma once
#include "Include/RasterizerState.hpp"

#include <d3d11.h>

class IRasterizerState
{
public:
  static IRasterizerState* Create();

  IRasterizerState() = default;

  virtual ~IRasterizerState() = default;

  virtual void Initialize(ID3D11Device* _pDevice, IDXGISwapChain* _pSwapChain) = 0;

  virtual ID3D11RasterizerState* GetRasterizerState(const hdx::RasterizerState& _RasterizerState) = 0;
};
