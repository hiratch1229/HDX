#include "CDepthStencilState.hpp"

#include "Src/Misc.hpp"

void CDepthStecilState::Initialize(ID3D11Device* _pDevice)
{
  pDevice_ = _pDevice;
}

inline int CDepthStecilState::Create(const hdx::DepthStencilState& _DepthStencilState)
{
  D3D11_DEPTH_STENCIL_DESC DepthStencilDesc{};
  {
    DepthStencilDesc.DepthEnable = _DepthStencilState.DepthEnable_;
    DepthStencilDesc.DepthWriteMask = static_cast<D3D11_DEPTH_WRITE_MASK>(_DepthStencilState.DepthWriteMask_);
    DepthStencilDesc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(_DepthStencilState.DepthFunc_);
    DepthStencilDesc.StencilEnable = _DepthStencilState.StencilEnable_;
    DepthStencilDesc.StencilReadMask = 0xFF;
    DepthStencilDesc.StencilWriteMask = 0xFF;
    DepthStencilDesc.FrontFace.StencilFailOp = static_cast<D3D11_STENCIL_OP>(_DepthStencilState.FrontFace_.FailOp_);
    DepthStencilDesc.FrontFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(_DepthStencilState.FrontFace_.DepthFailOp_);
    DepthStencilDesc.FrontFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(_DepthStencilState.FrontFace_.PassOp_);
    DepthStencilDesc.FrontFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(_DepthStencilState.FrontFace_.Func_);
    DepthStencilDesc.BackFace.StencilFailOp = static_cast<D3D11_STENCIL_OP>(_DepthStencilState.BackFace_.FailOp_);
    DepthStencilDesc.BackFace.StencilDepthFailOp = static_cast<D3D11_STENCIL_OP>(_DepthStencilState.BackFace_.DepthFailOp_);
    DepthStencilDesc.BackFace.StencilPassOp = static_cast<D3D11_STENCIL_OP>(_DepthStencilState.BackFace_.PassOp_);
    DepthStencilDesc.BackFace.StencilFunc = static_cast<D3D11_COMPARISON_FUNC>(_DepthStencilState.BackFace_.Func_);
  }

  Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState;

  //  エラーチェック用
  HRESULT hr = S_OK;

  hr = pDevice_->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  //  マップへ追加
  return DepthStencilStateMap_.insert(_DepthStencilState, pDepthStencilState);
}

ID3D11DepthStencilState* CDepthStecilState::GetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
{
  //  既に作成されているか確認
  {
    const int ID = DepthStencilStateMap_.find(_DepthStencilState);
    if (ID >= 0)
    {
      return DepthStencilStateMap_[ID].Get();
    }
  }

  //  作成して返す
  return DepthStencilStateMap_[Create(_DepthStencilState)].Get();
}
