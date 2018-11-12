#include "HDX.hpp"

void Main()
{
  hdx::System::SetWindowSize(1280, 720);
  hdx::System::ShowCursor(false);
  hdx::System::SetTitle("HDXlib");

  hdx::Texture A{ "DATA/exp.png" };

  GetInputState();

  //  hdx::SkinnedMesh Fbx("DATA/FBX/005_cube.fbx");
  //
  //  hdx::float3 Position;
  //  hdx::float3 Rotate;
  //
  //  static constexpr float kScale = 0.75f;
  //  //  拡大・縮小
  //  DirectX::XMMATRIX S = DirectX::XMMatrixScaling(kScale, kScale, kScale);
  //
  //  //  ビュー行列
  //  DirectX::XMMATRIX V;
  //  {
  //    DirectX::XMVECTOR pos = DirectX::XMVectorSet(0, 0, -10.0f, 1.0f);         //  カメラの位置
  //    DirectX::XMVECTOR target = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);  //  カメラの注視点
  //    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);      //  上ベクトル(仮)
  //    V = DirectX::XMMatrixLookAtLH(pos, target, up);
  //  }
  //
  //  //  プロジェクション行列
  //  DirectX::XMMATRIX P;
  //  {
  //    static constexpr float znear = 0.1f;   //  最近面
  //    static constexpr float zfar = 1000.0f; //  再遠面
  //
  //#if 0 //  投影変換行列(平行投影)     
  //    float width = 16.0f / 2.0f; //  投影幅
  //    float height = 9.0f / 2.0f; //  投影高さ
  //    P = DirectX::XMMatrixOrthographicLH(width, height, znear, zfar);
  //#else //  投影変換行列(透視投影)    
  //    float aspect = static_cast<float>(hdx::System::GetWindowWidth()) / hdx::System::GetWindowHeight();  //  アスペクト比
  //    static constexpr float fovY = 30 * 0.01745f;     //  視野角
  //    P = DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, znear, zfar);
  //#endif
  //  }
  //
  //  //  光の向き
  //  DirectX::XMFLOAT4 LightDirection(0.0f, 0.0f, 1.0f, 0.0f);
  //
  //  //  ゲームループ
  //  while (hdx::System::Update())
  //  {
  //    DirectX::XMFLOAT4X4 WordldViewProjection;
  //    DirectX::XMFLOAT4X4 World;
  //    {
  //      //  ワールド行列
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
  //        //  回転
  //        DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(hdx::Math::ToRadian(Rotate.X), hdx::Math::ToRadian(Rotate.Y), hdx::Math::ToRadian(Rotate.Z));
  //        //  平行移動
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

  hdx::RenderTarget RenderTarget(hdx::System::GetWindowSize());

  while (hdx::System::Update())
  {
    //RenderTarget.Clear();
    //
    //hdx::Renderer2D::SetRenderTarget(RenderTarget);

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

    for (int i = 0; i < 300; ++i)
    {
      A.Draw(hdx::int2((i % 50) * 64, (i / 50) * 64), hdx::int2(64, 64));
    }

    //hdx::Renderer2D::RestoreRenderTarget();
    //
    //RenderTarget.Draw();
  }
}
