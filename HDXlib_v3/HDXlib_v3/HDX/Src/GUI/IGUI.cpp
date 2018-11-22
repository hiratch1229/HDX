#include "IGUI.hpp"

#include "../Engine.hpp"
#include "../System/ISystem.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include <Windows.h>

//IGUI::IGUI()
//{
//  Engine::Start("GUI");
//
//  //hdx::InputElementDesc InputElementDescs[] =
//  //{
//  //  { "POSITION", 0, hdx::Format::R32G32_FLOAT, 0, hdx::AppendAlignedElement, hdx::InputClassification::PER_VERTEX_DATA, 0 },
//  //  { "COLOR", 0, hdx::Format::R32G32B32A32_FLOAT, 0, hdx::AppendAlignedElement, hdx::InputClassification::PER_VERTEX_DATA, 0 },
//  //  { "TEXCOORD", 0, hdx::Format::R32G32_FLOAT, 0, hdx::AppendAlignedElement, hdx::InputClassification::PER_VERTEX_DATA, 0 },
//  //};
//
//  //VertexShader = { "GUIVS.cso", InputElementDescs, ARRAY_SIZE(InputElementDescs) };
//  //PixelShader = { "GUIPS.cso" };
//
//  //IMGUI_CHECKVERSION();
//  //ImGui::CreateContext();
//  //ImGuiIO& IO = ImGui::GetIO();
//  //IO.ImeWindowHandle = ::GetActiveWindow();
//
//  ////  Setup Style
//  //ImGui::StyleColorsDark();
//
//  Engine::End("GUI");
//}

void IGUI::Initialize()
{
  ISystem* pSystem = Engine::Get<ISystem>();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui_ImplWin32_Init(pSystem->GethWnd());
  ImGui_ImplDX11_Init(pSystem->GetDevice(), pSystem->GetImmediateContext());

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

void IGUI::Update()
{
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();
}

IGUI::~IGUI()
{
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}