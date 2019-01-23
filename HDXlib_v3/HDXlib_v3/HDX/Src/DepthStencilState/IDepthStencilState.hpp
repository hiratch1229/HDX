#pragma once
#include "Include/DepthStencilState.hpp"

#include <d3d11.h>

class IDepthStencilState
{
public:
  static IDepthStencilState* Create();
  
  IDepthStencilState() = default;
  
  virtual ~IDepthStencilState() = default;
  
  virtual void Initialize(ID3D11Device* _pDevice) = 0;

  virtual ID3D11DepthStencilState* GetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState) = 0;
};
