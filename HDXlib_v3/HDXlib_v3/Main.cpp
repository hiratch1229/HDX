#include "HDX.hpp"

void Main()
{
  hdx::System::SetWindowSize(1280, 720);
  hdx::System::ShowCursor(true);
  hdx::System::SetTitle("HDXlib");

  hdx::Texture A{ "DATA/exp.png" };

  hdx::Model Models[] = {
    //{ hdx::Cube{} },
    //{ "DATA/Mr.Incredible/Mr.Incredible.obj" },
    //{ "DATA/000_cube.fbx" },
    //{ "DATA/001_cube.fbx" },
    //{ "DATA/005_cube.fbx" },
    { "DATA/danbo_fbx/danbo_atk.fbx" },
  };

  constexpr hdx::Input::Gamepad Gampads[3] = { 0, 1, 2 };
  constexpr float Scale = 1.0f;

  hdx::Camera Camera;
  hdx::RenderTarget RenderTarget(hdx::System::GetWindowSize() * 5);
  hdx::ConstantBuffer<hdx::Camera> C;

  hdx::Renderer3D::SetConstantBuffer(C, 1);

  int Num = 1;
  hdx::float3 Rotation;

  while (hdx::System::Update())
  {
    ImGui::Begin("DeltaTime");
    ImGui::Text("DeltaTime %f", hdx::System::GetDeltaTime());
    ImGui::Text("FPS:%d", hdx::System::GetFPS());
    ImGui::SliderInt("‘Ì", &Num, 1, 100);
    ImGui::End();

    RenderTarget.Clear();
    hdx::Renderer3D::SetRenderTarget(RenderTarget);

    Rotation.X += hdx::System::GetDeltaTime()*1.0f;
    Rotation.Y += hdx::System::GetDeltaTime()*0.5f;

    auto WorldMatrix = DirectX::XMMatrixScaling(Scale, Scale, Scale)
      *DirectX::XMMatrixRotationRollPitchYaw(Rotation.X, Rotation.Y, 0.0f)
      *DirectX::XMMatrixTranslation(0.0f, 0.0f, -5.0f);

    for (int i = 0; i < Num; ++i)
      Models[0].Draw(WorldMatrix);

    hdx::Renderer3D::RestoreRenderTarget();

    RenderTarget.Draw();

    A.Draw();
  }
}
