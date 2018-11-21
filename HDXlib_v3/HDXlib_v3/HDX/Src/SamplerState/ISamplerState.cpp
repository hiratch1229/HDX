#include "ISamplerState.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../NumberMap.hpp"
#include "../Misc.hpp"

#include "../../Include/SamplerState.hpp"

#include <d3d11.h>
#include <wrl.h>

template<>
struct std::hash<hdx::SamplerState>
{
  hdx::SamplerState::DataType operator()(const hdx::SamplerState& _SamplerState)const
  {
    return _SamplerState.DataType_;
  }
};

namespace
{
  NumberMap<hdx::SamplerState, Microsoft::WRL::ComPtr<ID3D11SamplerState>> SamplerStateMap;
  ID3D11Device* pDevice = nullptr;
}

void ISamplerState::Initialize()
{
  pDevice = Engine::Get<ISystem>()->GetDevice();
}

inline int ISamplerState::Create(const hdx::SamplerState& _SamplerState)
{
  D3D11_SAMPLER_DESC SamplerDesc{};
  {
    SamplerDesc.Filter = static_cast<D3D11_FILTER>(_SamplerState.Filter_);
    SamplerDesc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(_SamplerState.AddressModeU_);
    SamplerDesc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(_SamplerState.AddressModeV_);
    SamplerDesc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(_SamplerState.AddressModeW_);
    SamplerDesc.MipLODBias = 0;
    SamplerDesc.MaxAnisotropy = _SamplerState.MaxAnisotropy_;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    SamplerDesc.BorderColor[0] = _SamplerState.BorderColorR_;
    SamplerDesc.BorderColor[1] = _SamplerState.BorderColorG_;
    SamplerDesc.BorderColor[2] = _SamplerState.BorderColorB_;
    SamplerDesc.BorderColor[3] = _SamplerState.BorderColorA_;
    SamplerDesc.MinLOD = 0;
    SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
  }

  Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState;
  HRESULT hr = pDevice->CreateSamplerState(&SamplerDesc, pSamplerState.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return SamplerStateMap.insert(_SamplerState, pSamplerState);
}

ID3D11SamplerState** ISamplerState::GetSamplerState(const hdx::SamplerState& _SamplerState)
{
  //  ä˘Ç…çÏê¨Ç≥ÇÍÇƒÇ¢ÇÈÇ©ämîF
  {
    const int ID = SamplerStateMap.find(_SamplerState);
    if (ID >= 0)
    {
      return SamplerStateMap[ID].GetAddressOf();
    }
  }

  //  çÏê¨ÇµÇƒï‘Ç∑
  return SamplerStateMap[Create(_SamplerState)].GetAddressOf();
}
