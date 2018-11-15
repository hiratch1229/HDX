#include "IRasterizerState.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"
#include "../NumberMap.hpp"
#include "../Error.hpp"

#include "../../Include/RasterizerState.hpp"

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

namespace
{
  NumberMap<hdx::RasterizerState, Microsoft::WRL::ComPtr<ID3D11RasterizerState>> RasterizerStateMap;
}

IRasterizerState::IRasterizerState()
{
  RasterizerStateMap.clear();
}

int IRasterizerState::Create(const hdx::RasterizerState& _RasterizerState)
{
  //  既に作成されているか確認
  {
    const int ID = RasterizerStateMap.find(_RasterizerState);
    if (ID >= 0)
    {
      return ID;
    }
  }

  ISystem* pSystem = Engine::GetSystem();

  D3D11_RASTERIZER_DESC RasterizerDesc{};
  {
    DXGI_SWAP_CHAIN_DESC SwapDesc;
    pSystem->GetSwapChain()->GetDesc(&SwapDesc);

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
  HRESULT hr = pSystem->GetDevice()->CreateRasterizerState(&RasterizerDesc, pRasterizerState.GetAddressOf());
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  return RasterizerStateMap.insert(_RasterizerState, pRasterizerState);
}

ID3D11RasterizerState* IRasterizerState::GetRasterizerState(const hdx::RasterizerState& _SamplerState)
{
  //  既に作成されているか確認
  {
    const int ID = RasterizerStateMap.find(_SamplerState);
    if (ID >= 0)
    {
      return RasterizerStateMap[ID].Get();
    }
  }

  //  作成して返す
  return RasterizerStateMap[Create(_SamplerState)].Get();
}
