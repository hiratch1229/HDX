#include "HDX.hpp"

void Main()
{
  hdx::System::SetWindowSize(1280, 720);
  hdx::System::ShowCursor(true);
  hdx::System::SetTitle("HDXlib");
  hdx::System::SetFPS(0);

  hdx::Model Models[] = {
    //{ hdx::Cube{} },
    //{ "DATA/Model/motion.fbx" },
    //{ "DATA/Model/Mr.Incredible/Mr.Incredible.obj" },
    { "DATA/Model/danbo_fbx/danbo_atk.fbx" },
  };

  constexpr float Scale = 0.01f;

  hdx::Camera Camera;

  int MaxNum = 100;
  int Num = 1;

  hdx::float3 Rotation{ hdx::Math::ToRadian(0.0f), hdx::Math::ToRadian(180.0f), 0.0f };
  hdx::Matrix WorldMatrix;
  hdx::MotionData MotionData;
  const hdx::Matrix S = DirectX::XMMatrixScaling(Scale, Scale, Scale);

  while (hdx::System::Update())
  {
    ImGui::Begin("DeltaTime");
    ImGui::Text("DeltaTime %f", hdx::System::GetDeltaTime());
    ImGui::Text("FPS:%d", hdx::System::GetFPS());

    ImGui::InputInt("ç≈ëÂêî", &MaxNum);
    ImGui::SliderInt("ëÃ", &Num, 1, MaxNum);
    ImGui::End();

    //Rotation.X += hdx::System::GetDeltaTime()*1.0f;
    //Rotation.Y += hdx::System::GetDeltaTime()*0.5f;

    WorldMatrix = S
      * DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z)
      * DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < Num; ++i)
    {
      //Models[0].Update(hdx::System::GetDeltaTime(), &MotionData);
      Models[0].Draw(WorldMatrix/*, MotionData*/);
    }
  }
}
