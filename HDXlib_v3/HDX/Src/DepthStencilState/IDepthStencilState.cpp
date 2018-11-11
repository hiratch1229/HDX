#include "IDepthStencilState.hpp"

#include "../Engine/Engine.hpp"
#include "../System/ISystem.hpp"

#include "../../Include/DepthStencilState.hpp"
#include "../NumberMap.hpp"

#include <d3d11.h>
#include <wrl.h>

template<>
struct std::hash<hdx::DepthStencilState>
{
  hdx::DepthStencilState::DataType operator()(const hdx::DepthStencilState& _DepthStencilState)const
  {
    return _DepthStencilState.DataType_;
  }
};

namespace detail
{
  struct IDepthStencilState::Impl
  {
    NumberMap<hdx::DepthStencilState, Microsoft::WRL::ComPtr<ID3D11DepthStencilState>> DepthStencilStateMap_;
  public:
    Impl() { DepthStencilStateMap_.clear(); }
    ~Impl() { DepthStencilStateMap_.clear(); }
  };

  IDepthStencilState::IDepthStencilState()
    : pImpl_(new Impl)
  {

  }

  IDepthStencilState::~IDepthStencilState()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  int IDepthStencilState::Create(const hdx::DepthStencilState& _DepthStencilState)
  {
    //  既に作成されているか確認
    {
      const int ID = pImpl_->DepthStencilStateMap_.find(_DepthStencilState);
      if (ID >= 0)
      {
        return ID;
      }
    }

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

    HRESULT hr = GetSystem()->GetDevice()->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState");

    //  マップへ追加
    return pImpl_->DepthStencilStateMap_.insert(_DepthStencilState, pDepthStencilState);
  }

  ID3D11DepthStencilState* IDepthStencilState::GetDepthStencilState(const hdx::DepthStencilState& _DepthStencilState)
  {
    //  既に作成されているか確認
    {
      const int ID = pImpl_->DepthStencilStateMap_.find(_DepthStencilState);
      if (ID >= 0)
      {
        return pImpl_->DepthStencilStateMap_[ID].Get();
      }
    }

    //  作成して返す
    return pImpl_->DepthStencilStateMap_[Create(_DepthStencilState)].Get();
  }
}
