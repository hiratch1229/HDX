#include <HDX/SamplerState/ISamplerState.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>

#include <HDX/SamplerState/SamplerState.hpp>
#include <HDX/NumberMap.hpp>

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

namespace detail
{
  struct ISamplerState::Impl
  {
    NumberMap<hdx::SamplerState, Microsoft::WRL::ComPtr<ID3D11SamplerState>> SamplerStateMap_;
  public:
    Impl() { SamplerStateMap_.clear(); }
    ~Impl() { SamplerStateMap_.clear(); }
  };

  ISamplerState::ISamplerState()
    : pImpl_(new Impl)
  {

  }

  ISamplerState::~ISamplerState()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  int ISamplerState::Create(const hdx::SamplerState& _SamplerState)
  {
    //  既に作成されているか確認
    {
      const int ID = pImpl_->SamplerStateMap_.find(_SamplerState);
      if (ID >= 0)
      {
        return ID;
      }
    }

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
    HRESULT hr = GetSystem()->GetDevice()->CreateSamplerState(&SamplerDesc, pSamplerState.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSamplerState");

    return pImpl_->SamplerStateMap_.insert(_SamplerState, pSamplerState);
  }

  ID3D11SamplerState** ISamplerState::GetSamplerState(const hdx::SamplerState& _SamplerState)
  {
    //  既に作成されているか確認
    {
      const int ID = pImpl_->SamplerStateMap_.find(_SamplerState);
      if (ID >= 0)
      {
        return pImpl_->SamplerStateMap_[ID].GetAddressOf();
      }
    }

    //  作成して返す
    return pImpl_->SamplerStateMap_[Create(_SamplerState)].GetAddressOf();
  }
}
