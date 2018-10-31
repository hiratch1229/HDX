#include <HDX/System/System.hpp>

#include <HDX/Vertex.hpp>
#include <HDX/Input/Keyboard/IKeyboard.hpp>
#include <HDX/Input/Mouse/IMouse.hpp>
#include <HDX/Input/XInput/IXInput.hpp>
#include <HDX/Input/Gamepad/IGamepad.hpp>
#include <HDX/VertexShader/IVertexShader.hpp>
#include <HDX/PixelShader/IPixelShader.hpp>
#include <HDX/WIC.hpp>
#include <HDX/InputElementDesc.hpp>
#include <HDX/ConstantBuffer.hpp>
#include <HDX/Macro.hpp>

#include <HDX/System/ISystem.hpp>
#include <HDX/Engine.hpp>

#include <HDX/SkinnedMesh.hpp>

#include <time.h>
#include <direct.h>
#include <wincodec.h>
#include <ScreenGrab.h>

namespace detail
{
  //**************************************************
  //**************************************************
  //  Systemクラス
  //**************************************************
  //**************************************************

  //  初期化
  void System::Initialize()
  {
    //  Direct3Dを初期化
    InitializeD3D();

    //  ウィンドウを設定
    SetUpWindow();

    ////  Blendクラスを初期化
    //pBlender_ = std::make_unique<Blend>();

    ////  Blendをセット
    //OMSetBlendState(hdx::BlendState::Alpha);

    //  FPS管理クラスを初期化
    pFPS_ = std::make_unique<FrameRate>(60);
  }

  //  ウィンドウを設定
  void System::SetUpWindow()
  {
    //  ウィンドウ設定&表示
    SetWindowPos(hWnd_, HWND_TOP, WindowData_.LeftTopPos.X, WindowData_.LeftTopPos.Y, WindowData_.Size.X, WindowData_.Size.Y, SWP_SHOWWINDOW);

    wchar_t wWindowTitle[256];
    size_t Num;
    mbstowcs_s(&Num, wWindowTitle, WindowData_.Title, 256);

    //  ウィンドウタイトル設定
    SetWindowText(hWnd_, wWindowTitle);

    //  ウィンドウモードを設定
    pSwapChain_->SetFullscreenState(WindowData_.isFullScreen, nullptr);

    //  マウスをキャプチャー
    SetCapture(hWnd_);

    //  スワップチェーンのサイズ変更
    DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    pSwapChain_->GetDesc(&SwapChainDesc);
    pSwapChain_->ResizeBuffers(SwapChainDesc.BufferCount, WindowData_.Size.X, WindowData_.Size.Y, SwapChainDesc.BufferDesc.Format, SwapChainDesc.Flags);

    //  カーソル表示設定
    ShowCursor(WindowData_.isShowCursor);
  }

  //  ウィンドウ、デバイス、スワップチェーン作成
  void System::CreateWindowAndDeviceAndSwapChain(const HINSTANCE& _hInstane)
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    //  COM初期化
    hr = CoInitialize(nullptr);
    _ASSERT_EXPR(SUCCEEDED(hr), L"CoCreateInstance");

    //  ウィンドウ生成
    hWnd_ = CreateWindow(L"hdxlib", L"HDXlib", WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
      WindowData_.LeftTopPos.X, WindowData_.LeftTopPos.Y, WindowData_.Size.X, WindowData_.Size.Y, GetDesktopWindow(), nullptr, _hInstane, nullptr);

    //  デバイスの作成
    {
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

      for (auto i : DriverTypes)
      {
        D3D_FEATURE_LEVEL FeatureLevel;
        hr = ::D3D11CreateDevice(nullptr, DriverTypes[i], nullptr, CreateDeviceFlag, FeatureLevels,
          ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, pDevice_.GetAddressOf(), &FeatureLevel, pDeviceContext_.GetAddressOf());
        if (SUCCEEDED(hr))	break;
      }
      _ASSERT_EXPR(SUCCEEDED(hr), L"D3D11CreateDevice");
    }

    //  スワップチェーンの作成
    DXGI_SAMPLE_DESC SampleDesc{};
    {
      DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
      SwapChainDesc.BufferDesc.Width = WindowData_.Size.X;
      SwapChainDesc.BufferDesc.Height = WindowData_.Size.Y;
      SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
      SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
      SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
      SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
      SwapChainDesc.SampleDesc.Count = 1;
      SwapChainDesc.SampleDesc.Quality = 0;
      SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      SwapChainDesc.BufferCount = 1;
      SwapChainDesc.OutputWindow = hWnd_;
      SwapChainDesc.Windowed = true;
      SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
      SwapChainDesc.Flags = 0;

      //  スワップチェーン作成&ALT+ENTER無効化
      {
        Microsoft::WRL::ComPtr<IDXGIDevice> pDevice;
        pDevice_.Get()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(pDevice.GetAddressOf()));
        Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
        pDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(pAdapter.GetAddressOf()));
        Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
        pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

        hr = pFactory->CreateSwapChain(pDevice_.Get(), &SwapChainDesc, pSwapChain_.GetAddressOf());
        _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSwapChain");
        hr = pFactory->MakeWindowAssociation(hWnd_, DXGI_MWA_NO_ALT_ENTER);
        _ASSERT_EXPR(SUCCEEDED(hr), L"MakeWindowAssociation");
      }
    }

    //  キーボード初期化
    pKeyboard_ = new IKeyboard;

    //  マウス初期化
    pMouse_ = new IMouse;

    //  ゲームパッド初期化
    pGamepad_ = new IGamepad;
    pGamepad_->Initialize();

    //  XInput初期化
    pXInput_ = new IXInput;

    //  頂点シェーダー初期化
    pVertexShader_ = new IVertexShader;

    //  ピクセルシェーダー初期化
    pPixelShader_ = new IPixelShader;

    //  Windows Imaging Component初期化
    pWIC_ = new WIC;

    //  画像管理クラス初期化
    SpriteManager_.Initialize();

    //  メッシュ管理初期化
    MeshManager_.Initialize();

    //  プリミティブ管理初期化
    PrimitiveManager_.Initialize();

    //  Fbx管理初期化
    FbxManager_.Initialize();
  }

  //  Direct3Dを初期化
  void System::InitializeD3D()
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

    //  ビューポートの設定
    {
      ViewPort_.TopLeftX = 0.0f;
      ViewPort_.TopLeftY = 0.0f;
      ViewPort_.Width = static_cast<float>(WindowData_.Size.X);
      ViewPort_.Height = static_cast<float>(WindowData_.Size.Y);
      ViewPort_.MinDepth = 0.0f;
      ViewPort_.MaxDepth = 1.0f;

      pDeviceContext_->RSSetViewports(1, &ViewPort_);
    }

    pDeviceContext_->OMSetRenderTargets(1, pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
  }

  ////  バーテックスシェーダー作成
  //void System::CreateVS(const char* FileName, D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppInputLayout)
  //{
  //  //  エラーチェック用
  //  HRESULT hr = S_OK;
  //
  //  FILE* fp;
  //  fopen_s(&fp, FileName, "rb");
  //  _ASSERT_EXPR(fp, L"fopen_s");
  //
  //  fseek(fp, 0, SEEK_END);
  //  long Size = ftell(fp);
  //  fseek(fp, 0, SEEK_SET);
  //
  //  std::unique_ptr<unsigned char[]> Data = std::make_unique<unsigned char[]>(Size);
  //  fread(Data.get(), Size, 1, fp);
  //  fclose(fp);
  //
  //  //  頂点シェーダーの作成
  //  hr = pDevice_->CreateVertexShader(Data.get(), Size, nullptr, ppVertexShader);
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateVertexShader");
  //
  //  //  入力レイアウトの作成
  //  hr = pDevice_->CreateInputLayout(pInputElementDescs, NumElements, Data.get(), Size, ppInputLayout);
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateInputLayout");
  //}
  //
  ////  ピクセルシェーダー作成
  //void System::CreatePS(const char* FileName, ID3D11PixelShader** ppPixelShader)
  //{
  //  //  エラーチェック用
  //  HRESULT hr = S_OK;
  //
  //  FILE* fp;
  //  fopen_s(&fp, FileName, "rb");
  //  _ASSERT_EXPR(fp, L"fopen_s");
  //
  //  fseek(fp, 0, SEEK_END);
  //  long Size = ftell(fp);
  //  fseek(fp, 0, SEEK_SET);
  //
  //  std::unique_ptr<unsigned char[]> Data = std::make_unique<unsigned char[]>(Size);
  //  fread(Data.get(), Size, 1, fp);
  //  fclose(fp);
  //
  //  //  ピクセルシェーダーの作成
  //  hr = pDevice_->CreatePixelShader(Data.get(), Size, nullptr, ppPixelShader);
  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreatePixelShader");
  //}

  //  ダミーテクスチャ作成
  HRESULT System::MakeDummyTexture(ID3D11ShaderResourceView** ppShaderResouceView)
  {
    HRESULT hr = S_OK;

    D3D11_TEXTURE2D_DESC Texture2dDesc{};
    Texture2dDesc.Width = 1;
    Texture2dDesc.Height = 1;
    Texture2dDesc.MipLevels = 1;
    Texture2dDesc.ArraySize = 1;
    Texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    Texture2dDesc.SampleDesc.Count = 1;
    Texture2dDesc.SampleDesc.Quality = 0;
    Texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
    Texture2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    Texture2dDesc.CPUAccessFlags = 0;
    Texture2dDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA SubresourceData{};
    u_int color = 0xFFFFFFFF;
    SubresourceData.pSysMem = &color;
    SubresourceData.SysMemPitch = 4;
    SubresourceData.SysMemSlicePitch = 4;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2d;
    hr = pDevice_->CreateTexture2D(&Texture2dDesc, &SubresourceData, pTexture2d.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateTexture2D");

    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    detail::System::Get()->GetSwapChain()->GetDesc(&SwapChainDesc);
    D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc{};
    ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    ShaderResourceViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
    ShaderResourceViewDesc.Texture2D.MipLevels = 1;

    hr = pDevice_->CreateShaderResourceView(pTexture2d.Get(), &ShaderResourceViewDesc, ppShaderResouceView);
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateShaderResourceView");

    return hr;
  }

  //  メッセージプロシージャ
  LRESULT System::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    switch (msg)
    {
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_PAINT:
      ValidateRect(hWnd, NULL);
      break;
    case WM_KEYDOWN:      //  キーを押した時
      switch (wParam)
      {
      case VK_ESCAPE:
        Exit();
        break;
      case VK_F2:
        ScreenShot();
        break;
      case VK_F11:
        ChangeWindowMode();
        break;
      }
      break;
    case WM_LBUTTONDOWN:  //  マウス左ボタンを押した時
      pMouse_->ButtonPressed(MouseButtons::Left);
      break;
    case WM_LBUTTONUP:    //  マウス左ボタンを離した時
      pMouse_->ButtonReleased(MouseButtons::Left);
      break;
    case WM_RBUTTONDOWN:  //  マウス右ボタンを押した時
      pMouse_->ButtonPressed(MouseButtons::Right);
      break;
    case WM_RBUTTONUP:    //  マウス右ボタンを離した時
      pMouse_->ButtonReleased(MouseButtons::Right);
      break;
    case WM_MBUTTONDOWN:  //  マウス中ボタンを押した時
      pMouse_->ButtonPressed(MouseButtons::Middle);
      break;
    case WM_MBUTTONUP:    //  マウス中ボタンを離した時
      pMouse_->ButtonReleased(MouseButtons::Middle);
      break;
    case WM_MOUSEWHEEL:   //  マウスホイール回転
      pMouse_->SetWheel(static_cast<int>(GET_WHEEL_DELTA_WPARAM(wParam)));
      break;
    case WM_XBUTTONDOWN:  //  マウスXボタンのどちらかを押した時
      switch (GET_XBUTTON_WPARAM(wParam))
      {
      case XBUTTON1:  //  X1ボタン
        pMouse_->ButtonPressed(MouseButtons::X1);
        break;
      case XBUTTON2:  //  X2ボタン
        pMouse_->ButtonPressed(MouseButtons::X2);
        break;
      }
      break;
    case WM_XBUTTONUP:    //  マウスXボタンのどちらかを離した時
      switch (GET_XBUTTON_WPARAM(wParam))
      {
      case XBUTTON1:  //  X1ボタン
        pMouse_->ButtonReleased(MouseButtons::X1);
        break;
      case XBUTTON2:  //  X2ボタン
        pMouse_->ButtonReleased(MouseButtons::X2);
        break;
      }
      break;
    default:
      return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
  }

  void System::RenameTitle(const char* _Title)
  {
    wchar_t wWindowTitle[256];
    size_t Num;
    mbstowcs_s(&Num, wWindowTitle, WindowData_.Title = const_cast<char*>(_Title), 256);

    SetWindowText(hWnd_, wWindowTitle);
  }

  //  スクリーンショット
  void System::ScreenShot()
  {
    Microsoft::WRL::ComPtr<ID3D11Texture2D> ScreenShot;

    HRESULT hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(ScreenShot.GetAddressOf()));
    wchar_t wstr[256];

    if (SUCCEEDED(hr))
    {
      //  現在の時刻取得
      time_t now = time(nullptr);
      tm TM;
      localtime_s(&TM, &now);

      //  スクリーンショット用フォルダ作成
      _mkdir("SCREENSHOT");

      swprintf_s(wstr, L"SCREENSHOT\\%04d%02d%02d%02d%02d%02d.png", TM.tm_year + 1900, TM.tm_mon + 1, TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec);

      DirectX::SaveWICTextureToFile(pDeviceContext_.Get(), ScreenShot.Get(), GUID_ContainerFormatPng, wstr);
    }
  }

  //  ウィンドウモード変更
  void System::ChangeWindowMode()
  {
    pSwapChain_->SetFullscreenState(WindowData_.isFullScreen = !WindowData_.isFullScreen, nullptr);

    //if (WindowData_.isFullScreen = !WindowData_.isFullScreen)
    //{
    //  SetWindowLong(hWnd_, GWL_STYLE,);
    //  SetWindowPos(hWnd_, HWND_TOP,0,0,1920,1080,)
    //}
    //else
    //{
    //
    //}
  }

  //  ソフト終了時
  System::~System()
  {
    //  ウィンドウモードに戻す
    pSwapChain_->SetFullscreenState(false, nullptr);

    //  ポインタの解放
    SAFE_DELETE(pKeyboard_);
    SAFE_DELETE(pMouse_);
    SAFE_DELETE(pXInput_);
    SAFE_DELETE(pGamepad_);
    SAFE_DELETE(pVertexShader_);
    SAFE_DELETE(pPixelShader_);
    SAFE_DELETE(pWIC_);
  }

  //**************************************************
  //  Blendクラス
  //**************************************************

  ////  コンストラクタ
  //System::Blend::Blend()
  //{
  //  //  エラーチェック用
  //  HRESULT hr = S_OK;
  //
  //  //States_ = std::make_unique<Microsoft::WRL::ComPtr<ID3D11BlendState>[]>(static_cast<int>(hdx::BlendState::Num));
  //  //
  //  //D3D11_BLEND_DESC BlendStateDesc{};
  //  //
  //  ////  無効
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::None)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_NONE)");
  //  //}
  //  //
  //  ////  不透明度適応
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Alpha)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_ALPHA)");
  //  //}
  //  //
  //  ////  加算
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Add)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_ADD)");
  //  //}
  //  //
  //  ////  減算
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Subtract)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_SUBTRACT)");
  //  //}
  //  //
  //  ////  不透明度あり
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Replace)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_REPLACE)");
  //  //}
  //  //
  //  ////  乗算
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_DEST_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Multiply)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_MULTIPLY)");
  //  //}
  //  //
  //  ////  明るく
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Lighten)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_LIGHTEN)");
  //  //}
  //  //
  //  ////  暗く
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MIN;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MIN;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Draken)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_DARKEN)");
  //  //}
  //  //
  //  ////  スクリーン
  //  //{
  //  //  BlendStateDesc.AlphaToCoverageEnable = false;
  //  //  BlendStateDesc.IndependentBlendEnable = false;
  //  //  BlendStateDesc.RenderTarget[0].BlendEnable = true;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
  //  //  BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  //  //  BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
  //  //  BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  //  //  BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  //  //
  //  //  hr = detail::System::Get()->pDevice_->CreateBlendState(&BlendStateDesc, States_[static_cast<int>(hdx::BlendState::Screen)].GetAddressOf());
  //  //  _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBlendState(BS_SCREEN)");
  //  //}
  //}


  //**************************************************
  //  FPS管理クラス
  //**************************************************

  //  コンストラクタ
  System::FrameRate::FrameRate(int Maxframerate)
    : kMaxFrameRate(Maxframerate), kFrameInterval(1.0f / Maxframerate)
  {
    QueryPerformanceFrequency(&FreqTime_);
    _ASSERT_EXPR(FreqTime_.QuadPart != 0, L"QueryPerformanceFrequency");
    QueryPerformanceCounter(&LastTime_);
  }

  //  更新
  bool System::FrameRate::Update()
  {
    //  現在の時間を取得
    LARGE_INTEGER NowTime;
    QueryPerformanceCounter(&NowTime);

    //  現在のフレーム経過時間を取得
    const float FrameTime = (NowTime.QuadPart - LastTime_.QuadPart) / static_cast<float>(FreqTime_.QuadPart);

    //  経過時間が短いならfalse
    if (FrameTime < kFrameInterval) return false;

    //  データを保存
    {
      NowFPS_ = 1.0f / FrameTime;
      LastTime_ = NowTime;
    }

    return true;
  }


  //**************************************************
  //  スプライト管理クラス
  //**************************************************

  //  初期化
  HRESULT System::SpriteManager::Initialize()
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    Vertex2D Vertices[4]{};

    D3D11_BUFFER_DESC BufferDesc{};
    BufferDesc.ByteWidth = sizeof(Vertices);
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BufferDesc.MiscFlags = 0;
    BufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA InitialData{};
    InitialData.pSysMem = Vertices;
    InitialData.SysMemPitch = 0;
    InitialData.SysMemSlicePitch = 0;

    hr = System::Get()->pDevice_->CreateBuffer(&BufferDesc, &InitialData, pVertexBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    hdx::InputElementDesc InputElementDescs[] =
    {
      { "POSITION", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "COLOR", 0, hdx::Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "TEXCOORD", 0, hdx::Format::R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
    };

    VertexShaderID_ = System::Get()->GetVertexShader()->Create("SpriteVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs));
    PixelShaderID_ = System::Get()->GetPixelShader()->Create("SpritePS.cso");
    //System::Get()->CreateVS("SpriteVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs), pVertexShader_.GetAddressOf(), pInputLayout_.GetAddressOf());
    //System::Get()->CreatePS("SpritePS.cso", pPixelShader_.GetAddressOf());

    DXGI_SWAP_CHAIN_DESC SwapDesc;
    System::Get()->pSwapChain_->GetDesc(&SwapDesc);

    D3D11_RASTERIZER_DESC RasterizerDesc{};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    RasterizerDesc.CullMode = D3D11_CULL_NONE;
    RasterizerDesc.FrontCounterClockwise = false;
    RasterizerDesc.DepthBias = 0;
    RasterizerDesc.DepthBiasClamp = 0;
    RasterizerDesc.SlopeScaledDepthBias = 0;
    RasterizerDesc.DepthClipEnable = false;
    RasterizerDesc.ScissorEnable = false;
    RasterizerDesc.MultisampleEnable = (SwapDesc.SampleDesc.Count != 1) ? true : false; //  スワップチェーンのマルチサンプリング設定に合わせる
    RasterizerDesc.AntialiasedLineEnable = false;
    hr = System::Get()->pDevice_->CreateRasterizerState(&RasterizerDesc, pRasterizerState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");

    D3D11_SAMPLER_DESC SampleDesc;
    SampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SampleDesc.AddressU = SampleDesc.AddressV = SampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    SampleDesc.MipLODBias = 0;
    SampleDesc.MaxAnisotropy = 16;
    SampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    SampleDesc.BorderColor[0] = SampleDesc.BorderColor[1] = SampleDesc.BorderColor[2] = SampleDesc.BorderColor[3] = 0.0f;
    SampleDesc.MinLOD = 0;
    SampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = System::Get()->pDevice_->CreateSamplerState(&SampleDesc, pSamplerState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSamplerState");

    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
    DepthStencilDesc.DepthEnable = false;
    DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    DepthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
    DepthStencilDesc.StencilEnable = false;
    DepthStencilDesc.StencilReadMask = 0xFF;
    DepthStencilDesc.StencilWriteMask = 0xFF;
    DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    hr = System::Get()->pDevice_->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilState");

    return hr;
  }

  //  シェーダーリソースビューのIDを入手
  int System::SpriteManager::GetShaderResourceViewID(std::string FilePath)
  {
    return TextureMap_.find(FilePath);
  }

  //  シェーダーリソースビューのコンテナに格納
  int System::SpriteManager::InsertTextureDataMap(std::string FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView, const hdx::int2& _Size)
  {
    return TextureMap_.insert(FilePath, { pShaderResourceView, _Size });
  }


  //****************************************************************************************************
  //  MeshManager
  //****************************************************************************************************

  //  初期化
  HRESULT System::MeshManager::Initialize()
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    hdx::InputElementDesc InputElementDescs[] =
    {
      { "POSITION", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "NORMAL", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "TEXCOORD", 0, hdx::Format::R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
    };

    VertexShaderID_ = System::Get()->GetVertexShader()->Create("ModelVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs));
    PixelShaderID_ = System::Get()->GetPixelShader()->Create("ModelPS.cso");
    //System::Get()->CreateVS("ModelVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs), pVertexShader_.GetAddressOf(), pInputLayout_.GetAddressOf());
    //System::Get()->CreatePS("ModelPS.cso", pPixelShader_.GetAddressOf());

    DXGI_SWAP_CHAIN_DESC SwapDesc;
    System::Get()->GetSwapChain()->GetDesc(&SwapDesc);

    D3D11_RASTERIZER_DESC RasterizerDesc{};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    RasterizerDesc.CullMode = D3D11_CULL_BACK;
    RasterizerDesc.FrontCounterClockwise = false;
    RasterizerDesc.DepthBias = 0;
    RasterizerDesc.DepthBiasClamp = 0;
    RasterizerDesc.SlopeScaledDepthBias = 0;
    RasterizerDesc.DepthClipEnable = true;
    RasterizerDesc.ScissorEnable = false;
    RasterizerDesc.MultisampleEnable = (SwapDesc.SampleDesc.Count != 1) ? true : false; //  スワップチェーンのマルチサンプリング設定に合わせる
    RasterizerDesc.AntialiasedLineEnable = false;
    hr = System::Get()->GetDevice()->CreateRasterizerState(&RasterizerDesc, pSolidState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");

    RasterizerDesc.CullMode = D3D11_CULL_NONE;
    RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    hr = System::Get()->GetDevice()->CreateRasterizerState(&RasterizerDesc, pWireFrameState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");

    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
    DepthStencilDesc.DepthEnable = true;
    DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    DepthStencilDesc.StencilEnable = false;
    DepthStencilDesc.StencilReadMask = 0xFF;
    DepthStencilDesc.StencilWriteMask = 0xFF;
    DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    hr = System::Get()->GetDevice()->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilState");

    D3D11_BUFFER_DESC ConstantBufferDesc{};
    ConstantBufferDesc.ByteWidth = sizeof(hdx::ConstantBuffer);
    ConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ConstantBufferDesc.CPUAccessFlags = 0;
    ConstantBufferDesc.MiscFlags = 0;
    ConstantBufferDesc.StructureByteStride = 0;
    hr = System::Get()->GetDevice()->CreateBuffer(&ConstantBufferDesc, nullptr, pConstantBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    D3D11_SAMPLER_DESC SampleDesc;
    SampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SampleDesc.AddressU = SampleDesc.AddressV = SampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    SampleDesc.MipLODBias = 0;
    SampleDesc.MaxAnisotropy = 16;
    SampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    SampleDesc.BorderColor[0] = SampleDesc.BorderColor[1] = SampleDesc.BorderColor[2] = SampleDesc.BorderColor[3] = 0.0f;
    SampleDesc.MinLOD = 0;
    SampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = System::Get()->GetDevice()->CreateSamplerState(&SampleDesc, pSamplerState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSamplerState");

    return hr;
  }

  //  シェーダーリソースビューのIDを入手
  int System::MeshManager::GetShaderResourceViewID(std::wstring FilePath)
  {
    return ShaderResouceViewMap_.find(FilePath);
  }

  //  シェーダーリソースビューのコンテナに格納
  int System::MeshManager::InsertShaderResourceViewMap(std::wstring FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView)
  {
    return ShaderResouceViewMap_.insert(FilePath, pShaderResourceView);
  }


  //****************************************************************************************************
  //  PrimitiveManager
  //****************************************************************************************************

  //  初期化
  HRESULT System::PrimitiveManager::Initialize()
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    hdx::InputElementDesc InputElementDescs[] =
    {
      { "POSITION", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "NORMAL", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "TEXCOORD", 0, hdx::Format::R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
    };

    VertexShaderID_ = System::Get()->GetVertexShader()->Create("GeometricPrimitiveVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs));
    PixelShaderID_ = System::Get()->GetPixelShader()->Create("GeometricPrimitivePS.cso");
    //System::Get()->CreateVS("GeometricPrimitiveVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs), pVertexShader_.GetAddressOf(), pInputLayout_.GetAddressOf());
    //System::Get()->CreatePS("GeometricPrimitivePS.cso", pPixelShader_.GetAddressOf());

    DXGI_SWAP_CHAIN_DESC SwapDesc;
    System::Get()->GetSwapChain()->GetDesc(&SwapDesc);

    D3D11_RASTERIZER_DESC RasterizerDesc{};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    RasterizerDesc.CullMode = D3D11_CULL_BACK;
    RasterizerDesc.FrontCounterClockwise = false;
    RasterizerDesc.DepthBias = 0;
    RasterizerDesc.DepthBiasClamp = 0;
    RasterizerDesc.SlopeScaledDepthBias = 0;
    RasterizerDesc.DepthClipEnable = true;
    RasterizerDesc.ScissorEnable = false;
    RasterizerDesc.MultisampleEnable = (SwapDesc.SampleDesc.Count != 1) ? true : false; //  スワップチェーンのマルチサンプリング設定に合わせる
    RasterizerDesc.AntialiasedLineEnable = false;
    hr = System::Get()->GetDevice()->CreateRasterizerState(&RasterizerDesc, pSolidState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");

    RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    RasterizerDesc.CullMode = D3D11_CULL_NONE;
    hr = System::Get()->GetDevice()->CreateRasterizerState(&RasterizerDesc, pWireFrameState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");

    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
    DepthStencilDesc.DepthEnable = true;
    DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    DepthStencilDesc.StencilEnable = false;
    DepthStencilDesc.StencilReadMask = 0xFF;
    DepthStencilDesc.StencilWriteMask = 0xFF;
    DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    hr = System::Get()->GetDevice()->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilState");

    D3D11_BUFFER_DESC ConstantBufferDesc{};
    ConstantBufferDesc.ByteWidth = sizeof(hdx::ConstantBuffer);
    ConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ConstantBufferDesc.CPUAccessFlags = 0;
    ConstantBufferDesc.MiscFlags = 0;
    ConstantBufferDesc.StructureByteStride = 0;

    hr = System::Get()->GetDevice()->CreateBuffer(&ConstantBufferDesc, nullptr, pConstantBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    D3D11_SAMPLER_DESC SampleDesc;
    SampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SampleDesc.AddressU = SampleDesc.AddressV = SampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    SampleDesc.MipLODBias = 0;
    SampleDesc.MaxAnisotropy = 16;
    SampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    SampleDesc.BorderColor[0] = SampleDesc.BorderColor[1] = SampleDesc.BorderColor[2] = SampleDesc.BorderColor[3] = 0.0f;
    SampleDesc.MinLOD = 0;
    SampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = System::Get()->GetDevice()->CreateSamplerState(&SampleDesc, pSamplerState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSamplerState");

    return hr;
  }

  //  シェーダーリソースビューのIDを入手
  int System::PrimitiveManager::GetShaderResourceViewID(std::wstring FilePath)
  {
    return ShaderResouceViewMap_.find(FilePath);
  }

  //  シェーダーリソースビューのコンテナに格納
  int System::PrimitiveManager::InsertShaderResourceViewMap(std::wstring FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView)
  {
    return ShaderResouceViewMap_.insert(FilePath, pShaderResourceView);
  }


  //****************************************************************************************************
  //  FbxManager
  //****************************************************************************************************

  //  初期化
  HRESULT System::FbxManager::Initialize()
  {
    //  エラーチェック用
    HRESULT hr = S_OK;

    hdx::InputElementDesc InputElementDescs[] =
    {
      { "POSITION", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "NORMAL", 0, hdx::Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "TEXCOORD", 0, hdx::Format::R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "WEIGHTS", 0, hdx::Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
      { "BONES", 0, hdx::Format::R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, hdx::InputClassification::PER_VERTEX_DATA, 0 },
    };

    VertexShaderID_ = System::Get()->GetVertexShader()->Create("FbxVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs));
    PixelShaderID_ = System::Get()->GetPixelShader()->Create("FbxPS.cso");
    //System::Get()->CreateVS("FbxVS.cso", InputElementDescs, ARRAYSIZE(InputElementDescs), pVertexShader_.GetAddressOf(), pInputLayout_.GetAddressOf());
    //System::Get()->CreatePS("FbxPS.cso", pPixelShader_.GetAddressOf());

    DXGI_SWAP_CHAIN_DESC SwapDesc;
    System::Get()->GetSwapChain()->GetDesc(&SwapDesc);

    D3D11_RASTERIZER_DESC RasterizerDesc{};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    RasterizerDesc.CullMode = D3D11_CULL_NONE;
    RasterizerDesc.FrontCounterClockwise = false;
    RasterizerDesc.DepthBias = 0;
    RasterizerDesc.DepthBiasClamp = 0;
    RasterizerDesc.SlopeScaledDepthBias = 0;
    RasterizerDesc.DepthClipEnable = true;
    RasterizerDesc.ScissorEnable = false;
    RasterizerDesc.MultisampleEnable = (SwapDesc.SampleDesc.Count != 1) ? true : false; //  スワップチェーンのマルチサンプリング設定に合わせる
    RasterizerDesc.AntialiasedLineEnable = false;
    hr = System::Get()->GetDevice()->CreateRasterizerState(&RasterizerDesc, pSolidState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");

    RasterizerDesc.CullMode = D3D11_CULL_NONE;
    RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    hr = System::Get()->GetDevice()->CreateRasterizerState(&RasterizerDesc, pWireFrameState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateRasterizerState");

    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
    DepthStencilDesc.DepthEnable = true;
    DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    DepthStencilDesc.StencilEnable = false;
    DepthStencilDesc.StencilReadMask = 0xFF;
    DepthStencilDesc.StencilWriteMask = 0xFF;
    DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    hr = System::Get()->GetDevice()->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateDepthStencilState");

    D3D11_BUFFER_DESC ConstantBufferDesc{};
    ConstantBufferDesc.ByteWidth = sizeof(hdx::SkinnedMesh::ConstantBuffer);
    ConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ConstantBufferDesc.CPUAccessFlags = 0;
    ConstantBufferDesc.MiscFlags = 0;
    ConstantBufferDesc.StructureByteStride = 0;
    hr = System::Get()->GetDevice()->CreateBuffer(&ConstantBufferDesc, nullptr, pConstantBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateBuffer");

    D3D11_SAMPLER_DESC SampleDesc;
    SampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SampleDesc.AddressU = SampleDesc.AddressV = SampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    SampleDesc.MipLODBias = 0;
    SampleDesc.MaxAnisotropy = 16;
    SampleDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    SampleDesc.BorderColor[0] = SampleDesc.BorderColor[1] = SampleDesc.BorderColor[2] = SampleDesc.BorderColor[3] = 0.0f;
    SampleDesc.MinLOD = 0;
    SampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = System::Get()->GetDevice()->CreateSamplerState(&SampleDesc, pSamplerState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), L"CreateSamplerState");

    return hr;
  }

  //  シェーダーリソースビューのIDを入手
  int System::FbxManager::GetShaderResourceViewID(std::wstring FilePath)
  {
    return ShaderResouceViewMap_.find(FilePath);
  }

  //  シェーダーリソースビューのコンテナに格納
  int System::FbxManager::InsertShaderResourceViewMap(std::wstring FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView)
  {
    return ShaderResouceViewMap_.insert(FilePath, pShaderResourceView);
  }


  //**************************************************
  //  GPUにセットするラップ関数
  //**************************************************

  ////  ブレンドステートセット
  //void System::OMSetBlendState(hdx::BlendState _BlendState)
  //{
  //  static hdx::BlendState BlendState = hdx::BlendState::None;
  //  if (BlendState != _BlendState)
  //  {
  //    BlendState = _BlendState;
  //    pDeviceContext_.Get()->OMSetBlendState(pBlender_.get()->GetState(_BlendState), nullptr, 0xFFFFFFFF);
  //  }
  //}

  //  シェーダーリソースビューセット
  void System::PSSetShaderResources(ID3D11ShaderResourceView*const* _ppShaderResourceView)
  {
    static ID3D11ShaderResourceView*const* ppShaderResourceView = nullptr;
    if (ppShaderResourceView != _ppShaderResourceView)
    {
      ppShaderResourceView = _ppShaderResourceView;
      pDeviceContext_.Get()->PSSetShaderResources(0, 1, ppShaderResourceView);
    }
  }

  //  バーテックスバッファセット
  void System::IASetVertexBuffers(ID3D11Buffer*const* _ppVertexBuffer, UINT Strides, UINT Offsets)
  {
    static ID3D11Buffer*const* ppVertexBuffer = nullptr;
    if (ppVertexBuffer != _ppVertexBuffer)
    {
      ppVertexBuffer = _ppVertexBuffer;
      pDeviceContext_.Get()->IASetVertexBuffers(0, 1, ppVertexBuffer, &Strides, &Offsets);
    }
  }

  //  インプットレイアウトセット
  void System::IASetInputLayout(ID3D11InputLayout* _pInputLayout)
  {
    static ID3D11InputLayout* pInputLayout = nullptr;
    if (pInputLayout != _pInputLayout)
    {
      pInputLayout = _pInputLayout;
      pDeviceContext_.Get()->IASetInputLayout(pInputLayout);
    }
  }

  void System::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology)
  {
    static D3D11_PRIMITIVE_TOPOLOGY Topology;
    if (Topology != _Topology)
    {
      Topology = _Topology;
      pDeviceContext_.Get()->IASetPrimitiveTopology(Topology);
    }
  }

  //  ラスタライザーステートセット
  void System::RSSetState(ID3D11RasterizerState* _pRasterizerState)
  {
    static ID3D11RasterizerState* pRasterizerState = nullptr;
    if (pRasterizerState != _pRasterizerState)
    {
      pRasterizerState = _pRasterizerState;
      pDeviceContext_.Get()->RSSetState(pRasterizerState);
    }
  }

  //  バーテックスシェーダーセット
  void System::VSSetShader(ID3D11VertexShader* _pVertexShader)
  {
    static ID3D11VertexShader* pVertexShader = nullptr;
    if (pVertexShader != _pVertexShader)
    {
      pVertexShader = _pVertexShader;
      pDeviceContext_.Get()->VSSetShader(pVertexShader, nullptr, 0);
    }
  }

  //  ピクセルシェーダーセット
  void System::PSSetShader(ID3D11PixelShader* _pPixelShader)
  {
    static ID3D11PixelShader* pPixelShader = nullptr;
    if (pPixelShader != _pPixelShader)
    {
      pPixelShader = _pPixelShader;
      pDeviceContext_.Get()->PSSetShader(pPixelShader, nullptr, 0);
    }
  }

  //  サンプラーステートセット
  void System::PSSetSamplers(ID3D11SamplerState*const* _ppSamplerState)
  {
    static ID3D11SamplerState*const* ppSamplerState = nullptr;
    if (ppSamplerState != _ppSamplerState)
    {
      ppSamplerState = _ppSamplerState;
      pDeviceContext_.Get()->PSSetSamplers(0, 1, ppSamplerState);
    }
  }

  //  デプスステンシルステートセット
  void System::OMSetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState)
  {
    static ID3D11DepthStencilState* pDepthStencilState = nullptr;
    if (pDepthStencilState != _pDepthStencilState)
    {
      pDepthStencilState = _pDepthStencilState;
      pDeviceContext_.Get()->OMSetDepthStencilState(pDepthStencilState, 1);
    }
  }

  void System::OMSetRenderTargets(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView)
  {
    pDeviceContext_.Get()->OMSetRenderTargets(1, (_ppRenderTargetView) ? _ppRenderTargetView : pRenderTargetView_.GetAddressOf(), (_pDepthStencilView) ? _pDepthStencilView : pDepthStencilView_.Get());
  }
}

#include <HDX/System/System.hpp>

#include <HDX/Engine.hpp>
#include <HDX/System/ISystem.hpp>

namespace hdx
{
  //**************************************************
  //**************************************************
  //  Systemクラス
  //**************************************************
  //**************************************************

  //  更新
  int System::Update()
  {
    //static bool SystemInitialize = false;
    //
    ////  一回目
    //if (!SystemInitialize)
    //{
    //  SystemInitialize = true;
    //  //  初期化
    //  detail::System::Get()->Initialize();
    //}
    ////  それ以降
    //else
    //{
    //  //  描画裏表反転
    //  detail::System::Get()->Present();
    //}
    //
    ////  入力情報更新
    //{
    //  //  キーボード情報更新
    //  detail::System::Get()->GetKeyboard()->Update();
    //
    //  //  マウス情報更新
    //  detail::System::Get()->GetMouse()->Update();
    //
    //  //  XInputコントローラ情報更新
    //  detail::System::Get()->GetXInput()->Update();
    //
    //  //  コントローラ情報更新
    //  detail::System::Get()->GetGamepad()->Update();
    //}
    //
    ////  メッセージを全て処理
    //MSG Msg{};
    //while (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
    //{
    //  TranslateMessage(&Msg);
    //  DispatchMessage(&Msg);
    //}
    //
    ////  FPS制御
    //while (!detail::System::Get()->FrameRateUpdate());
    //
    ////  画面クリア
    //detail::System::Get()->ScreenClear();
    //
    ////  ウィンドウが閉じられたかどうか
    //return detail::System::Get()->isNotCloseWindow();

    return detail::Engine::GetSystem()->Update();
  }

  //  画面幅を取得
  int System::GetWindowWidth()
  {
    return  detail::Engine::GetSystem()->GetWindowWidth();
  }

  //  画面高を取得
  int System::GetWindowHeight()
  {
    return  detail::Engine::GetSystem()->GetWindowHeight();
  }

  //  画面サイズを取得
  int2 System::GetWindowSize()
  {
    return  detail::Engine::GetSystem()->GetWindowSize();
  }

  //  ウィンドウの設定
  void System::SetWindowLeftTopPos(int _LeftPos, int _TopPos)
  {
    detail::Engine::GetSystem()->SetWindowLeftTopPos({ _LeftPos, _TopPos });
  }

  //  ウィンドウの設定
  void System::SetWindowLeftTopPos(const int2& _LeftTopPos)
  {
    detail::Engine::GetSystem()->SetWindowLeftTopPos(_LeftTopPos);
  }

  //  ウィンドウの設定
  void System::SetWindowSize(int _Width, int _Height)
  {
    detail::Engine::GetSystem()->SetWindowSize({ _Width, _Height });
  }

  //  ウィンドウの設定
  void System::SetWindowSize(const int2& _Size)
  {
    detail::Engine::GetSystem()->SetWindowSize(_Size);
  }

  //  ウィンドウの設定
  void System::SetWindowMode(bool _isFullScreen)
  {
    detail::Engine::GetSystem()->SetWindowMode(_isFullScreen);
  }

  //  ウィンドウの設定
  void System::SettingWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen)
  {
    detail::Engine::GetSystem()->SetWindow({ _LeftPos, _TopPos }, { _Width, _Height }, _isFullScreen);
  }

  //  ウィンドウの設定
  void System::SettingWindow(const int2& _LeftTopPos, const int2& _Size, bool _isFullScreen)
  {
    detail::Engine::GetSystem()->SetWindow(_LeftTopPos, _Size, _isFullScreen);
  }

  //  カーソル表示設定
  void System::ShowCursor(bool _isShowCursor)
  {
    detail::Engine::GetSystem()->ShowCursor(_isShowCursor);
  }

  //  ウィンドウのタイトルを設定
  void System::SetTitle(const char* _Title)
  {
    detail::Engine::GetSystem()->SetTitle(_Title);
  }

  //  背景の色変更
  void System::SetBackColor(const ColorF& _Color)
  {
    detail::Engine::GetSystem()->SetBackColor(_Color);
  }

  //  ウィンドウのモードを変更
  void System::ChangeWindowMode()
  {
    detail::Engine::GetSystem()->ChangeWindowMode();
  }

  //  ウィンドウのタイトルを変更
  void System::RenameTitle(const char* _Title)
  {
    detail::Engine::GetSystem()->RenameTitle(_Title);
  }

  //  スクリーンショット
  void System::ScreenShot()
  {
    detail::Engine::GetSystem()->ScreenShot();
  }

  //  ソフトを終了
  void System::Exit()
  {
    detail::Engine::GetSystem()->Exit();
  }
}
