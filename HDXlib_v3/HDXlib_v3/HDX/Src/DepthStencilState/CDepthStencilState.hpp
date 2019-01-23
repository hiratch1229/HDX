#pragma once
#include "IDepthStencilState.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>

class CDepthStecilState : public IDepthStencilState
{
  NumberMap<hdx::DepthStencilState, Microsoft::WRL::ComPtr<ID3D11DepthStencilState>> DepthStencilStateMap_;
  ID3D11Device* pDevice_ = nullptr;
private:
  int Create(const hdx::DepthStencilState& _DepthStencilState);
public:
  ID3D11DepthStencilState* GetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)override;
public:
  void Initialize(ID3D11Device* _pDevice)override;
};
