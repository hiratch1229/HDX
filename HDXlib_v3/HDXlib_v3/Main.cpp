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
    { "DATA/005_cube.fbx" }
  };

  //  hdx::SkinnedMesh Fbx("DATA/FBX/005_cube.fbx");
  //
  //  hdx::float3 Position;
  //  hdx::float3 Rotate;
  //
  //  static constexpr float kScale = 0.75f;
  //  //  �g��E�k��
  //  DirectX::XMMATRIX S = DirectX::XMMatrixScaling(kScale, kScale, kScale);
  //
  //  //  �r���[�s��
  //  DirectX::XMMATRIX V;
  //  {
  //    DirectX::XMVECTOR pos = DirectX::XMVectorSet(0, 0, -10.0f, 1.0f);         //  �J�����̈ʒu
  //    DirectX::XMVECTOR target = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);  //  �J�����̒����_
  //    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);      //  ��x�N�g��(��)
  //    V = DirectX::XMMatrixLookAtLH(pos, target, up);
  //  }
  //
  //  //  �v���W�F�N�V�����s��
  //  DirectX::XMMATRIX P;
  //  {
  //    static constexpr float znear = 0.1f;   //  �ŋߖ�
  //    static constexpr float zfar = 1000.0f; //  �ĉ���
  //
  //#if 0 //  ���e�ϊ��s��(���s���e)     
  //    float width = 16.0f / 2.0f; //  ���e��
  //    float height = 9.0f / 2.0f; //  ���e����
  //    P = DirectX::XMMatrixOrthographicLH(width, height, znear, zfar);
  //#else //  ���e�ϊ��s��(�������e)    
  //    float aspect = static_cast<float>(hdx::System::GetWindowWidth()) / hdx::System::GetWindowHeight();  //  �A�X�y�N�g��
  //    static constexpr float fovY = 30 * 0.01745f;     //  ����p
  //    P = DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, znear, zfar);
  //#endif
  //  }
  //
  //  //  ���̌���
  //  DirectX::XMFLOAT4 LightDirection(0.0f, 0.0f, 1.0f, 0.0f);
  //
  //  //  �Q�[�����[�v
  //  while (hdx::System::Update())
  //  {
  //    DirectX::XMFLOAT4X4 WordldViewProjection;
  //    DirectX::XMFLOAT4X4 World;
  //    {
  //      //  ���[���h�s��
  //      DirectX::XMMATRIX W;
  //      {
  //        if (hdx::Input::Keyboard::KeyW) Rotate.X -= 1.0f;
  //        if (hdx::Input::Keyboard::KeyS) Rotate.X += 1.0f;
  //        if (hdx::Input::Keyboard::KeyA) Rotate.Z -= 1.0f;
  //        if (hdx::Input::Keyboard::KeyD) Rotate.Z += 1.0f;
  //
  //        if (hdx::Input::Keyboard::KeyLeft) Position.X -= 0.1f;
  //        if (hdx::Input::Keyboard::KeyRight) Position.X += 0.1f;
  //        if (hdx::Input::Keyboard::KeyUp) Position.Y += 0.1f;
  //        if (hdx::Input::Keyboard::KeyDown) Position.Y -= 0.1f;
  //
  //        //  ��]
  //        DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(hdx::Math::ToRadian(Rotate.X), hdx::Math::ToRadian(Rotate.Y), hdx::Math::ToRadian(Rotate.Z));
  //        //  ���s�ړ�
  //        DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z);
  //        W = S*R*T;
  //      }
  //
  //      DirectX::XMStoreFloat4x4(&WordldViewProjection, W*V*P);
  //      DirectX::XMStoreFloat4x4(&World, W);
  //    }
  //
  //    //Model.Render(WordldViewProjection, World, LightDirection);
  //    //Cube.Render(WordldViewProjection, World, LightDirection, hdx::Palette::Red);
  //    Fbx.Render(WordldViewProjection, World, LightDirection, 1 / 60.0f, hdx::Palette::White, hdx::Input::Keyboard::KeySpace);
  //  }
  //
  //hdx::RenderTarget RenderTarget(hdx::System::GetWindowSize());

  constexpr hdx::Input::Gamepad Gampads[3] = { 0, 1, 2 };
  constexpr float Scale = 1.0f;

  hdx::Camera Camera;

  int Num = 1;
  hdx::float3 Rotation;
  while (hdx::System::Update())
  {
    //ImGui::Begin("DeltaTime");
    //ImGui::Text("DeltaTime %f", hdx::System::GetDeltaTime());
    //ImGui::SliderInt("��", &Num, 1, 100);
    //ImGui::End();

    //hdx::Renderer3D::SetCamera(Camera);

    //if (hdx::Input::Keyboard::KeyUp)
    //{
    //  Camera.Pos.Y += 0.1f;
    //}
    //if (hdx::Input::Keyboard::KeyDown)
    //{
    //  Camera.Pos.Y -= 0.1f;
    //}
    //if (hdx::Input::Keyboard::KeyLeft)
    //{
    //  Camera.Pos.X -= 0.1f;
    //}
    //if (hdx::Input::Keyboard::KeyRight)
    //{
    //  Camera.Pos.X += 0.1f;
    //}
    //
    //hdx::Renderer3D::SetCamera(Camera);

    Rotation.X += hdx::System::GetDeltaTime()*1.0f;
    Rotation.Y += hdx::System::GetDeltaTime()*0.5f;

    auto WorldMatrix = DirectX::XMMatrixScaling(Scale, Scale, Scale)
      *DirectX::XMMatrixRotationRollPitchYaw(Rotation.X, Rotation.Y, 0.0f)
      *DirectX::XMMatrixTranslation(0.0f, 0.0f, -5.0f);

    for (int i = 0; i < Num; ++i)
      Models[0].Draw(WorldMatrix);

    //A.Draw();

    //Models[0].Draw(
    //  DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f)
    //  *DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f)
    //  *DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f));
    //
    //for (int i = 0; i < 3; ++i)
    //{
    //  const int ButtonNum = Gampads[i].GetButtonNum();
    //
    //  for (int j = 0; j < ButtonNum; ++j)
    //  {
    //    if (Gampads[i].GetButton(j))
    //    {
    //      A.Draw(hdx::int2((i % 50) * 64, (i / 50) * 64), hdx::int2(64, 64));
    //    }
    //  }
    //}
    //
    //RenderTarget.Clear();
    //
    //hdx::Renderer2D::SetRenderTarget(RenderTarget);
    //
    //if (hdx::Input::Keyboard::Key0.Pressed())
    //{
    //  hdx::Renderer2D::SetSamplerState(hdx::SamplerState::Default2D, 0);
    //}
    //else if (hdx::Input::Keyboard::Key1.Pressed())
    //{
    //  static constexpr hdx::SamplerState SamplerState{ hdx::AddressMode::Clamp, hdx::AddressMode::Clamp, hdx::AddressMode::Clamp, hdx::Filter::MinMagMipPoint };
    //  hdx::Renderer2D::SetSamplerState(SamplerState, 0);
    //}
    //else if (hdx::Input::Keyboard::Key2.Pressed())
    //{
    //  static constexpr hdx::SamplerState SamplerState{ hdx::AddressMode::Clamp, hdx::AddressMode::Clamp, hdx::AddressMode::Clamp, hdx::Filter::MinMagMipLinear };
    //  hdx::Renderer2D::SetSamplerState(SamplerState, 0);
    //}
    //
    //for (int i = 0; i < 10000; ++i)
    //{
    //  A.Draw(hdx::int2((i % 50) * 64, (i / 50) * 64), hdx::int2(64, 64));
    //}
    //
    //hdx::Renderer2D::RestoreRenderTarget();
    //
    //RenderTarget.Draw();
  }
}
