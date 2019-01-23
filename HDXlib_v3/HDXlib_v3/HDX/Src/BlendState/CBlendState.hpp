#pragma once
#include "IBlendState.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>

class CBlendState : public IBlendState
{
  NumberMap<hdx::BlendState, Microsoft::WRL::ComPtr<ID3D11BlendState>> BlendStateMap_;
  ID3D11Device* pDevice_ = nullptr;
private:
  int Create(const hdx::BlendState& _BlendState);
public:
  ID3D11BlendState* GetBlendState(const hdx::BlendState& _BlendState)override;
public:
  void Initialize(ID3D11Device* _pDevice)override;
};
