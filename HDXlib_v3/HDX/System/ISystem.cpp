#include <HDX/System/ISystem.hpp>

#include <HDX/Engine.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>

#include <HDX/Type2.hpp>
#include <HDX/Color.hpp>
#include <HDX/Constants.hpp>

#include <Windows.h>
#include <d3d11.h>
#include <wincodec.h>
#include <wrl.h>

#include <time.h>
#include <direct.h>
#include <ScreenGrab.h>

#include <memory>

namespace detail
{
  class ISystem::Impl
  {
    class FrameRate
    {
      //  固定フレームレート値
      const int MaxFrameRate_;
      //  フレーム間隔
      const float FrameInterval_;
    private:
      //  現在のFPS
      float CurrentFPS_ = 0.0f;
      //  経過時間
      float DeltaTime_ = 0.0f;
      //  クロック数
      LARGE_INTEGER FreqTime_;
      //  最後の時間
      LARGE_INTEGER LastTime_;
    public:
      FrameRate(int _MaxFrameRate)
        : MaxFrameRate_(_MaxFrameRate), FrameInterval_(1.0f / _MaxFrameRate)
      {
        //  周波数を取得
        QueryPerformanceFrequency(&FreqTime_);
        _ASSERT_EXPR(FreqTime_.QuadPart != 0, L"QueryPerformanceFrequency");
        //  作成時の時間を取得
        QueryPerformanceCounter(&LastTime_);
      }
      bool Update()
      {
        //  現在の時間を取得
        LARGE_INTEGER CurrentTime;
        QueryPerformanceCounter(&CurrentTime);

        //  現在のフレーム経過時間を取得
        const float DeltaTime = (CurrentTime.QuadPart - LastTime_.QuadPart) / static_cast<float>(FreqTime_.QuadPart);

        //  経過時間が短いなら失敗
        if (DeltaTime < FrameInterval_)
        {
          return false;
        }

        CurrentFPS_ = 1.0f / DeltaTime;
        DeltaTime_ = DeltaTime;
        LastTime_ = CurrentTime;

        //  更新成功
        return true;
      }
    };
    class Window
    {
    public:
      const HWND hWnd_;
    public:
      hdx::int2 LeftTopPos_ = { 0,0 };
      hdx::int2 Size_ = { 1280,720 };
      char* Title_ = "HDXlib";
      bool isFullScreen_ = false;
      bool isShowCursor_ = false;
      hdx::ColorF BackColor_ = hdx::Palette::Black;
    public:
      //  ウィンドウを設定
      void SetUpWindow()
      {
        //  マウスをキャプチャー
        SetCapture(hWnd_);

        //  カーソル表示設定
        ::ShowCursor(isShowCursor_);

        //  ウィンドウタイトル設定
        {
          wchar_t wWindowTitle[hdx::kMaxCharLimit];
          mbstowcs_s(nullptr, wWindowTitle, Title_, hdx::kMaxCharLimit);

          SetWindowText(hWnd_, wWindowTitle);
        }

        //  ウィンドウ設定&表示
        SetWindowPos(hWnd_, HWND_TOP, LeftTopPos_.X, LeftTopPos_.Y, Size_.X, Size_.Y, SWP_SHOWWINDOW);
      }
    public:
      Window()
        : hWnd_(CreateWindow(L"HDXlib",
          L"HDXlib",
          WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
          LeftTopPos_.X,
          LeftTopPos_.Y,
          Size_.X,
          Size_.Y,
          GetDesktopWindow(),
          nullptr,
          GetModuleHandle(NULL),
          nullptr
        ))
      {
        //  エラーチェック用
        HRESULT hr = S_OK;

        //  COM初期化
        hr = CoInitialize(nullptr);
        _ASSERT_EXPR(SUCCEEDED(hr), L"CoCreateInstance");
      }
      ~Window() = default;
    };
  public:
    bool isSetUpWindow_ = false;
    std::unique_ptr<FrameRate> pFrameRate_;
    std::unique_ptr<Window> pWindow_;
  public:
    Microsoft::WRL::ComPtr<ID3D11Device> pDevice_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView_;
  public:
    void ResizeSwapChain()
    {
      DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
      pSwapChain_->GetDesc(&SwapChainDesc);
      pSwapChain_->ResizeBuffers(SwapChainDesc.BufferCount, pWindow_->Size_.X, pWindow_->Size_.Y, SwapChainDesc.BufferDesc.Format, SwapChainDesc.Flags);

      D3D11_VIEWPORT ViewPort{};
      ViewPort.TopLeftX = 0.0f;
      ViewPort.TopLeftY = 0.0f;
      ViewPort.Width = static_cast<float>(pWindow_->Size_.X);
      ViewPort.Height = static_cast<float>(pWindow_->Size_.Y);
      ViewPort.MinDepth = 0.0f;
      ViewPort.MaxDepth = 1.0f;

      pImmediateContext_->RSSetViewports(1, &ViewPort);
    }
  public:
    void CreateDevice()
    {
      //  エラーチェック用
      HRESULT hr = S_OK;

      //  デバイスフラグ
      UINT CreateDeviceFlag = 0;
#if defined( DEBUG ) || defined( _DEBUG )
      CreateDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

      D3D_DRIVER_TYPE DriverTypes[] =
      {
        D3D_DRIVER_TYPE_UNKNOWN,
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
      };

      D3D_FEATURE_LEVEL FeatureLevels[] =
      {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
      };

      const UINT FeatureLevelNum = ARRAYSIZE(FeatureLevels);
      for (auto i : DriverTypes)
      {
        D3D_FEATURE_LEVEL FeatureLevel;

        //  デバイスを作成
        hr = D3D11CreateDevice(nullptr, DriverTypes[i], nullptr, CreateDeviceFlag, FeatureLevels,
          FeatureLevelNum, D3D11_SDK_VERSION, pDevice_.GetAddressOf(), &FeatureLevel, pImmediateContext_.GetAddressOf());

        //  成功時に終了
        if (SUCCEEDED(hr))
        {
          break;
        }
      }
      _ASSERT_EXPR(SUCCEEDED(hr), L"D3D11CreateDevice");
    }
    void CreateSwapChain()
    {
      //  エラーチェック用
      HRESULT hr = S_OK;

      DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
      SwapChainDesc.BufferDesc.Width = pWindow_->Size_.X;
      SwapChainDesc.BufferDesc.Height = pWindow_->Size_.Y;
      SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
      SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
      SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
      SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
      SwapChainDesc.SampleDesc.Count = 1;
      SwapChainDesc.SampleDesc.Quality = 0;
      SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      SwapChainDesc.BufferCount = 1;
      SwapChainDesc.OutputWindow = pWindow_->hWnd_;
      SwapChainDesc.Windowed = true;
      SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
      SwapChainDesc.Flags = 0;

      //  ALT+ENTER無効にしてスワップチェーンを作成
      {
        Microsoft::WRL::ComPtr<IDXGIDevice> pDevice;
        pDevice_.Get()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(pDevice.GetAddressOf()));
        Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
        pDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(pAdapter.GetAddressOf()));
        Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
        pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

        hr = pFactory->CreateSwapChain(pDevice_.Get(), &SwapChainDesc, pSwapChain_.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSwapChain");
        hr = pFactory->MakeWindowAssociation(pWindow_->hWnd_, DXGI_MWA_NO_ALT_ENTER);
        _ASSERT_EXPR(SUCCEEDED(hr), L"MakeWindowAssociation");
      }
    }
    void CreateRenderTargetViewAndDepthStencilView()
    {
      //  エラーチェック用
      HRESULT hr = S_OK;

      //  レンダーターゲットビューの作成
      D3D11_TEXTURE2D_DESC BackBufferDesc{};
      {
        Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
        hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
        _ASSERT_EXPR(SUCCEEDED(hr), L"GetBuffer");

        hr = pDevice_->CreateRenderTargetView(pBackBuffer.Get(), nullptr, pRenderTargetView_.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRenderTargetView");

        pBackBuffer->GetDesc(&BackBufferDesc);
      }

      //  深度ステンシルビューの作成
      {
        D3D11_TEXTURE2D_DESC DepthStencilBufferDesc = BackBufferDesc;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthStencilBuffer;
        DepthStencilBufferDesc.MipLevels = 1;
        DepthStencilBufferDesc.ArraySize = 1;
        DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        DepthStencilBufferDesc.CPUAccessFlags = 0;
        DepthStencilBufferDesc.MiscFlags = 0;

        hr = pDevice_->CreateTexture2D(&DepthStencilBufferDesc, nullptr, DepthStencilBuffer.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");

        DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
        pSwapChain_->GetDesc(&SwapChainDesc);

        D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
        DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
        DepthStencilViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
        DepthStencilViewDesc.Flags = 0;
        DepthStencilViewDesc.Texture2D.MipSlice = 0;

        hr = pDevice_->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, pDepthStencilView_.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilView");
      }

      pImmediateContext_->OMSetRenderTargets(1, pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
    }
  public:
    void ScreenClear()const
    {
      //  クリア色
      const float ClearColor[4] = {
        pWindow_->BackColor_.R,
        pWindow_->BackColor_.G,
        pWindow_->BackColor_.B,
        pWindow_->BackColor_.A };

      pImmediateContext_->ClearRenderTargetView(pRenderTargetView_.Get(), ClearColor);
      pImmediateContext_->ClearDepthStencilView(pDepthStencilView_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
      pImmediateContext_->OMSetRenderTargets(1, pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
    }
    void Present()const
    {
      pSwapChain_->Present(0, 0);
    }
    void ChangeWindowMode()
    {
      pSwapChain_->SetFullscreenState(pWindow_->isFullScreen_ = !pWindow_->isFullScreen_, nullptr);
    }
    void ScreenShot()const
    {
      //  エラーチェック用
      HRESULT hr = S_OK;

      Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;

      hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBuffer.GetAddressOf()));

      //  成功時
      if (SUCCEEDED(hr))
      {
        //  現在の時刻を取得
        time_t CurrentTime = time(nullptr);

        tm TM;
        localtime_s(&TM, &CurrentTime);

        //  スクリーンショット用フォルダ作成
        _mkdir("SCREENSHOT");

        wchar_t wstr[hdx::kMaxCharLimit];
        swprintf_s(wstr, L"SCREENSHOT\\%04d%02d%02d%02d%02d%02d.png", TM.tm_year + 1900, TM.tm_mon + 1, TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec);

        DirectX::SaveWICTextureToFile(pImmediateContext_.Get(), BackBuffer.Get(), GUID_ContainerFormatPng, wstr);
      }
    }
  public:
    Impl()
    {
      //  フレームレートの作成
      pFrameRate_ = std::make_unique<FrameRate>(60);

      //  ウィンドウの作成
      pWindow_ = std::make_unique<Window>();

      //  デバイスの作成
      CreateDevice();

      //  三角リスト設定
      pImmediateContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

      //  スワップチェーンの作成
      CreateSwapChain();
    }
    ~Impl()
    {
      pSwapChain_->SetFullscreenState(false, nullptr);
    }
  };

  ISystem::ISystem()
    : pImpl_(new Impl)
  {

  }

  ISystem::~ISystem()
  {
    delete pImpl_;
    pImpl_ = nullptr;
  }

  bool ISystem::Update()
  {
    //  ウィンドウ設定
    if (!pImpl_->isSetUpWindow_)
    {
      pImpl_->isSetUpWindow_ = true;
      pImpl_->pWindow_->SetUpWindow();
      pImpl_->ResizeSwapChain();
      pImpl_->CreateRenderTargetViewAndDepthStencilView();
    }
    //  描画裏表反転
    else
    {
      pImpl_->Present();
    }
   
    Engine::GetKeyboard()->Update();
    Engine::GetMouse()->Update();
    Engine::GetXInput()->Update();
    Engine::GetGamepad()->Update();

    //  メッセージを全て処理
    MSG Msg{};
    while (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
    }

    //  FPS制御
    //  時間が来るまで無限ループ(仮)
    while (!pImpl_->pFrameRate_->Update());

    //  スクリーンを初期化
    pImpl_->ScreenClear();

    //  ウィンドウの状態を返す
    return IsWindow(pImpl_->pWindow_->hWnd_) != 0;
  }

  void ISystem::ChangeWindowMode()
  {
    pImpl_->ChangeWindowMode();
  }

  void ISystem::RenameTitle(const char* _Title)
  {
    wchar_t wWindowTitle[hdx::kMaxCharLimit];
    mbstowcs_s(nullptr, wWindowTitle, pImpl_->pWindow_->Title_ = const_cast<char*>(_Title), hdx::kMaxCharLimit);

    SetWindowText(pImpl_->pWindow_->hWnd_, wWindowTitle);
  }

  void ISystem::ScreenShot()
  {
    pImpl_->ScreenShot();
  }

  void ISystem::Exit()
  {
    PostMessage(pImpl_->pWindow_->hWnd_, WM_CLOSE, 0, 0);
  }

  int ISystem::GetWindowWidth()const
  {
    return pImpl_->pWindow_->Size_.X;
  }

  int ISystem::GetWindowHeight()const
  {
    return pImpl_->pWindow_->Size_.Y;
  }

  const hdx::int2& ISystem::GetWindowSize()const
  {
    return pImpl_->pWindow_->Size_;
  }

  void ISystem::SetWindowLeftTopPos(int _LeftPos, int _TopPos)
  {
    pImpl_->pWindow_->LeftTopPos_ = { _LeftPos, _TopPos };
  }

  void ISystem::SetWindowLeftTopPos(const hdx::int2& _LeftTopPos)
  {
    pImpl_->pWindow_->LeftTopPos_ = _LeftTopPos;
  }

  void ISystem::SetWindowSize(int _Width, int _Height)
  {
    pImpl_->pWindow_->Size_ = { _Width, _Height };
  }

  void ISystem::SetWindowSize(const hdx::int2& _Size)
  {
    pImpl_->pWindow_->Size_ = _Size;
  }

  void ISystem::SetWindowMode(bool _isFullScreen)
  {
    pImpl_->pWindow_->isFullScreen_ = _isFullScreen;
  }

  void ISystem::SetWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen)
  {
    pImpl_->pWindow_->LeftTopPos_ = { _LeftPos, _TopPos };
    pImpl_->pWindow_->Size_ = { _Width, _Height };
    pImpl_->pWindow_->isFullScreen_ = _isFullScreen;
  }

  void ISystem::SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen)
  {
    pImpl_->pWindow_->LeftTopPos_ = _LeftTopPos;
    pImpl_->pWindow_->Size_ = _Size;
    pImpl_->pWindow_->isFullScreen_ = _isFullScreen;
  }

  void ISystem::ShowCursor(bool _isShowCursor)
  {
    pImpl_->pWindow_->isShowCursor_ = _isShowCursor;

    ::ShowCursor(_isShowCursor);
  }

  void ISystem::SetTitle(const char* _Title)
  {
    pImpl_->pWindow_->Title_ = const_cast<char*>(_Title);
  }

  void ISystem::SetBackColor(const hdx::ColorF& _Color)
  {
    pImpl_->pWindow_->BackColor_ = _Color;
  }

  void ISystem::SetShaderResouceView(ID3D11ShaderResourceView** _ppShaderResourceView, int _Slot)
  {
    static ID3D11ShaderResourceView*const* ppShaderResourceView = nullptr;
    if (ppShaderResourceView != _ppShaderResourceView)
    {
      ppShaderResourceView = _ppShaderResourceView;
      //  設定を反映
      pImpl_->pImmediateContext_->PSSetShaderResources(_Slot, 1, ppShaderResourceView);
    }
  }

  void ISystem::SetBlendState(ID3D11BlendState* _pBlendState)
  {
    static ID3D11BlendState* pBlendState = nullptr;

    //  現在のと同じなら設定しない
    if (pBlendState != _pBlendState)
    {
      pBlendState = _pBlendState;
      //  設定を反映
      pImpl_->pImmediateContext_->OMSetBlendState(pBlendState, nullptr, 0xFFFFFFFF);
    }
  }

  void ISystem::SetInputLayout(ID3D11InputLayout* _pInputLayout)
  {
    static ID3D11InputLayout* pInputLayout = nullptr;
    if (pInputLayout != _pInputLayout)
    {
      pInputLayout = _pInputLayout;
      //  設定を反映
      pImpl_->pImmediateContext_->IASetInputLayout(pInputLayout);
    }
  }

  void ISystem::SetVertexShader(ID3D11VertexShader* _pVertexShader)
  {
    static ID3D11VertexShader* pVertexShader = nullptr;
    if (pVertexShader != _pVertexShader)
    {
      pVertexShader = _pVertexShader;
      //  設定を反映
      pImpl_->pImmediateContext_->VSSetShader(pVertexShader, nullptr, 0);
    }
  }

  void ISystem::SetPixelShader(ID3D11PixelShader* _pPixelShader)
  {
    static ID3D11PixelShader* pPixelShader = nullptr;
    if (pPixelShader != _pPixelShader)
    {
      pPixelShader = _pPixelShader;
      //  設定を反映
      pImpl_->pImmediateContext_->PSSetShader(pPixelShader, nullptr, 0);
    }
  }

  void ISystem::SetVertexBuffers(ID3D11Buffer*const* _ppVertexBuffer, UINT _Strides)
  {
    static ID3D11Buffer*const* ppVertexBuffer = nullptr;
    if (ppVertexBuffer != _ppVertexBuffer)
    {
      ppVertexBuffer = _ppVertexBuffer;
      UINT Offset = 0;

      //  設定を反映
      pImpl_->pImmediateContext_->IASetVertexBuffers(0, 1, ppVertexBuffer, &_Strides, &Offset);
    }
  }

  void ISystem::SetSamplersState(ID3D11SamplerState*const* _ppSamplerState)
  {
    static ID3D11SamplerState*const* ppSamplerState = nullptr;
    if (ppSamplerState != _ppSamplerState)
    {
      ppSamplerState = _ppSamplerState;
      //  設定を反映
      pImpl_->pImmediateContext_->PSSetSamplers(0, 1, ppSamplerState);
    }
  }

  void ISystem::SetRasterizerState(ID3D11RasterizerState* _pRasterizerState)
  {
    static ID3D11RasterizerState* pRasterizerState = nullptr;
    if (pRasterizerState != _pRasterizerState)
    {
      pRasterizerState = _pRasterizerState;
      //  設定を反映
      pImpl_->pImmediateContext_->RSSetState(pRasterizerState);
    }
  }

  void ISystem::SetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
  {
    static ID3D11DepthStencilState* pDepthStencilState = nullptr;
    if (pDepthStencilState != _pDepthStencilState)
    {
      pDepthStencilState = _pDepthStencilState;
      //  設定を反映
      pImpl_->pImmediateContext_->OMSetDepthStencilState(pDepthStencilState, 1);
    }
  }

  void ISystem::Map(ID3D11Buffer* _pVertexBuffer, D3D11_MAPPED_SUBRESOURCE* _pMappedSubresorce)
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    pImpl_->pImmediateContext_->Map(_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, _pMappedSubresorce);
  }

  void ISystem::Unmap(ID3D11Buffer* _pVertexBuffer)
  {
    pImpl_->pImmediateContext_->Unmap(_pVertexBuffer, 0);
  }

  ID3D11Device* ISystem::GetDevice()
  {
    return pImpl_->pDevice_.Get();
  }

  ID3D11DeviceContext* ISystem::GetImmediateContext()
  {
    return pImpl_->pImmediateContext_.Get();
  }

  IDXGISwapChain* ISystem::GetSwapChain()
  {
    return pImpl_->pSwapChain_.Get();
  }

  HWND ISystem::GetHWND()
  {
    return pImpl_->pWindow_->hWnd_;
  }
}
