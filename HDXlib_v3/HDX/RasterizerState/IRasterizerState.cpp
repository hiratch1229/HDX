#include <HDX/RasterizerState/IRasterizerState.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>

#include <HDX/RasterizerState/RasterizerState.hpp>
#include <HDX/NumberMap.hpp>

#include <d3d11.h>
#include <wrl.h>

template<>
struct std::hash<hdx::RasterizerState>
{
  hdx::RasterizerState::DataType operator()(const hdx::RasterizerState& _RasterizerState)const
  {
    return _RasterizerState.DataType_;
  }
};

namespace detail
{
  struct IRasterizerState::Impl
  {
    NumberMap<hdx::RasterizerState, Microsoft::WRL::ComPtr<ID3D11RasterizerState>> RasterizerStateMap_;
  public:
    Impl() { RasterizerStateMap_.clear(); }
    ~Impl() { RasterizerStateMap_.clear(); }
  };

  IRasterizerState::IRasterizerState()
    : pImpl_(new Impl)
  {

  }

  IRasterizerState::~IRasterizerState()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  int IRasterizerState::Create(const hdx::RasterizerState& _RasterizerState)
  {
    //  既に作成されているか確認
    {
      const int ID = pImpl_->RasterizerStateMap_.find(_RasterizerState);
      if (ID >= 0)
      {
        return ID;
      }
    }

    D3D11_RASTERIZER_DESC RasterizerDesc{};
    {
      DXGI_SWAP_CHAIN_DESC SwapDesc;
      detail::Engine::GetSystem()->GetSwapChain()->GetDesc(&SwapDesc);

      RasterizerDesc.FillMode = static_cast<D3D11_FILL_MODE>(_RasterizerState.FillMode_);
      RasterizerDesc.CullMode = static_cast<D3D11_CULL_MODE>(_RasterizerState.CullMode_);
      RasterizerDesc.FrontCounterClockwise = _RasterizerState.FrontCounterClockwise_;
      RasterizerDesc.DepthBias = _RasterizerState.DepthBias_;
      RasterizerDesc.DepthBiasClamp = 0.1f;
      RasterizerDesc.SlopeScaledDepthBias = 0.01f;
      RasterizerDesc.DepthClipEnable = false;
      RasterizerDesc.ScissorEnable = _RasterizerState.ScissorEnable_;
      RasterizerDesc.MultisampleEnable = (SwapDesc.SampleDesc.Count != 1) ? true : false; //  スワップチェーンのマルチサンプリング設定に合わせる
      RasterizerDesc.AntialiasedLineEnable = _RasterizerState.AntialiasedLineAnable_;
    }


    Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizerState;
    HRESULT hr = detail::Engine::GetSystem()->GetDevice()->CreateRasterizerState(&RasterizerDesc, pRasterizerState.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSamplerState");

    return pImpl_->RasterizerStateMap_.insert(_RasterizerState, pRasterizerState);
  }

  ID3D11RasterizerState* IRasterizerState::GetRasterizerState(const hdx::RasterizerState& _SamplerState)
  {
    //  既に作成されているか確認
    {
      const int ID = pImpl_->RasterizerStateMap_.find(_SamplerState);
      if (ID >= 0)
      {
        return pImpl_->RasterizerStateMap_[ID].Get();
      }
    }

    //  作成して返す
    return pImpl_->RasterizerStateMap_[Create(_SamplerState)].Get();
  }
}
