#pragma once
#include "ISamplerState.hpp"

#include "Src/NumberMap.hpp"

#include <wrl.h>

class CSamplerState : public ISamplerState
{
  ID3D11Device* pDevice_ = nullptr;
  NumberMap<hdx::SamplerState, Microsoft::WRL::ComPtr<ID3D11SamplerState>> SamplerStateMap_;
private:
  int Create(const hdx::SamplerState& _SamplerState);
public:
 void Initialize(ID3D11Device* _pDevice)override;

 ID3D11SamplerState** GetSamplerState(const hdx::SamplerState& _SamplerState)override;
};
