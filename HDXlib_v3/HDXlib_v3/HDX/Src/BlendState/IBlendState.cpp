#include "IBlendState.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../Misc.hpp"

#include "../../Include/BlendState.hpp"

#include "../NumberMap.hpp"

#include <d3d11.h>
#include <wrl.h>

template<>
struct std::hash<hdx::BlendState>
{
  size_t operator()(const hdx::BlendState& _BlendState)const
  {
    return _BlendState.DataType_;
  }
};

namespace
{
  NumberMap<hdx::BlendState, Microsoft::WRL::ComPtr<ID3D11BlendState>> BlendStateMap;
}

int IBlendState::Create(const hdx::BlendState& _BlendState)
{
  //  既に作成されているか確認
  {
    const int ID = BlendStateMap.find(_BlendState);
    if (ID >= 0)
    {
      return ID;
    }
  }

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

  HRESULT hr = Engine::GetSystem()->GetDevice()->CreateBlendState(&BlendDesc, pBlendState.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  //  マップへ追加
  return BlendStateMap.insert(_BlendState, pBlendState);
}

ID3D11BlendState* IBlendState::GetBlendState(const hdx::BlendState& _BlendState)
{
  //  既に作成されているか確認
  {
    const int ID = BlendStateMap.find(_BlendState);
    if (ID >= 0)
    {
      return BlendStateMap[ID].Get();
    }
  }

  //  作成して返す
  return BlendStateMap[Create(_BlendState)].Get();
}
