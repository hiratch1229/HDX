#pragma once
#include "Include/BlendState.hpp"

#include <d3d11.h>

class IBlendState
{
public:
  static IBlendState* Create();

  IBlendState() = default;

  virtual ~IBlendState() = default;

  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual ID3D11BlendState* GetBlendState(const hdx::BlendState& _BlendState) = 0;
};
