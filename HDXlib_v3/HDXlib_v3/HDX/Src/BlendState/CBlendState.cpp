#include "CBlendState.hpp"

#include "Src/Misc.hpp"

void CBlendState::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

int CBlendState::Create(const hdx::BlendState& _BlendState)
{
  D3D11_BLEND_DESC BlendDesc{};
  {
    BlendDesc.AlphaToCoverageEnable = _BlendState.AlphaToCoverageEnable_;
    BlendDesc.IndependentBlendEnable = false;
    BlendDesc.RenderTarget[0].BlendEnable = _BlendState.BlendEnable_;
    BlendDesc.RenderTarget[0].SrcBlend = static_cast<D3D11_BLEND>(_BlendState.SrcBlend_);
    BlendDesc.RenderTarget[0].DestBlend = static_cast<D3D11_BLEND>(_BlendState.DestBlend_);
    BlendDesc.RenderTarget[0].BlendOp = static_cast<D3D11_BLEND_OP>(_BlendState.BlendOp_);
    BlendDesc.RenderTarget[0].SrcBlendAlpha = static_cast<D3D11_BLEND>(_BlendState.SrcBlendAlpha_);
    BlendDesc.RenderTarget[0].DestBlendAlpha = static_cast<D3D11_BLEND>(_BlendState.DestBlnedAlpha_);
    BlendDesc.RenderTarget[0].BlendOpAlpha = static_cast<D3D11_BLEND_OP>(_BlendState.BlendOpAlpha_);
    BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  }

  Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = pDevice_->CreateBlendState(&BlendDesc, pBlendState.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  //  マップへ追加
  return BlendStateMap_.insert(_BlendState, pBlendState);
}

ID3D11BlendState* CBlendState::GetBlendState(const hdx::BlendState& _BlendState)
{
  //  既に作成されているか確認
  {
    const int ID = BlendStateMap_.find(_BlendState);
    if (ID >= 0)
    {
      return BlendStateMap_[ID].Get();
    }
  }

  //  作成して返す
  return BlendStateMap_[Create(_BlendState)].Get();
}
