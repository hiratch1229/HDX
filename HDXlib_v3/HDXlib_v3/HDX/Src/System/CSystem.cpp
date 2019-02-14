#include "CSystem.hpp"

#include "Src/Engine.hpp"
#include "Src/Misc.hpp"
#include "Src/Constants.hpp"

#include "Src/BlendState/IBlendState.hpp"
#include "Src/ConstantBuffer/IConstantBuffer.hpp"
#include "Src/DepthStencilState/IDepthStencilState.hpp"
#include "Src/RasterizerState/IRasterizerState.hpp"
#include "Src/RenderTarget/IRenderTarget.hpp"
#include "Src/SamplerState/ISamplerState.hpp"
#include "Src/VertexShader/IVertexShader.hpp"
#include "Src/PixelShader/IPixelShader.hpp"
#include "Src/Renderer/Renderer2D/IRenderer2D.hpp"
#include "Src/Renderer/Renderer3D/IRenderer3D.hpp"
#include "Src/Input/Keyboard/IKeyboard.hpp"
#include "Src/Input/Mouse/IMouse.hpp"
#include "Src/Input/XInput/IXInput.hpp"
#include "Src/Input/Gamepad/IGamepad.hpp"
#include "Src/Texture/ITexture.hpp"
#include "Src/Sound/ISound.hpp"
#include "Src/Model/IModel.hpp"
#include "Src/GUI/IGUI.hpp"

#include "Include/Macro.hpp"

#include <wincodec.h>
#include <time.h>
#include <direct.h>
#include <ScreenGrab.h>

CSystem::FrameRate::FrameRate(UINT _MaxFrameRate)
{
  //  ���g�����擾
  QueryPerformanceFrequency(&FreqTime_);
  assert(FreqTime_.QuadPart != 0);
  //  �쐬���̎��Ԃ��擾
  QueryPerformanceCounter(&LastTime_);
}

bool CSystem::FrameRate::Update()
{
  //  ���݂̎��Ԃ��擾
  LARGE_INTEGER CurrentTime;
  QueryPerformanceCounter(&CurrentTime);

  //  ���݂̃t���[���o�ߎ��Ԃ��擾
  const float DeltaTime = (CurrentTime.QuadPart - LastTime_.QuadPart) / static_cast<float>(FreqTime_.QuadPart);

  if (DeltaTime < FrameInterval_)
  {
    //const DWORD SleepTime = static_cast<DWORD>((FrameInterval_ - DeltaTime) * 1000);
    //timeBeginPeriod(1);
    //Sleep(SleepTime);
    //timeEndPeriod(1);
    return false;
  }

  ++Frames_;
  if (((TimeStamp_ += DeltaTime) - TimeTlapsed_) >= 1.0f)
  {
    CurrentFPS_ = Frames_;

    Frames_ = 0;
    TimeTlapsed_ += 1.0f;
  }

  DeltaTime_ = DeltaTime;
  LastTime_ = CurrentTime;

  //  �X�V����
  return true;
}

void CSystem::FrameRate::SetFPS(UINT _MaxFPS)
{
  //  ���݂̎��Ԃ��擾
  LARGE_INTEGER CurrentTime;
  QueryPerformanceCounter(&CurrentTime);

  FrameInterval_ = ((_MaxFPS == 0) ? 0.0f : 1.0f / _MaxFPS);
  CurrentFPS_ = 0;
  DeltaTime_ = 0.0f;
  LastTime_ = CurrentTime;
}

//--------------------------------------------------

CSystem::Window::Window()
  : hWnd_(CreateWindow(L"HDXlib",
    L"HDXlib",
    WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
    LeftTopPos_.x,
    LeftTopPos_.y,
    Size_.x,
    Size_.y,
    GetDesktopWindow(),
    nullptr,
    GetModuleHandle(NULL),
    nullptr
  ))
{
  //  �G���[�`�F�b�N�p
  HRESULT hr = S_OK;

  //  COM������
  hr = CoInitialize(nullptr);
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
}

void CSystem::Window::SetUpWindow()
{
  //  �}�E�X���L���v�`���[
  ::SetCapture(hWnd_);

  //  �J�[�\���\���ݒ�
  ::ShowCursor(isShowCursor_);

  //  �E�B���h�E�^�C�g���ݒ�
  {
    wchar_t wWindowTitle[kCharMaxNum];
    mbstowcs_s(nullptr, wWindowTitle, Title_, kCharMaxNum);

    SetWindowText(hWnd_, wWindowTitle);
  }

  //  �E�B���h�E�ݒ�&�\��
  ::SetWindowPos(hWnd_, HWND_TOP, LeftTopPos_.x, LeftTopPos_.y, Size_.x, Size_.y, SWP_SHOWWINDOW);

  //pSwapChain_->SetFullscreenState(isFullScreen_, nullptr);
}

//--------------------------------------------------

CSystem::CSystem()
{
  TIMER_START("System");

  //  �t���[�����[�g�̍쐬
  pFrameRate_ = std::make_unique<FrameRate>(MaxFPS_);

  //  �E�B���h�E�̍쐬
  pWindow_ = std::make_unique<Window>();

  //  �f�o�C�X�̍쐬
  CreateDevice();

  //  �X���b�v�`�F�[���̍쐬
  CreateSwapChain();

  TIMER_END("System");
}

CSystem::~CSystem()
{
  pSwapChain_->SetFullscreenState(false, nullptr);
}

void CSystem::Initialize()
{
  Engine::Get<IBlendState>()->Initialize(pDevice_.Get());
  Engine::Get<IConstantBuffer>()->Initialize(pDevice_.Get());
  Engine::Get<IDepthStencilState>()->Initialize(pDevice_.Get());
  Engine::Get<IRasterizerState>()->Initialize(pDevice_.Get(), pSwapChain_.Get());
  Engine::Get<IRenderTarget>()->Initialize(pDevice_.Get(), pImmediateContext_.Get(), pSwapChain_.Get());
  Engine::Get<ISamplerState>()->Initialize(pDevice_.Get());
  Engine::Get<IVertexShader>()->Initialize(pDevice_.Get());
  Engine::Get<IPixelShader>()->Initialize(pDevice_.Get());
  Engine::Get<IRenderer2D>()->Initialize(pDevice_.Get(), pImmediateContext_.Get(), pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
  Engine::Get<IRenderer3D>()->Initialize(pDevice_.Get(), pImmediateContext_.Get(), pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
  Engine::Get<IGamepad>()->Initialize(pWindow_->hWnd_);
  Engine::Get<ITexture>()->Initialize(pDevice_.Get(), pSwapChain_.Get());
  Engine::Get<ISound>()->Initialize(pWindow_->hWnd_);
  Engine::Get<IModel>()->Initialize(pDevice_.Get());
  Engine::Get<IGUI>()->Initialize(pDevice_.Get(), pImmediateContext_.Get(), pWindow_->hWnd_);
}

bool CSystem::Update()
{
  //  �E�B���h�E�����ݒ�
  if (!isSetUpWindow_)
  {
    isSetUpWindow_ = true;
    pWindow_->SetUpWindow();

    pSwapChain_->SetFullscreenState(pWindow_->isFullScreen_, nullptr);

    ResizeSwapChain();
    CreateRenderTargetViewAndDepthStencilView();

    Engine::Get<IRenderer3D>()->CalcProjection();

    pFrameRate_->SetFPS(MaxFPS_);
  }

  //  ���͌n�X�V
  {
    Engine::Get<IKeyboard>()->Update();
    Engine::Get<IMouse>()->Update();
    Engine::Get<IXInput>()->Update();
    Engine::Get<IGamepad>()->Update();
  }

  //  GUI�̍X�V�ƕ`��
  Engine::Get<IGUI>()->Update();

  //  �T�E���h�̃��[�v����
  Engine::Get<ISound>()->Update();

  //  �`�无�\���]
  pSwapChain_->Present(0, 0);

  //  ���b�Z�[�W��S�ď���
  MSG Msg{};
  while (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
  }

  //  �X�N���[����������
  {
    //  �N���A�F
    const float ClearColor[4] = {
      pWindow_->BackColor_.R,
      pWindow_->BackColor_.G,
      pWindow_->BackColor_.B,
      pWindow_->BackColor_.A };

    pImmediateContext_->ClearRenderTargetView(pRenderTargetView_.Get(), ClearColor);
    pImmediateContext_->ClearDepthStencilView(pDepthStencilView_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    pImmediateContext_->OMSetRenderTargets(1, pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
  }

  //  FPS����
  //  ���Ԃ�����܂Ŗ������[�v(��)
  while (!pFrameRate_->Update());

  //  �E�B���h�E�̏�Ԃ�Ԃ�
  return ::IsWindow(pWindow_->hWnd_) != 0;
}

void CSystem::ShowCursor(bool _isShowCursor)
{
  pWindow_->isShowCursor_ = _isShowCursor;

  ::ShowCursor(_isShowCursor);
}

void CSystem::ChangeWindowMode()
{
  pSwapChain_->SetFullscreenState(pWindow_->isFullScreen_ = !pWindow_->isFullScreen_, nullptr);
}

void CSystem::RenameTitle(const char* _Title)
{
  wchar_t wWindowTitle[kCharMaxNum];
  mbstowcs_s(nullptr, wWindowTitle, pWindow_->Title_ = const_cast<char*>(_Title), kCharMaxNum);

  SetWindowText(pWindow_->hWnd_, wWindowTitle);
}

void CSystem::ScreenShot()
{
  //  �G���[�`�F�b�N�p
  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;

  hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBuffer.GetAddressOf()));

  //  ������
  if (SUCCEEDED(hr))
  {
    //  ���݂̎������擾
    time_t CurrentTime = time(nullptr);

    tm TM;
    localtime_s(&TM, &CurrentTime);

    //  �X�N���[���V���b�g�p�t�H���_�쐬
    _mkdir("SCREENSHOT");

    wchar_t wstr[kCharMaxNum];
    swprintf_s(wstr, L"SCREENSHOT/%04d%02d%02d%02d%02d%02d.png", TM.tm_year + 1900, TM.tm_mon + 1, TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec);

    DirectX::SaveWICTextureToFile(pImmediateContext_.Get(), BackBuffer.Get(), GUID_ContainerFormatPng, wstr);
  }
}

void CSystem::Exit()
{
  PostMessage(pWindow_->hWnd_, WM_CLOSE, 0, 0);
}

void CSystem::ResizeSwapChain()
{
  DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
  pSwapChain_->GetDesc(&SwapChainDesc);
  pSwapChain_->ResizeBuffers(SwapChainDesc.BufferCount, pWindow_->Size_.x, pWindow_->Size_.y, SwapChainDesc.BufferDesc.Format, SwapChainDesc.Flags);

  D3D11_VIEWPORT ViewPort{};
  ViewPort.TopLeftX = 0.0f;
  ViewPort.TopLeftY = 0.0f;
  ViewPort.Width = static_cast<float>(pWindow_->Size_.x);
  ViewPort.Height = static_cast<float>(pWindow_->Size_.y);
  ViewPort.MinDepth = 0.0f;
  ViewPort.MaxDepth = 1.0f;

  pImmediateContext_->RSSetViewports(1, &ViewPort);
}

void CSystem::CreateDevice()
{
  //  �G���[�`�F�b�N�p
  HRESULT hr = S_OK;

  //  �f�o�C�X�t���O
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
    D3D_FEATURE_LEVEL_11_1,
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
    D3D_FEATURE_LEVEL_9_3,
    D3D_FEATURE_LEVEL_9_2,
    D3D_FEATURE_LEVEL_9_1,
  };

  Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
  hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  IDXGIAdapter* pAdapter;
  {
    for (UINT i = 0; ; ++i)
    {
      if (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND)
      {
        break;
      }
    }
  }

  DXGI_ADAPTER_DESC AdapterDesc;
  pAdapter->GetDesc(&AdapterDesc);

  const UINT FeatureLevelNum = hdx::Macro::ArraySize(FeatureLevels);

  D3D_FEATURE_LEVEL FeatureLevel;
  for (auto i : DriverTypes)
  {
    //  �f�o�C�X���쐬
    hr = D3D11CreateDevice(pAdapter, DriverTypes[i], nullptr, CreateDeviceFlag, FeatureLevels,
      FeatureLevelNum, D3D11_SDK_VERSION, pDevice_.GetAddressOf(), &FeatureLevel, pImmediateContext_.GetAddressOf());

    //  �������ɏI��
    if (SUCCEEDED(hr))
    {
      break;
    }
  }
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
}

void CSystem::CreateSwapChain()
{
  //  �G���[�`�F�b�N�p
  HRESULT hr = S_OK;

  DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
  SwapChainDesc.BufferDesc.Width = pWindow_->Size_.x;
  SwapChainDesc.BufferDesc.Height = pWindow_->Size_.y;
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

  //  ALT+ENTER�����ɂ��ăX���b�v�`�F�[�����쐬
  {
    Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice;
    pDevice_.Get()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(pDXGIDevice.GetAddressOf()));
    Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
    pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(pAdapter.GetAddressOf()));
    Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
    pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

    hr = pFactory->CreateSwapChain(pDevice_.Get(), &SwapChainDesc, pSwapChain_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    hr = pFactory->MakeWindowAssociation(pWindow_->hWnd_, DXGI_MWA_NO_ALT_ENTER);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }
}

void CSystem::CreateRenderTargetViewAndDepthStencilView()
{
  //  �G���[�`�F�b�N�p
  HRESULT hr = S_OK;

  //  �����_�[�^�[�Q�b�g�r���[�̍쐬
  D3D11_TEXTURE2D_DESC BackBufferDesc{};
  {
    Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
    hr = pSwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    hr = pDevice_->CreateRenderTargetView(pBackBuffer.Get(), nullptr, pRenderTargetView_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    pBackBuffer->GetDesc(&BackBufferDesc);
  }

  //  �[�x�X�e���V���r���[�̍쐬
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
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    pSwapChain_->GetDesc(&SwapChainDesc);

    D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
    DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
    DepthStencilViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
    DepthStencilViewDesc.Flags = 0;
    DepthStencilViewDesc.Texture2D.MipSlice = 0;

    hr = pDevice_->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, pDepthStencilView_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  pImmediateContext_->OMSetRenderTargets(1, pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
}