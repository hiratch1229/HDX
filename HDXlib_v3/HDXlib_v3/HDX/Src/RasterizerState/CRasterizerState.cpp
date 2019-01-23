#include "CRasterizerState.hpp"

#include "Src/Misc.hpp"

void CRasterizerState::Initialize(ID3D11Device* _pDevice, IDXGISwapChain* _pSwapChain)
{
  pDevice_ = _pDevice;
  pSwapChain_ = _pSwapChain;
}

int CRasterizerState::Create(const hdx::RasterizerState& _RasterizerState)
{
  D3D11_RASTERIZER_DESC RasterizerDesc{};
  {
    DXGI_SWAP_CHAIN_DESC SwapDesc;
    pSwapChain_->GetDesc(&SwapDesc);

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

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = pDevice_->CreateRasterizerState(&RasterizerDesc, pRasterizerState.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return RasterizerStateMap_.insert(_RasterizerState, pRasterizerState);
}

ID3D11RasterizerState* CRasterizerState::GetRasterizerState(const hdx::RasterizerState& _SamplerState)
{
  //  既に作成されているか確認
  {
    const int ID = RasterizerStateMap_.find(_SamplerState);
    if (ID >= 0)
    {
      return RasterizerStateMap_[ID].Get();
    }
  }

  //  作成して返す
  return RasterizerStateMap_[Create(_SamplerState)].Get();
}
