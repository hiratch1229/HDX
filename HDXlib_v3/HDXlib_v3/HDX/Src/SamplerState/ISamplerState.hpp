#pragma once
#include "Include/SamplerState.hpp"

#include <d3d11.h>

class ISamplerState
{
public:
  static ISamplerState* Create();

  ISamplerState() = default;

  virtual ~ISamplerState() = default;

  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual ID3D11SamplerState** GetSamplerState(const hdx::SamplerState& _SamplerState) = 0;
};
