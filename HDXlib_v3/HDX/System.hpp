#pragma once
#include <HDX/Singleton.hpp>
#include <HDX/Color.hpp>
#include <HDX/Type2.hpp>
#include <HDX/NumberMap.hpp>

#include <Windows.h>
#include <d3d11.h>
#include <wrl.h>
#include <memory>

//  前方宣言
namespace hdx
{
  enum class BlendState;
}

namespace detail
{
  class IKeyboard;
  class IMouse;
  class IXInput;
  class IGamepad;
  class IVertexShader;
  class IPixelShader;
  class WIC;

  class System : public hdx::Singleton<System>
  {
    struct WindowData
    {
      hdx::int2 LeftTopPos = { 0,0 };
      hdx::int2 Size = { 1280,720 };
      char* Title = "HDXlib";
      bool isFullScreen = false;
      bool isShowCursor = false;
      hdx::ColorF BackColor = hdx::Palette::Black;
    };
    class FrameRate
    {
      const int kMaxFrameRate;    //  固定フレームレート値
      const float kFrameInterval; //  フレーム間隔
    private:
      float NowFPS_ = 0.0f;     //  現在のFPS
      LARGE_INTEGER FreqTime_;  //  クロック数
      LARGE_INTEGER LastTime_;  //  最後の時間
    public:
      FrameRate(int Maxframerate);
      bool Update();
    public:
      float GetFPS()const { return NowFPS_; }
    };
    class Blend
    {
      std::unique_ptr<Microsoft::WRL::ComPtr<ID3D11BlendState>[]> States_; //  ブレンドステート
    public:
      ID3D11BlendState* GetState(hdx::BlendState State) { return States_[static_cast<int>(State)].Get(); }
    public:
      Blend();
    };
    class SpriteManager
    {
      struct TextureData
      {
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView;
        hdx::int2 Size_;
      };
    private:
      int VertexShaderID_;
      int PixelShaderID_;
    private:
      Microsoft::WRL::ComPtr<ID3D11Buffer>            pVertexBuffer_;
      Microsoft::WRL::ComPtr<ID3D11RasterizerState>   pRasterizerState_;
      Microsoft::WRL::ComPtr<ID3D11SamplerState>      pSamplerState_;
      Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState_;
      NumberMap<std::string, TextureData> TextureMap_;
    public:
      int GetVertexShaderID()const { return VertexShaderID_; }
      int GetPixelShaderID()const { return PixelShaderID_; }
    public:
      ID3D11Buffer* GetVertexBuffer()const { return pVertexBuffer_.Get(); }
      ID3D11Buffer** GetAddressOfVertexBuffer() { return pVertexBuffer_.GetAddressOf(); }
      ID3D11RasterizerState* GetRasterizerState()const { return pRasterizerState_.Get(); }
      ID3D11SamplerState** GetAddressOfSamplerState() { return pSamplerState_.GetAddressOf(); }
      ID3D11DepthStencilState* GetDepthStencilState()const { return pDepthStencilState_.Get(); }
    public:
      HRESULT Initialize();
      int GetShaderResourceViewID(std::string FilePath);
      int InsertTextureDataMap(std::string FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView, const hdx::int2& _Size);
      hdx::int2 GetSize(int _ID) { return TextureMap_[_ID].Size_; }
      ID3D11ShaderResourceView* GetShaderResourceView(int number) { return TextureMap_[number].pShaderResourceView.Get(); }
      ID3D11ShaderResourceView** GetAddressOfShaderResourceView(int number) { return TextureMap_[number].pShaderResourceView.GetAddressOf(); }
      void Reset() { TextureMap_.clear(); }
    };
    class MeshManager
    {
      int VertexShaderID_;
      int PixelShaderID_;
    private:
      Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer_;
      Microsoft::WRL::ComPtr<ID3D11RasterizerState> pWireFrameState_;
      Microsoft::WRL::ComPtr<ID3D11RasterizerState> pSolidState_;
      Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState_;
      Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState_;
      NumberMap<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> ShaderResouceViewMap_;
    public:
      int GetVertexShaderID()const { return VertexShaderID_; }
      int GetPixelShaderID()const { return PixelShaderID_; }
    public:
      ID3D11Buffer* GetConstantBuffer()const { return pConstantBuffer_.Get(); }
      ID3D11Buffer** GetAddressOfConstantBuffer() { return pConstantBuffer_.GetAddressOf(); }
      ID3D11RasterizerState* GetWireFrameState()const { return pWireFrameState_.Get(); }
      ID3D11RasterizerState* GetSolidState()const { return pSolidState_.Get(); }
      ID3D11SamplerState** GetAddressOfSamplerState() { return pSamplerState_.GetAddressOf(); }
      ID3D11DepthStencilState* GetDepthStencilState()const { return pDepthStencilState_.Get(); }
    public:
      HRESULT Initialize();
      int GetShaderResourceViewID(std::wstring FilePath);
      int InsertShaderResourceViewMap(std::wstring FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView);
      ID3D11ShaderResourceView* GetShaderResourceView(int number) { return ShaderResouceViewMap_[number].Get(); }
      ID3D11ShaderResourceView** GetAddressOfShaderResourceView(int number) { return ShaderResouceViewMap_[number].GetAddressOf(); }
      void Reset() { ShaderResouceViewMap_.clear(); }
    };
    class PrimitiveManager
    {
      int VertexShaderID_;
      int PixelShaderID_;
      Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer_;
      Microsoft::WRL::ComPtr<ID3D11RasterizerState> pWireFrameState_;
      Microsoft::WRL::ComPtr<ID3D11RasterizerState> pSolidState_;
      Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState_;
      Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState_;
      NumberMap<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> ShaderResouceViewMap_;
    public:
      int GetVertexShaderID()const { return VertexShaderID_; }
      int GetPixelShaderID()const { return PixelShaderID_; }
    public:
      ID3D11Buffer* GetConstantBuffer()const { return pConstantBuffer_.Get(); }
      ID3D11Buffer** GetAddressOfConstantBuffer() { return pConstantBuffer_.GetAddressOf(); }
      ID3D11RasterizerState* GetWireFrameState()const { return pWireFrameState_.Get(); }
      ID3D11RasterizerState* GetSolidState()const { return pSolidState_.Get(); }
      ID3D11SamplerState** GetAddressOfSamplerState() { return pSamplerState_.GetAddressOf(); }
      ID3D11DepthStencilState* GetDepthStencilState()const { return pDepthStencilState_.Get(); }
    public:
      HRESULT Initialize();
      int GetShaderResourceViewID(std::wstring FilePath);
      int InsertShaderResourceViewMap(std::wstring FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView);
      ID3D11ShaderResourceView* GetShaderResourceView(int number) { return ShaderResouceViewMap_[number].Get(); }
      ID3D11ShaderResourceView** GetAddressOfShaderResourceView(int number) { return ShaderResouceViewMap_[number].GetAddressOf(); }
      void Reset() { ShaderResouceViewMap_.clear(); }
    };
    class FbxManager
    {
      int VertexShaderID_;
      int PixelShaderID_;
      Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer_;
      Microsoft::WRL::ComPtr<ID3D11RasterizerState> pWireFrameState_;
      Microsoft::WRL::ComPtr<ID3D11RasterizerState> pSolidState_;
      Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState_;
      Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState_;
      NumberMap<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> ShaderResouceViewMap_;
    public:
      int GetVertexShaderID()const { return VertexShaderID_; }
      int GetPixelShaderID()const { return PixelShaderID_; }
    public:
      ID3D11Buffer* GetConstantBuffer()const { return pConstantBuffer_.Get(); }
      ID3D11Buffer** GetAddressOfConstantBuffer() { return pConstantBuffer_.GetAddressOf(); }
      ID3D11RasterizerState* GetWireFrameState()const { return pWireFrameState_.Get(); }
      ID3D11RasterizerState* GetSolidState()const { return pSolidState_.Get(); }
      ID3D11SamplerState** GetAddressOfSamplerState() { return pSamplerState_.GetAddressOf(); }
      ID3D11DepthStencilState* GetDepthStencilState()const { return pDepthStencilState_.Get(); }
    public:
      HRESULT Initialize();
      int GetShaderResourceViewID(std::wstring FilePath);
      int InsertShaderResourceViewMap(std::wstring FilePath, const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& pShaderResourceView);
      ID3D11ShaderResourceView* GetShaderResourceView(int number) { return ShaderResouceViewMap_[number].Get(); }
      ID3D11ShaderResourceView** GetAddressOfShaderResourceView(int number) { return ShaderResouceViewMap_[number].GetAddressOf(); }
      void Reset() { ShaderResouceViewMap_.clear(); }
    };
  private:
    HWND hWnd_ = {};          //  ウィンドウハンドル
    D3D11_VIEWPORT ViewPort_; //  ビューポート
  private:
    Microsoft::WRL::ComPtr<ID3D11Device>		    pDevice_;           //  デバイス(DirectX)
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>	    pDeviceContext_;    //  デバイスコンテキスト(DirectX)
    Microsoft::WRL::ComPtr<IDXGISwapChain>		    pSwapChain_;        //  スワップチェイン(DirectX)
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  pRenderTargetView_; //  レンダーターゲットビュー(DirectX)
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  pDepthStencilView_; //  デプスステンシルビュー(DirectX)
  private:
    WindowData WindowData_;
    std::unique_ptr<FrameRate>  pFPS_;
    std::unique_ptr<Blend>      pBlender_;
    IKeyboard*                  pKeyboard_;
    IMouse*                     pMouse_;
    IXInput*                    pXInput_;
    IGamepad*                   pGamepad_;
    IVertexShader*              pVertexShader_;
    IPixelShader*               pPixelShader_;
    WIC*                        pWIC_;
  private:
    SpriteManager     SpriteManager_;     //  画像管理
    MeshManager       MeshManager_;       //  メッシュ管理
    PrimitiveManager  PrimitiveManager_;  //  プリミティブ管理  
    FbxManager        FbxManager_;        //  FBX管理
  public:
    int GetWindowWidth()const { return WindowData_.Size.X; }
    int GetWindowHeight()const { return WindowData_.Size.Y; }
    hdx::int2 GetWindowSize()const { return WindowData_.Size; }
    bool isFullScreen()const { return WindowData_.isFullScreen; }
    bool isNotCloseWindow()const { return IsWindow(hWnd_) != 0; }
  public:
    ID3D11Device* GetDevice()const { return pDevice_.Get(); }
    ID3D11DeviceContext* GetDeviceContext()const { return pDeviceContext_.Get(); }
    IDXGISwapChain* GetSwapChain()const { return pSwapChain_.Get(); }
    const HWND& GetHWND()const { return hWnd_; }
  public:
    SpriteManager* GetSpriteManager() { return &SpriteManager_; }
    MeshManager* GetMeshManager() { return &MeshManager_; }
    PrimitiveManager* GetPrimitiveManager() { return &PrimitiveManager_; }
    FbxManager* GetFbxManager() { return &FbxManager_; }
  public:
    void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos)
    {
      WindowData_.LeftTopPos = _LeftTopPos;
    }
    void SetWindowSize(const hdx::int2& _Size)
    {
      WindowData_.Size = _Size;
    }
    void SetWindowMode(bool _isFullScreen)
    {
      WindowData_.isFullScreen = _isFullScreen;
    }
    void SetWindowData(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen)
    {
      WindowData_.LeftTopPos = _LeftTopPos;
      WindowData_.Size = _Size;
      WindowData_.isFullScreen = _isFullScreen;
    }
    void SetShowCursor(bool _isShowCursor)
    {
      WindowData_.isShowCursor = _isShowCursor;
    }
    void SetTitle(char* _Title)
    {
      WindowData_.Title = _Title;
    }
    void SetBackColor(const hdx::ColorF& _Color)
    {
      WindowData_.BackColor = _Color;
    }
    void MoveWindowLeftTopPos(const hdx::int2& _LeftTopPos)
    {
      SetWindowPos(hWnd_, HWND_TOP, WindowData_.LeftTopPos.X = _LeftTopPos.X, WindowData_.LeftTopPos.Y = _LeftTopPos.Y, WindowData_.Size.X, WindowData_.Size.Y, SWP_SHOWWINDOW);
    }
    //void ResizeWindow(int _Width, int _Height)
    //{
    //  SetWindowPos(hWnd_, HWND_TOP, WindowData_.LeftPos, WindowData_.TopPos, WindowData_.Width = _Width, WindowData_.Height = _Height, SWP_SHOWWINDOW);
    //
    //  pDeviceContext_->OMSetRenderTargets(0, nullptr, nullptr);
    //
    //  DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
    //  pSwapChain_->GetDesc(&SwapChainDesc);
    //  pSwapChain_->ResizeBuffers(SwapChainDesc.BufferCount, WindowData_.Width, WindowData_.Height, SwapChainDesc.BufferDesc.Format, SwapChainDesc.Flags);
    //}
    void ChangeShowCursorMode()
    {
      ShowCursor(WindowData_.isShowCursor = !WindowData_.isShowCursor);
    }
    void Exit()
    {
      PostMessage(hWnd_, WM_CLOSE, 0, 0);
    }
    void RenameTitle(const char* _Title);
    void ScreenShot();
    void ChangeWindowMode();
  public:
    bool FrameRateUpdate()
    {
      return pFPS_->Update();
    }
    void ScreenClear()const
    {
      //  クリア色
      const float ClearColor[4] = { WindowData_.BackColor.R,WindowData_.BackColor.G,WindowData_.BackColor.B,WindowData_.BackColor.A };

      pDeviceContext_->ClearRenderTargetView(pRenderTargetView_.Get(), ClearColor);
      pDeviceContext_->ClearDepthStencilView(pDepthStencilView_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
      pDeviceContext_->OMSetRenderTargets(1, pRenderTargetView_.GetAddressOf(), pDepthStencilView_.Get());
    }
    void Present()const
    {
      pSwapChain_->Present(0, 0);
    }
  private:
    void SetUpWindow();
    //void CreateVS(const char* FileName, D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppInputLayout);
    //void CreatePS(const char* FileName, ID3D11PixelShader** ppPixelShader);
  public:
    HRESULT MakeDummyTexture(ID3D11ShaderResourceView** ppShaderResouceView);
  public:
    void OMSetBlendState(hdx::BlendState _BlendState);
    void PSSetShaderResources(ID3D11ShaderResourceView*const* _ppShaderResourceView);
    void IASetVertexBuffers(ID3D11Buffer*const* _ppVertexBuffer, UINT Strides, UINT Offsets);
    void IASetInputLayout(ID3D11InputLayout* _pInputLayout);
    void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology);
    void RSSetState(ID3D11RasterizerState* _pRasterizerState);
    void VSSetShader(ID3D11VertexShader* _pVertexShader);
    void PSSetShader(ID3D11PixelShader* _pPixelShader);
    void PSSetSamplers(ID3D11SamplerState*const* _ppSamplerState);
    void OMSetDepthStencilState(ID3D11DepthStencilState* _pDepthStencilState);
    void OMSetRenderTargets(ID3D11RenderTargetView** _ppRenderTargetView, ID3D11DepthStencilView* _pDepthStencilView);
  public:
    IKeyboard* GetKeyboard()const { return pKeyboard_; }
    IMouse* GetMouse()const { return pMouse_; }
    IXInput* GetXInput()const { return pXInput_; }
    IGamepad* GetGamepad()const { return pGamepad_; }
    IVertexShader* GetVertexShader()const { return pVertexShader_; }
    IPixelShader* GetPixelShader()const { return pPixelShader_; }
    WIC* GetWIC()const { return pWIC_; }
  public:
    void Initialize();
    void InitializeD3D();
    void CreateWindowAndDeviceAndSwapChain(const HINSTANCE& _hInstane);
    LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
  public:
    ~System();
  };
}

//  ライブラリ
namespace hdx
{
  //  システム
  class System
  {
    System() = delete;
    System(const System&) = delete;
    System& operator=(const System&) = delete;
  public:
    //  画面幅を取得
    static int GetWindowWidth()
    {
      return detail::System::Get()->GetWindowWidth();
    }
    //  画面高を取得
    static int GetWindowHeight()
    {
      return detail::System::Get()->GetWindowHeight();
    }
    static int2 GetWindowSize()
    {
      return detail::System::Get()->GetWindowSize();
    }
  public:
    //  ウィンドウの設定
    //  _LeftPos:左上座標X
    //  _TopPos:左上座標Y
    static void SetWindowLeftTopPos(int _LeftPos, int _TopPos)
    {
      detail::System::Get()->SetWindowLeftTopPos({ _LeftPos, _TopPos });
    }
    //  ウィンドウの設定
    //  _LeftTopPos:左上座標
    static void SetWindowLeftTopPos(const hdx::int2& _LeftTopPos)
    {
      detail::System::Get()->SetWindowLeftTopPos(_LeftTopPos);
    }
    //  ウィンドウの設定
    //  _Width:ウィンドウ幅
    //  _Height:ウィンドウ高
    static void SetWindowSize(int _Width, int _Height)
    {
      detail::System::Get()->SetWindowSize({ _Width, _Height });
    }
    //  ウィンドウの設定
    //  _Size:ウィンドウ縦横幅
    static void SetWindowSize(const hdx::int2& _Size)
    {
      detail::System::Get()->SetWindowSize(_Size);
    }
    //  ウィンドウの設定
    //  _isFullScreen:画面モード(true:フルスクリーン,false:ウィンドウモード)
    static void SetWindowMode(bool _isFullScreen)
    {
      detail::System::Get()->SetWindowMode(_isFullScreen);
    }
    //  ウィンドウの設定
    //  _LeftPos:左上座標X
    //  _TopPos:左上座標Y
    //  _Width:ウィンドウ幅
    //  _Height:ウィンドウ高
    //  _isFullScreen:画面モード(true:フルスクリーン,false:ウィンドウモード)
    static void SettingWindow(int _LeftPos, int _TopPos, int _Width, int _Height, bool _isFullScreen = false)
    {
      detail::System::Get()->SetWindowData({ _LeftPos, _TopPos }, { _Width, _Height }, _isFullScreen);
    }
    //  ウィンドウの設定
    //  _LeftTopPos:左上座標
    //  _Size:ウィンドウ縦横幅
    //  _isFullScreen:画面モード(true:フルスクリーン,false:ウィンドウモード)
    static void SettingWindow(const hdx::int2& _LeftTopPos, const hdx::int2& _Size, bool _isFullScreen = false)
    {
      detail::System::Get()->SetWindowData(_LeftTopPos, _Size, _isFullScreen);
    }
    //  カーソル表示設定(true:表示,false:非表示)
    static void ShowCursor(bool _isShowCursor)
    {
      detail::System::Get()->SetShowCursor(_isShowCursor);
    }
    //  ウィンドウのタイトルを設定
    static void SetTitle(char* _Title)
    {
      detail::System::Get()->SetTitle(_Title);
    }
    //  背景の色変更
    static void SetBackColor(const hdx::ColorF& _Color)
    {
      detail::System::Get()->SetBackColor(_Color);
    }

    ////  ウィンドウのサイズを変更
    ////  _Width:ウィンドウ幅
    ////  _Height:ウィンドウ高 
    //static inline void ResizeWindow(int _Width, int _Height)
    //{
    //  detail::System::Get()->ResizeWindow(_Width, _Height);
    //}

    //  ウィンドウのモードを変更
    //  ウィンドウモード⇔フルスクリーン
    static void ChangeWindowMode()
    {
      detail::System::Get()->ChangeWindowMode();
    }
    //  カーソルの表示を変更
    //  表示⇔非表示
    static void ChangeShowCursorMode()
    {
      detail::System::Get()->ChangeShowCursorMode();
    }
    //  ウィンドウのタイトルを変更
    static void RenameTitle(const char* _Title)
    {
      detail::System::Get()->RenameTitle(_Title);
    }
    //  ソフトを終了
    static void Exit()
    {
      detail::System::Get()->Exit();
    }
    //  スクリーンショット
    //  SCREENSHOTフォルダに保存
    static void ScreenShot()
    {
      detail::System::Get()->ScreenShot();
    }
  public:
    //  更新
    static int Update();
  };
};
