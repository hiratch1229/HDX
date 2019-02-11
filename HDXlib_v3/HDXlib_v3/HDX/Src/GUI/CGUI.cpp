#include "CGUI.hpp"

#include "Src/Engine.hpp"
#include "Src/System/ISystem.hpp"
#include "Src/Input/Keyboard/IKeyboard.hpp"
#include "Src/Input/Mouse/IMouse.hpp"
#include "Src/VertexShader/IVertexShader.hpp"
#include "Src/PixelShader/IPixelShader.hpp"
#include "Src/Renderer/Renderer2D/IRenderer2D.hpp"
#include "Src/Renderer/Renderer3D/IRenderer3D.hpp"

#include "Src/Misc.hpp"
#include "Src/Constants.hpp"

#include "Include/Mouse.hpp"

CGUI::Win32::Win32(const HWND& _hWnd)
  : hWnd_(_hWnd)
{
  ImGuiIO& io = ImGui::GetIO();
  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors; // We can honor GetMouseCursor() values (optional)
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;  // We can honor io.WantSetMousePos requests (optional, rarely used)
  io.ImeWindowHandle = hWnd_;

  // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array that we will update during the application lifetime.
  io.KeyMap[ImGuiKey_Tab] = VK_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
  io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
  io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
  io.KeyMap[ImGuiKey_Home] = VK_HOME;
  io.KeyMap[ImGuiKey_End] = VK_END;
  io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
  io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
  io.KeyMap[ImGuiKey_Space] = VK_SPACE;
  io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
  io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
  io.KeyMap[ImGuiKey_A] = 'A';
  io.KeyMap[ImGuiKey_C] = 'C';
  io.KeyMap[ImGuiKey_V] = 'V';
  io.KeyMap[ImGuiKey_X] = 'X';
  io.KeyMap[ImGuiKey_Y] = 'Y';
  io.KeyMap[ImGuiKey_Z] = 'Z';
}

void CGUI::Win32::NewFrame()
{
  ImGuiIO& io = ImGui::GetIO();

  //  Setup display size (every frame to accommodate for window resizing)
  const ISystem* pSystem = Engine::Get<ISystem>();

  //  Setup display size (every frame to accommodate for window resizing)
  const hdx::float2 WindowSize = pSystem->GetWindowSize();
  io.DisplaySize = ImVec2(WindowSize.x, WindowSize.y);

  //  Setup time step
  io.DeltaTime = pSystem->GetDeltaTime();

  const IKeyboard* pKeyboard = Engine::Get<IKeyboard>();

  //  Read keyboard modifiers inputs
  {
    for (int i = 0; i < 256; ++i)
    {
      io.KeysDown[i] = pKeyboard->Press(i);
    }

    io.KeyCtrl = pKeyboard->Press(VK_CONTROL);
    io.KeyShift = pKeyboard->Press(VK_SHIFT);
    io.KeyAlt = pKeyboard->Press(VK_MENU);
    io.KeySuper = false;
  }

  //  Update OS mouse position
  {
    const IMouse* pMouse = Engine::Get<IMouse>();

    io.MouseDown[0] = pMouse->Press(hdx::Input::Mouse::Buttons::Left);
    io.MouseDown[1] = pMouse->Press(hdx::Input::Mouse::Buttons::Right);
    io.MouseDown[2] = pMouse->Press(hdx::Input::Mouse::Buttons::Middle);
    io.MouseDown[3] = pMouse->Press(hdx::Input::Mouse::Buttons::X1);
    io.MouseDown[4] = pMouse->Press(hdx::Input::Mouse::Buttons::X2);


    const hdx::int2& Wheel = pMouse->GetWheel();
    io.MouseWheel += Wheel.y;
    io.MouseWheelH += Wheel.x;

    // Set mouse position
    io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

    if (::GetActiveWindow() == hWnd_)
    {
      const hdx::float2& MousePos = pMouse->GetPos();
      io.MousePos = ImVec2(MousePos.x, MousePos.y);
    }
  }

  //  Update OS mouse cursor with the cursor requested by imgui
  ImGuiMouseCursor MouseCursor = io.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();
  if (LastMouseCursor_ != MouseCursor)
  {
    LastMouseCursor_ = MouseCursor;

    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
    {
      return;
    }

    // Show OS mouse cursor
    LPTSTR Cursor = IDC_ARROW;
    switch (ImGui::GetMouseCursor())
    {
    case ImGuiMouseCursor_Arrow:      Cursor = IDC_ARROW; break;
    case ImGuiMouseCursor_TextInput:  Cursor = IDC_IBEAM; break;
    case ImGuiMouseCursor_ResizeAll:  Cursor = IDC_SIZEALL; break;
    case ImGuiMouseCursor_ResizeEW:   Cursor = IDC_SIZEWE; break;
    case ImGuiMouseCursor_ResizeNS:   Cursor = IDC_SIZENS; break;
    case ImGuiMouseCursor_ResizeNESW: Cursor = IDC_SIZENESW; break;
    case ImGuiMouseCursor_ResizeNWSE: Cursor = IDC_SIZENWSE; break;
    case ImGuiMouseCursor_Hand:       Cursor = IDC_HAND; break;
    }

    ::SetCursor(::LoadCursor(NULL, Cursor));
  }
}


//--------------------------------------------------

CGUI::DX11::DX11(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext)
  : pDevice_(_pDevice), pImmediateContext_(_pImmediateContext)
  , pVertexShader_(Engine::Get<IVertexShader>()->GetVertexShader(Engine::Get<IVertexShader>()->CreateGUI(pInputLayout_.GetAddressOf())))
  , pPixelShader_(Engine::Get<IPixelShader>()->GetPixeShader(Engine::Get<IPixelShader>()->CreateGUI()))
{
  //  エラーチェック用
  HRESULT hr = S_OK;

  // Create the constant buffer
  {
    D3D11_BUFFER_DESC BufferDesc;
    BufferDesc.ByteWidth = sizeof(VertexConstantBuffer);
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BufferDesc.MiscFlags = 0;

    hr = pDevice_->CreateBuffer(&BufferDesc, nullptr, pVertexConstantBuffer_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  // Create the blending setup
  {
    D3D11_BLEND_DESC BlendDesc{};
    BlendDesc.AlphaToCoverageEnable = false;
    BlendDesc.RenderTarget[0].BlendEnable = true;
    BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    hr = pDevice_->CreateBlendState(&BlendDesc, pBlendState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  // Create the rasterizer state
  {
    D3D11_RASTERIZER_DESC RasterizerDesc{};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    RasterizerDesc.CullMode = D3D11_CULL_NONE;
    RasterizerDesc.ScissorEnable = true;
    RasterizerDesc.DepthClipEnable = true;

    hr = pDevice_->CreateRasterizerState(&RasterizerDesc, pRsterizerState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  // Create depth-stencil State
  {
    D3D11_DEPTH_STENCIL_DESC DepthStencilDesc{};
    DepthStencilDesc.DepthEnable = false;
    DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    DepthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
    DepthStencilDesc.StencilEnable = false;
    DepthStencilDesc.FrontFace.StencilFailOp = DepthStencilDesc.FrontFace.StencilDepthFailOp
      = DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    DepthStencilDesc.BackFace = DepthStencilDesc.FrontFace;

    hr = pDevice_->CreateDepthStencilState(&DepthStencilDesc, pDepthStencilState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  // Create texture sampler
  {
    D3D11_SAMPLER_DESC SamplerDesc{};
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamplerDesc.AddressU = SamplerDesc.AddressV = SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.MipLODBias = 0.f;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    SamplerDesc.MinLOD = 0.f;
    SamplerDesc.MaxLOD = 0.f;

    hr = pDevice_->CreateSamplerState(&SamplerDesc, pSamplerState_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  ImGuiIO& io = ImGui::GetIO();
  // Build texture atlas
  unsigned char* Pixels;
  hdx::int2 Size;
  io.Fonts->GetTexDataAsRGBA32(&Pixels, &Size.x, &Size.y);

  // Upload texture to graphics system
  {
    D3D11_TEXTURE2D_DESC Texture2dDesc{};
    Texture2dDesc.Width = Size.x;
    Texture2dDesc.Height = Size.y;
    Texture2dDesc.MipLevels = 1;
    Texture2dDesc.ArraySize = 1;
    Texture2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    Texture2dDesc.SampleDesc.Count = 1;
    Texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
    Texture2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    Texture2dDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA SubresouceData;
    SubresouceData.pSysMem = Pixels;
    SubresouceData.SysMemPitch = Texture2dDesc.Width * 4;
    SubresouceData.SysMemSlicePitch = 0;

    ID3D11Texture2D* pTexture2d = nullptr;
    hr = pDevice_->CreateTexture2D(&Texture2dDesc, &SubresouceData, &pTexture2d);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResouceViewDesc{};
    ShaderResouceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    ShaderResouceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    ShaderResouceViewDesc.Texture2D.MipLevels = Texture2dDesc.MipLevels;
    ShaderResouceViewDesc.Texture2D.MostDetailedMip = 0;

    hr = pDevice_->CreateShaderResourceView(pTexture2d, &ShaderResouceViewDesc, pFont_.GetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    pTexture2d->Release();
  }

  // Store our identifier
  io.Fonts->TexID = reinterpret_cast<ImTextureID>(pFont_.Get());
}

void CGUI::DX11::Render(ImDrawData* _pDrawData)
{
  //  描画の残りを出力
  {
    Engine::Get<IRenderer2D>()->Flush();
    Engine::Get<IRenderer3D>()->Flush();
  }

  if (_pDrawData->TotalVtxCount <= 0) return;

  //  エラーチェック用
  HRESULT hr = S_OK;

  // Create and grow vertex buffers if needed
  if (!pVertexBuffer_ || VertexBufferSize_ < _pDrawData->TotalVtxCount)
  {
    VertexBufferSize_ = _pDrawData->TotalVtxCount + kVertexBufferExtraSize;

    D3D11_BUFFER_DESC BufferDesc{};
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.ByteWidth = VertexBufferSize_ * sizeof(ImDrawVert);
    BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BufferDesc.MiscFlags = 0;

    hr = pDevice_->CreateBuffer(&BufferDesc, nullptr, pVertexBuffer_.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }
  // Create and grow index buffers if needed
  if (!pIndexBuffer_ || IndexBufferSize_ < _pDrawData->TotalIdxCount)
  {
    IndexBufferSize_ = _pDrawData->TotalIdxCount + kIndexBufferExtraSize;

    D3D11_BUFFER_DESC BufferDesc{};
    BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    BufferDesc.ByteWidth = IndexBufferSize_ * sizeof(ImDrawIdx);
    BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = pDevice_->CreateBuffer(&BufferDesc, nullptr, pIndexBuffer_.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  // Copy and convert all vertices into a single contiguous buffer
  {
    D3D11_MAPPED_SUBRESOURCE VertexResource;
    hr = pImmediateContext_->Map(pVertexBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &VertexResource);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    D3D11_MAPPED_SUBRESOURCE IndexResource;
    hr = pImmediateContext_->Map(pIndexBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &IndexResource);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    ImDrawVert* pVertexData = reinterpret_cast<ImDrawVert*>(VertexResource.pData);
    ImDrawIdx* pIndexData = reinterpret_cast<ImDrawIdx*>(IndexResource.pData);
    for (int n = 0; n < _pDrawData->CmdListsCount; ++n)
    {
      const ImDrawList* pCmdList = _pDrawData->CmdLists[n];
      memcpy(pVertexData, pCmdList->VtxBuffer.Data, pCmdList->VtxBuffer.Size * sizeof(ImDrawVert));
      memcpy(pIndexData, pCmdList->IdxBuffer.Data, pCmdList->IdxBuffer.Size * sizeof(ImDrawIdx));
      pVertexData += pCmdList->VtxBuffer.Size;
      pIndexData += pCmdList->IdxBuffer.Size;
    }
    pImmediateContext_->Unmap(pVertexBuffer_.Get(), 0);
    pImmediateContext_->Unmap(pIndexBuffer_.Get(), 0);
  }

  // Setup orthographic projection matrix into our constant buffer
  // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). 
  {
    D3D11_MAPPED_SUBRESOURCE MappedResource;
    hr = pImmediateContext_->Map(pVertexConstantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    VertexConstantBuffer* pConstantBuffer = reinterpret_cast<VertexConstantBuffer*>(MappedResource.pData);
    float L = _pDrawData->DisplayPos.x;
    float R = _pDrawData->DisplayPos.x + _pDrawData->DisplaySize.x;
    float T = _pDrawData->DisplayPos.y;
    float B = _pDrawData->DisplayPos.y + _pDrawData->DisplaySize.y;

    float mvp[4][4] =
    {
        { 2.0f / (R - L),   0.0f,           0.0f,       0.0f },
        { 0.0f,         2.0f / (T - B),     0.0f,       0.0f },
        { 0.0f,         0.0f,           0.5f,       0.0f },
        { (R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f },
    };
    memcpy(&pConstantBuffer->mvp, mvp, sizeof(mvp));
    pImmediateContext_->Unmap(pVertexConstantBuffer_.Get(), 0);
  }

  // Setup viewport
  {
    D3D11_VIEWPORT vp{};
    vp.Width = _pDrawData->DisplaySize.x;
    vp.Height = _pDrawData->DisplaySize.y;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = vp.TopLeftY = 0;

    pImmediateContext_->RSSetViewports(1, &vp);
  }

  // Bind shader and vertex buffers
  {
    UINT Stride = sizeof(ImDrawVert);
    UINT Offset = 0;
    pImmediateContext_->IASetInputLayout(pInputLayout_.Get());
    pImmediateContext_->IASetVertexBuffers(0, 1, pVertexBuffer_.GetAddressOf(), &Stride, &Offset);
    pImmediateContext_->IASetIndexBuffer(pIndexBuffer_.Get(), sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
    pImmediateContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pImmediateContext_->VSSetShader(pVertexShader_, nullptr, 0);
    pImmediateContext_->VSSetConstantBuffers(0, 1, pVertexConstantBuffer_.GetAddressOf());
    pImmediateContext_->PSSetShader(pPixelShader_, nullptr, 0);
    pImmediateContext_->PSSetSamplers(0, 1, pSamplerState_.GetAddressOf());
  }

  // Setup render state
  {
    const float BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    pImmediateContext_->OMSetBlendState(pBlendState_.Get(), BlendFactor, 0xffffffff);
    pImmediateContext_->OMSetDepthStencilState(pDepthStencilState_.Get(), 0);
    pImmediateContext_->RSSetState(pRsterizerState_.Get());
  }

  // Render command lists
  {
    int VertexOffset = 0;
    int IndexOffset = 0;
    ImVec2 Pos = _pDrawData->DisplayPos;

    for (int n = 0; n < _pDrawData->CmdListsCount; ++n)
    {
      const ImDrawList* pCmdList = _pDrawData->CmdLists[n];
      for (int i = 0; i < pCmdList->CmdBuffer.Size; ++i)
      {
        const ImDrawCmd* pCmd = &pCmdList->CmdBuffer[i];
        if (pCmd->UserCallback)
        {
          // User callback (registered via ImDrawList::AddCallback)
          pCmd->UserCallback(pCmdList, pCmd);
        }
        else
        {
          // Apply scissor/clipping rectangle
          const D3D11_RECT Rect = { static_cast<LONG>(pCmd->ClipRect.x - Pos.x), static_cast<LONG>(pCmd->ClipRect.y - Pos.y),
            static_cast<LONG>(pCmd->ClipRect.z - Pos.x), static_cast<LONG>(pCmd->ClipRect.w - Pos.y) };
          pImmediateContext_->RSSetScissorRects(1, &Rect);

          // Bind texture, Draw
          ID3D11ShaderResourceView* pShaderResouceView = reinterpret_cast<ID3D11ShaderResourceView*>(pCmd->TextureId);
          pImmediateContext_->PSSetShaderResources(0, 1, &pShaderResouceView);
          pImmediateContext_->DrawIndexed(pCmd->ElemCount, IndexOffset, VertexOffset);
        }
        IndexOffset += pCmd->ElemCount;
      }
      VertexOffset += pCmdList->VtxBuffer.Size;
    }
  }
}


//--------------------------------------------------

void CGUI::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext, const HWND& _hWnd)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  pWin32_ = std::make_unique<Win32>(_hWnd);
  pDX11_ = std::make_unique<DX11>(_pDevice, _pImmediateContext);

  pWin32_->NewFrame();
  ImGui::NewFrame();
}

void CGUI::Update()
{
  ImGui::Render();
  pDX11_->Render(ImGui::GetDrawData());

  pWin32_->NewFrame();
  ImGui::NewFrame();
}

CGUI::~CGUI()
{
  ImGui::DestroyContext();
}
