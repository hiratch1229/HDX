#pragma once
#include "IRasterizerState.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>

class CRasterizerState : public IRasterizerState
{
  NumberMap<hdx::RasterizerState, Microsoft::WRL::ComPtr<ID3D11RasterizerState>> RasterizerStateMap_;
  ID3D11Device* pDevice_ = nullptr;
  IDXGISwapChain* pSwapChain_ = nullptr;
private:
  int Create(const hdx::RasterizerState& _RasterizerState);
public:
  void Initialize(ID3D11Device* _pDevice, IDXGISwapChain* _pSwapChain)override;

  ID3D11RasterizerState* GetRasterizerState(const hdx::RasterizerState& _RasterizerState)override;
};
