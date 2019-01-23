#include "CSamplerState.hpp"

#include "Src/Misc.hpp"

void CSamplerState::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

int CSamplerState::Create(const hdx::SamplerState& _SamplerState)
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

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = pDevice_->CreateSamplerState(&SamplerDesc, pSamplerState.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return SamplerStateMap_.insert(_SamplerState, pSamplerState);
}

ID3D11SamplerState** CSamplerState::GetSamplerState(const hdx::SamplerState& _SamplerState)
{
  //  既に作成されているか確認
  {
    const int ID = SamplerStateMap_.find(_SamplerState);
    if (ID >= 0)
    {
      return SamplerStateMap_[ID].GetAddressOf();
    }
  }

  //  作成して返す
  return SamplerStateMap_[Create(_SamplerState)].GetAddressOf();
}
