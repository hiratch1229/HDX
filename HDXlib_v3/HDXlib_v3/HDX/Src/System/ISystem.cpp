#include "ISystem.hpp"

#include "../Engine.hpp"
#include "../Input/Keyboard/IKeyboard.hpp"
#include "../Input/Mouse/IMouse.hpp"
#include "../Input/XInput/IXInput.hpp"
#include "../Input/Gamepad/IGamepad.hpp"
#include "../Renderer/Renderer2D/IRenderer2D.hpp"
#include "../Renderer/Renderer3D/IRenderer3D.hpp"
#include "../GUI/IGUI.hpp"
#include "../Misc.hpp"

#include "../../Include/System.hpp"
#include "../../Include/Type2.hpp"
#include "../../Include/Color.hpp"

#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>
#include <wincodec.h>
#include <assert.h>

#include <time.h>
#include <direct.h>
#include <ScreenGrab.h>

#include <memory>
#include <functional>

namespace
{
  class FrameRate
  {
    //  �Œ�t���[�����[�g�l
    const int MaxFrameRate_;
    //  �t���[���Ԋu
    const float FrameInterval_;
  private:
    //  ���݂�FPS
    float CurrentFPS_ = 0.0f;
    //  �N���b�N��
    LARGE_INTEGER FreqTime_;
    //  �Ō�̎���
    LARGE_INTEGER LastTime_;
  public:
    //  �o�ߎ���
    float DeltaTime_ = 0.0f;
  public:
    FrameRate(int _MaxFrameRate)
      : MaxFrameRate_(_MaxFrameRate), FrameInterval_(1.0f / _MaxFrameRate)
    {
      //  ���g�����擾
      QueryPerformanceFrequency(&FreqTime_);
      assert(FreqTime_.QuadPart != 0);
      //  �쐬���̎��Ԃ��擾
      QueryPerformanceCounter(&LastTime_);
    }
    bool Update()
    {
      //  ���݂̎��Ԃ��擾
      LARGE_INTEGER CurrentTime;
      QueryPerformanceCounter(&CurrentTime);

      //  ���݂̃t���[���o�ߎ��Ԃ��擾
      const float DeltaTime = (CurrentTime.QuadPart - LastTime_.QuadPart) / static_cast<float>(FreqTime_.QuadPart);

#if 1
      //  �o�ߎ��Ԃ��Z���Ȃ玸�s
      if (DeltaTime < FrameInterval_)
      {
        return false;
      }
#else
      //  �o�ߎ��Ԃ��Z���Ȃ�X���[�v
      if (DeltaTime < FrameInterval_)
      {
        DWORD SleepTime = static_cast<DWORD>((FrameInterval_ - DeltaTime) * 1000);
        timeBeginPeriod(1);
        Sleep(SleepTime);
        timeEndPeriod(1);
        return false;
      }
#endif

      CurrentFPS_ = 1.0f / DeltaTime;
      DeltaTime_ = DeltaTime;
      LastTime_ = CurrentTime;

      //  �X�V����
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
    //  �E�B���h�E��ݒ�
    void SetUpWindow()
    {
      //  �}�E�X���L���v�`���[
      ::SetCapture(hWnd_);

      //  �J�[�\���\���ݒ�
      ::ShowCursor(isShowCursor_);

      //  �E�B���h�E�^�C�g���ݒ�
      {
        wchar_t wWindowTitle[hdx::MaxCharLimit];
        mbstowcs_s(nullptr, wWindowTitle, Title_, hdx::MaxCharLimit);

        SetWindowText(hWnd_, wWindowTitle);
      }

      //  �E�B���h�E�ݒ�&�\��
      ::SetWindowPos(hWnd_, HWND_TOP, LeftTopPos_.X, LeftTopPos_.Y, Size_.X, Size_.Y, SWP_SHOWWINDOW);
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
      //  �G���[�`�F�b�N�p
      HRESULT hr = S_OK;

      //  COM������
      hr = CoInitialize(nullptr);
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

      //  �E�B���h�E�n���h�����A�N�e�B�u��
      ::SetActiveWindow(hWnd_);
    }
    ~Window() = default;
  };

  bool isSetUpWindow = false;
  std::unique_ptr<FrameRate> pFrameRate;
  std::unique_ptr<Window> pWindow;
  Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmediateContext;
  Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
  Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
  Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView;

  void ResizeSwapChain()
  {
    DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    pSwapChain->GetDesc(&SwapChainDesc);
    pSwapChain->ResizeBuffers(SwapChainDesc.BufferCount, pWindow->Size_.X, pWindow->Size_.Y, SwapChainDesc.BufferDesc.Format, SwapChainDesc.Flags);

    D3D11_VIEWPORT ViewPort{};
    ViewPort.TopLeftX = 0.0f;
    ViewPort.TopLeftY = 0.0f;
    ViewPort.Width = static_cast<float>(pWindow->Size_.X);
    ViewPort.Height = static_cast<float>(pWindow->Size_.Y);
    ViewPort.MinDepth = 0.0f;
    ViewPort.MaxDepth = 1.0f;

    pImmediateContext->RSSetViewports(1, &ViewPort);
  }

  void CreateDevice()
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

      //  �f�o�C�X���쐬
      hr = D3D11CreateDevice(nullptr, DriverTypes[i], nullptr, CreateDeviceFlag, FeatureLevels,
        FeatureLevelNum, D3D11_SDK_VERSION, pDevice.GetAddressOf(), &FeatureLevel, pImmediateContext.GetAddressOf());

      //  �������ɏI��
      if (SUCCEEDED(hr))
      {
        break;
      }
    }
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  void CreateSwapChain()
  {
    //  �G���[�`�F�b�N�p
    HRESULT hr = S_OK;

    DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    SwapChainDesc.BufferDesc.Width = pWindow->Size_.X;
    SwapChainDesc.BufferDesc.Height = pWindow->Size_.Y;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.SampleDesc.Quality = 0;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = 1;
    SwapChainDesc.OutputWindow = pWindow->hWnd_;
    SwapChainDesc.Windowed = true;
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    SwapChainDesc.Flags = 0;

    //  ALT+ENTER�����ɂ��ăX���b�v�`�F�[�����쐬
    {
      Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice;
      pDevice.Get()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(pDXGIDevice.GetAddressOf()));
      Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
      pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(pAdapter.GetAddressOf()));
      Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
      pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));

      hr = pFactory->CreateSwapChain(pDevice.Get(), &SwapChainDesc, pSwapChain.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
      hr = pFactory->MakeWindowAssociation(pWindow->hWnd_, DXGI_MWA_NO_ALT_ENTER);
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    }
  }

  void CreateRenderTargetViewAndDepthStencilView()
  {
    //  �G���[�`�F�b�N�p
    HRESULT hr = S_OK;

    //  �����_�[�^�[�Q�b�g�r���[�̍쐬
    D3D11_TEXTURE2D_DESC BackBufferDesc{};
    {
      Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
      hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

      hr = pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, pRenderTargetView.GetAddressOf());
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

      hr = pDevice->CreateTexture2D(&DepthStencilBufferDesc, nullptr, DepthStencilBuffer.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

      DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
      pSwapChain->GetDesc(&SwapChainDesc);

      D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc;
      DepthStencilViewDesc.Format = DepthStencilBufferDesc.Format;
      DepthStencilViewDesc.ViewDimension = (SwapChainDesc.SampleDesc.Count != 1) ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
      DepthStencilViewDesc.Flags = 0;
      DepthStencilViewDesc.Texture2D.MipSlice = 0;

      hr = pDevice->CreateDepthStencilView(DepthStencilBuffer.Get(), &DepthStencilViewDesc, pDepthStencilView.GetAddressOf());
      _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
    }

    pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());
  }
}

ISystem::ISystem()
{
  TIMER_START("System");

  //  �t���[�����[�g�̍쐬
  pFrameRate = std::make_unique<FrameRate>(60);

  //  �E�B���h�E�̍쐬
  pWindow = std::make_unique<Window>();

  //  �f�o�C�X�̍쐬
  CreateDevice();

  //  �O�p���X�g�ݒ�
  pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

  //  �X���b�v�`�F�[���̍쐬
  CreateSwapChain();

  TIMER_END("System");
}

bool ISystem::Update()
{
  //  �E�B���h�E�����ݒ�
  if (!isSetUpWindow)
  {
    isSetUpWindow = true;
    pWindow->SetUpWindow();
    ResizeSwapChain();
    CreateRenderTargetViewAndDepthStencilView();

    Engine::Get<IRenderer3D>()->CalcProjection();
  }

  //  ���͌n�X�V
  {
    Engine::Get<IKeyboard>()->Update();
    Engine::Get<IMouse>()->Update();
    Engine::Get<IXInput>()->Update();
    Engine::Get<IGamepad>()->Update();
  }

  //  �c���Ă���X�v���C�g�̕`��
  Engine::Get<IRenderer2D>()->End();

  //  GUI�̍X�V�ƕ`��
  Engine::Get<IGUI>()->Update();

  //  �`�无�\���]
  pSwapChain->Present(0, 0);

  //  ���b�Z�[�W��S�ď���
  MSG Msg{};
  while (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
  }

  //  FPS����
  //  ���Ԃ�����܂Ŗ������[�v(��)
  while (!pFrameRate->Update());

  //  �X�N���[����������
  {
    //  �N���A�F
    const float ClearColor[4] = {
      pWindow->BackColor_.R,
      pWindow->BackColor_.G,
      pWindow->BackColor_.B,
      pWindow->BackColor_.A };

    pImmediateContext->ClearRenderTargetView(pRenderTargetView.Get(), ClearColor);
    pImmediateContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    pImmediateContext->OMSetRenderTargets(1, pRenderTargetView.GetAddressOf(), pDepthStencilView.Get());
  }

  //  �E�B���h�E�̏�Ԃ�Ԃ�
  return ::IsWindow(pWindow->hWnd_) != 0;
}

void ISystem::ChangeWindowMode()
{
  pSwapChain->SetFullscreenState(pWindow->isFullScreen_ = !pWindow->isFullScreen_, nullptr);
}

void ISystem::RenameTitle(const char* _Title)
{
  wchar_t wWindowTitle[hdx::MaxCharLimit];
  mbstowcs_s(nullptr, wWindowTitle, pWindow->Title_ = const_cast<char*>(_Title), hdx::MaxCharLimit);

  SetWindowText(pWindow->hWnd_, wWindowTitle);
}

void ISystem::ScreenShot()
{
  //  �G���[�`�F�b�N�p
  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;

  hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBuffer.GetAddressOf()));

  //  ������
  if (SUCCEEDED(hr))
  {
    //  ���݂̎������擾
    time_t CurrentTime = time(nullptr);

    tm TM;
    localtime_s(&TM, &CurrentTime);

    //  �X�N���[���V���b�g�p�t�H���_�쐬
    _mkdir("SCREENSHOT");

    wchar_t wstr[hdx::MaxCharLimit];
    swprintf_s(wstr, L"SCREENSHOT/%04d%02d%02d%02d%02d%02d.png", TM.tm_year + 1900, TM.tm_mon + 1, TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec);

    DirectX::SaveWICTextureToFile(pImmediateContext.Get(), BackBuffer.Get(), GUID_ContainerFormatPng, wstr);
  }
}

void ISystem::Exit()
{
  PostMessage(pWindow->hWnd_, WM_CLOSE, 0, 0);
}

int ISystem::GetWindowWidth()const
{
  return pWindow->Size_.X;
}

int ISystem::GetWindowHeight()const
{
  return pWindow->Size_.Y;
}

const hdx::int2& ISystem::GetWindowSize()const
{
  return pWindow->Size_;
}

float ISystem::GetDeltaTime()const
{
  return pFrameRate->DeltaTime_;
}

void ISystem::SetWindowLeftTopPos(int _LeftPos, int _TopPos)
{
  pWindow->LeftTopPos_ = { _LeftPos, _TopPos };
}

void ISystem::SetWindowLeftTopPos(const hdx::int2& _LeftTopPos)
{
  pWindow->LeftTopPos_ = _LeftTopPos;
}

void ISystem::SetWindowSize(int _Width, int _Height)
{
  pWindow->Size_ = { _Width, _Height };
}

void ISystem::SetWindowSize(const hdx::int2& _Size)
{
  pWindow->Size_ = _Size;
}

void ISystem::SetWindowMode(bool _isFullScreen)
{
  pWindow->isFullScreen_ = _isFullScreen;
}

void ISystem::SetWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen)
{
  pWindow->LeftTopPos_ = { _LeftPos, _TopPos };
  pWindow->Size_ = { _Width, _Height };
  pWindow->isFullScreen_ = _isFullScreen;
}

void ISystem::SetWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen)
{
  pWindow->LeftTopPos_ = _LeftTopPos;
  pWindow->Size_ = _Size;
  pWindow->isFullScreen_ = _isFullScreen;
}

void ISystem::ShowCursor(bool _isShowCursor)
{
  pWindow->isShowCursor_ = _isShowCursor;

  ::ShowCursor(_isShowCursor);
}

void ISystem::SetTitle(const char* _Title)
{
  pWindow->Title_ = const_cast<char*>(_Title);
}

void ISystem::SetBackColor(const hdx::ColorF& _Color)
{
  pWindow->BackColor_ = _Color;
}

ID3D11Device* ISystem::GetDevice()
{
  return pDevice.Get();
}

ID3D11DeviceContext* ISystem::GetImmediateContext()
{
  return pImmediateContext.Get();
}

IDXGISwapChain* ISystem::GetSwapChain()
{
  return pSwapChain.Get();
}

ID3D11RenderTargetView** ISystem::GetRenderTargetView()
{
  return pRenderTargetView.GetAddressOf();
}

ID3D11DepthStencilView* ISystem::GetDepthStencilView()
{
  return pDepthStencilView.Get();
}

const HWND& ISystem::GethWnd()
{
  return pWindow->hWnd_;
}
