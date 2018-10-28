#include <HDX/BlendState/IBlendState.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>

#include <HDX/BlendState/BlendState.hpp>
#include <HDX/NumberMap.hpp>

#include <d3d11.h>
#include <wrl.h>

namespace detail
{
  class IBlendState::Impl
  {
  public:
    struct BlendStatus
    {
      bool AlphaToCoverageEnable;
      bool BlendEnable;
      hdx::Blend SrcBlend;
      hdx::Blend DestBlend;
      hdx::BlendOp BlendOp;
      hdx::Blend SrcBlendAlpha;
      hdx::Blend DestBlnedAlpha;
      hdx::BlendOp BlendOpAlpha;
    };
  public:
    NumberMap<BlendStatus, Microsoft::WRL::ComPtr<ID3D11BlendState>> BlendStatusMap_;
  public:
    Impl() { BlendStatusMap_.clear(); }
    ~Impl() { BlendStatusMap_.clear(); }
  };

  IBlendState::IBlendState()
    : pImpl_(new Impl)
  {

  }

  IBlendState::~IBlendState()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  int IBlendState::Create(bool _AlphaToCoverageEnable, bool _BlendEnable, hdx::Blend& _SrcBlend, hdx::Blend& _DestBlend, hdx::BlendOp& _BlendOp, hdx::Blend& _SrcBlendAlpha, hdx::Blend& _DestBlnedAlpha, hdx::BlendOp& _BlendOpAlpha)
  {
    const Impl::BlendStatus BlendStatus{ _AlphaToCoverageEnable, _BlendEnable, _SrcBlend, _DestBlend, _BlendOp, _SrcBlendAlpha, _DestBlnedAlpha, _BlendOpAlpha };

    //  既に作成されているか確認
    {
      const int ID = pImpl_->BlendStatusMap_.find(BlendStatus);
      if (ID >= 0)
      {
        return ID;
      }
    }

    D3D11_BLEND_DESC BlendDesc{};
    {
      BlendDesc.AlphaToCoverageEnable = BlendStatus.AlphaToCoverageEnable;
      BlendDesc.IndependentBlendEnable = false;
      BlendDesc.RenderTarget[0].BlendEnable = BlendStatus.BlendEnable;
      BlendDesc.RenderTarget[0].SrcBlend = static_cast<D3D11_BLEND>(BlendStatus.SrcBlend);
      BlendDesc.RenderTarget[0].DestBlend = static_cast<D3D11_BLEND>(BlendStatus.DestBlend);
      BlendDesc.RenderTarget[0].BlendOp = static_cast<D3D11_BLEND_OP>(BlendStatus.BlendOp);
      BlendDesc.RenderTarget[0].SrcBlendAlpha = static_cast<D3D11_BLEND>(BlendStatus.SrcBlendAlpha);
      BlendDesc.RenderTarget[0].DestBlendAlpha = static_cast<D3D11_BLEND>(BlendStatus.DestBlnedAlpha);
      BlendDesc.RenderTarget[0].BlendOpAlpha = static_cast<D3D11_BLEND_OP>(BlendStatus.BlendOpAlpha);
      BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }

    Microsoft::WRL::ComPtr<ID3D11BlendState> pBlendState;

    HRESULT hr = detail::Engine::GetSystem()->GetDevice()->CreateBlendState(&BlendDesc, pBlendState.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState");

    //  マップへ追加
    return pImpl_->BlendStatusMap_.insert(BlendStatus, pBlendState);
  }
}
