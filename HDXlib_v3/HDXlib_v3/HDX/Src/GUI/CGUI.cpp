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
    io.MouseWheel += Wheel.y / WHEEL_DELTA;
    io.MouseWheelH += Wheel.x / WHEEL_DELTA;

    // Set mouse position
    io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);

    if (::GetActiveWindow() == hWnd_)
    {
      const hdx::float2& MousePos = pMouse->GetPos();
      io.MousePos = ImVec2(MousePos.x, MousePos.y);
    }
  }

  //  Update OS mouse cursor with the cursor requested by imgui
  ImGuiMouseCursor mouse_cursor = io.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();
  if (LastMouseCursor_ != mouse_cursor)
  {
    LastMouseCursor_ = mouse_cursor;

    if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
    {
      return;
    }

    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();

    // Show OS mouse cursor
    LPTSTR win32_cursor = IDC_ARROW;
    switch (imgui_cursor)
    {
    case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
    case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
    case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
    case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
    case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
    case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
    case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
    case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
    }
    ::SetCursor(::LoadCursor(NULL, win32_cursor));
  }
}


//--------------------------------------------------

CGUI::DX11::DX11(ID3D11Device* _pDevice, ID3D11DeviceContext* _pImmediateContext)
  : pDevice_(_pDevice), pImmediateContext_(_pImmediateContext)
  , VertexShader_(Engine::Get<IVertexShader>()->CreateGUI(pInputLayout_.GetAddressOf()))
  , PixelShader_(Engine::Get<IPixelShader>()->CreateGUI())
{
  //  エラーチェック用
  HRESULT hr = S_OK;

  Microsoft::WRL::ComPtr<IDXGIDevice> pDevice;
  hr = pDevice_->QueryInterface(IID_PPV_ARGS(pDevice.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
  hr = pDevice->GetParent(IID_PPV_ARGS(pAdapter.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  // Get factory from device
  hr = pAdapter->GetParent(IID_PPV_ARGS(pFactory_.GetAddressOf()));
  _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

  // Create the constant buffer
  {
    D3D11_BUFFER_DESC desc;
    desc.ByteWidth = sizeof(VERTEX_CONSTANT_BUFFER);
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    pDevice_->CreateBuffer(&desc, NULL, pVertexConstantBuffer_.GetAddressOf());
  }

  // Create the blending setup
  {
    D3D11_BLEND_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.AlphaToCoverageEnable = false;
    desc.RenderTarget[0].BlendEnable = true;
    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    pDevice_->CreateBlendState(&desc, pBlendState_.GetAddressOf());
  }

  // Create the rasterizer state
  {
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_NONE;
    desc.ScissorEnable = true;
    desc.DepthClipEnable = true;
    pDevice_->CreateRasterizerState(&desc, pRsterizerState_.GetAddressOf());
  }

  // Create depth-stencil State
  {
    D3D11_DEPTH_STENCIL_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.DepthEnable = false;
    desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
    desc.StencilEnable = false;
    desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    desc.BackFace = desc.FrontFace;
    pDevice_->CreateDepthStencilState(&desc, pDepthStencilState_.GetAddressOf());
  }

  // Create texture sampler
  {
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.MipLODBias = 0.f;
    desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    desc.MinLOD = 0.f;
    desc.MaxLOD = 0.f;
    pDevice_->CreateSamplerState(&desc, pSamplerState_.GetAddressOf());
  }

  ImGuiIO& io = ImGui::GetIO();
  // Build texture atlas
  unsigned char* pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

  // Upload texture to graphics system
  {
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D *pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = pixels;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    pDevice_->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    pDevice_->CreateShaderResourceView(pTexture, &srvDesc, pFont_.GetAddressOf());
    pTexture->Release();
  }

  // Store our identifier
  io.Fonts->TexID = reinterpret_cast<ImTextureID>(pFont_.Get());
}

void CGUI::DX11::Render(ImDrawData* draw_data)
{
  //  描画の残りを出力
  {
    Engine::Get<IRenderer2D>()->Flush();
    Engine::Get<IRenderer3D>()->Flush();
  }

  if (draw_data->TotalVtxCount <= 0) return;

  //  エラーチェック用
  HRESULT hr = S_OK;

  // Create and grow vertex buffers if needed
  if (!pVertexBuffer_ || VertexBufferSize_ < draw_data->TotalVtxCount)
  {
    VertexBufferSize_ = draw_data->TotalVtxCount + 5000;

    D3D11_BUFFER_DESC desc;
    memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = VertexBufferSize_ * sizeof(ImDrawVert);
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;

    hr = pDevice_->CreateBuffer(&desc, nullptr, pVertexBuffer_.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }
  // Create and grow index buffers if needed
  if (!pIndexBuffer_ || IndexBufferSize_ < draw_data->TotalIdxCount)
  {
    IndexBufferSize_ = draw_data->TotalIdxCount + 10000;
    D3D11_BUFFER_DESC desc;
    memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = IndexBufferSize_ * sizeof(ImDrawIdx);
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = pDevice_->CreateBuffer(&desc, nullptr, pIndexBuffer_.ReleaseAndGetAddressOf());
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));
  }

  // Copy and convert all vertices into a single contiguous buffer
  {
    D3D11_MAPPED_SUBRESOURCE vtx_resource, idx_resource;
    hr = pImmediateContext_->Map(pVertexBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &vtx_resource);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    hr = pImmediateContext_->Map(pIndexBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_resource);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource.pData;
    ImDrawIdx* idx_dst = (ImDrawIdx*)idx_resource.pData;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
      const ImDrawList* cmd_list = draw_data->CmdLists[n];
      memcpy(vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
      memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
      vtx_dst += cmd_list->VtxBuffer.Size;
      idx_dst += cmd_list->IdxBuffer.Size;
    }
    pImmediateContext_->Unmap(pVertexBuffer_.Get(), 0);
    pImmediateContext_->Unmap(pIndexBuffer_.Get(), 0);
  }

  // Setup orthographic projection matrix into our constant buffer
  // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). 
  {
    D3D11_MAPPED_SUBRESOURCE mapped_resource;
    hr = pImmediateContext_->Map(pVertexConstantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
    _ASSERT_EXPR(SUCCEEDED(hr), hResultTrace(hr));

    VERTEX_CONSTANT_BUFFER* constant_buffer = (VERTEX_CONSTANT_BUFFER*)mapped_resource.pData;
    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
    float mvp[4][4] =
    {
        { 2.0f / (R - L),   0.0f,           0.0f,       0.0f },
        { 0.0f,         2.0f / (T - B),     0.0f,       0.0f },
        { 0.0f,         0.0f,           0.5f,       0.0f },
        { (R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f },
    };
    memcpy(&constant_buffer->mvp, mvp, sizeof(mvp));
    pImmediateContext_->Unmap(pVertexConstantBuffer_.Get(), 0);
  }

  // Setup viewport
  {
    D3D11_VIEWPORT vp;
    memset(&vp, 0, sizeof(D3D11_VIEWPORT));
    vp.Width = draw_data->DisplaySize.x;
    vp.Height = draw_data->DisplaySize.y;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = vp.TopLeftY = 0;
    pImmediateContext_->RSSetViewports(1, &vp);
  }

  // Bind shader and vertex buffers
  {
    unsigned int stride = sizeof(ImDrawVert);
    unsigned int offset = 0;
    pImmediateContext_->IASetInputLayout(pInputLayout_.Get());
    pImmediateContext_->IASetVertexBuffers(0, 1, pVertexBuffer_.GetAddressOf(), &stride, &offset);
    pImmediateContext_->IASetIndexBuffer(pIndexBuffer_.Get(), sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
    pImmediateContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pImmediateContext_->VSSetShader(Engine::Get<IVertexShader>()->GetVertexShader(VertexShader_), NULL, 0);
    pImmediateContext_->VSSetConstantBuffers(0, 1, pVertexConstantBuffer_.GetAddressOf());
    pImmediateContext_->PSSetShader(Engine::Get<IPixelShader>()->GetPixeShader(PixelShader_), NULL, 0);
    pImmediateContext_->PSSetSamplers(0, 1, pSamplerState_.GetAddressOf());
  }

  // Setup render state
  {
    const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
    pImmediateContext_->OMSetBlendState(pBlendState_.Get(), blend_factor, 0xffffffff);
    pImmediateContext_->OMSetDepthStencilState(pDepthStencilState_.Get(), 0);
    pImmediateContext_->RSSetState(pRsterizerState_.Get());
  }

  // Render command lists
  {
    int vtx_offset = 0;
    int idx_offset = 0;
    ImVec2 pos = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; ++n)
    {
      const ImDrawList* cmd_list = draw_data->CmdLists[n];
      for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; ++cmd_i)
      {
        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
        if (pcmd->UserCallback)
        {
          // User callback (registered via ImDrawList::AddCallback)
          pcmd->UserCallback(cmd_list, pcmd);
        }
        else
        {
          // Apply scissor/clipping rectangle
          const D3D11_RECT r = { (LONG)(pcmd->ClipRect.x - pos.x), (LONG)(pcmd->ClipRect.y - pos.y), (LONG)(pcmd->ClipRect.z - pos.x), (LONG)(pcmd->ClipRect.w - pos.y) };
          pImmediateContext_->RSSetScissorRects(1, &r);

          // Bind texture, Draw
          ID3D11ShaderResourceView* texture_srv = (ID3D11ShaderResourceView*)pcmd->TextureId;
          pImmediateContext_->PSSetShaderResources(0, 1, &texture_srv);
          pImmediateContext_->DrawIndexed(pcmd->ElemCount, idx_offset, vtx_offset);
        }
        idx_offset += pcmd->ElemCount;
      }
      vtx_offset += cmd_list->VtxBuffer.Size;
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
