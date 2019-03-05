#include "HDX.hpp"
#include <memory>

class ITest
{
public:
  ITest() = default;

  virtual ~ITest() = default;

  virtual void Update(float _DeltaTime) = 0;
};

class Test1 : public ITest
{
  struct Charactor
  {
    const hdx::Model Model;
  public:
    hdx::float3 Position;
    hdx::float3 Rotation;
    hdx::float3 Scalling;
    hdx::MotionData MotionData;
  public:
    Charactor(const hdx::Model& _Model) : Model(_Model) { }

    void Draw(bool _isMotion)const
    {
      const hdx::Matrix World = DirectX::XMMatrixScaling(Scalling.x, Scalling.y, Scalling.z)
        * DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z)
        * DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);

      (_isMotion) ? Model.Draw(World, MotionData) : Model.Draw(World);
    }
  };
private:
  Charactor Danbo_ = { "DATA/Model/danbo_fbx/danbo_atk.fbx" };
private:
  hdx::Model Floor_ = hdx::Rectangle{};
private:
  hdx::VertexShader VertexShader_ = { "DATA/Shader/LightTestVS.cso" };
  hdx::PixelShader PixelShader_ = { "DATA/Shader/LightTestPS.cso" };
private:
  hdx::ConstantBuffer<hdx::DirectionalLight> DirectionalLight_;
  hdx::ConstantBuffer<hdx::PointLight> PointLight_;
  hdx::ConstantBuffer<hdx::SpotLight> SpotLight_;
public:
  Test1()
  {
    //  DirectionalLight
    {
      hdx::DirectionalLight& Light = DirectionalLight_.Get();

      Light.Direction = hdx::float3(0.0f, -1.0f, 0.0f);
      Light.Itensity = 1.0f;
      Light.Color = hdx::Palette::White;
    }

    //  PointLight
    {
      hdx::PointLight& Light = PointLight_.Get();

      Light.Position = hdx::float3(0.0f, 1.0f, 0.0f);
      Light.Itensity = 1.0f;
      Light.Color = hdx::Palette::Yellow;
      Light.Range = 1.5f;
    }

    //  SpotLight
    {
      hdx::SpotLight& Light = SpotLight_.Get();

      Light.Position = hdx::float3(0.0f, 1.5f, 0.0f);
      Light.Direction = hdx::float3(0.0f, -1.0f, 0.0f);
      Light.Itensity = 1.0f;
      Light.Color = hdx::Palette::Red;
      Light.Range = 2.5f;
      Light.Angle = hdx::Math::ToRadian(60.0f);
    }

    Danbo_.Position = 0.0f;
    Danbo_.Rotation = hdx::float3(0.0f, hdx::Math::ToRadian(180.0f), 0.0f);
    Danbo_.Scalling = 0.01f;
    Danbo_.MotionData = { 0.0f, 0 };
  }

  void Update(float _DeltaTime)override
  {
    hdx::Renderer3D::SetVertexShader(VertexShader_);
    hdx::Renderer3D::SetPixelShader(PixelShader_);

    hdx::Renderer3D::SetConstantBuffer(DirectionalLight_, 1, hdx::ShaderStage::Vertex);
    hdx::Renderer3D::SetConstantBuffer(PointLight_, 1, hdx::ShaderStage::Pixel);
    hdx::Renderer3D::SetConstantBuffer(SpotLight_, 2, hdx::ShaderStage::Pixel);

    hdx::Renderer3D::FreeCamera();

    ImGui::Begin("DirectionalLight");
    {
      hdx::DirectionalLight& Light = DirectionalLight_.Get();

      float Direction[3] = { Light.Direction.x, Light.Direction.y, Light.Direction.z };
      ImGui::InputFloat3("Direction", Direction);
      Light.Direction = hdx::float3(Direction[0], Direction[1], Direction[2]);

      ImGui::InputFloat("Itensity", &Light.Itensity);

      float Color[3] = { Light.Color.R, Light.Color.G, Light.Color.B };
      ImGui::ColorPicker3("Color", Color);
      Light.Color = hdx::ColorF(Color[0], Color[1], Color[2], Light.Color.A);
    }
    ImGui::End();

    ImGui::Begin("PointLight");
    {
      hdx::PointLight& Light = PointLight_.Get();

      float Position[3] = { Light.Position.x, Light.Position.y, Light.Position.z };
      ImGui::InputFloat3("Position", Position);
      Light.Position = hdx::float3(Position[0], Position[1], Position[2]);

      ImGui::InputFloat("Itensity", &Light.Itensity);

      ImGui::InputFloat("Range", &Light.Range);

      float Color[3] = { Light.Color.R, Light.Color.G, Light.Color.B };
      ImGui::ColorPicker3("Color", Color);
      Light.Color = hdx::ColorF(Color[0], Color[1], Color[2], Light.Color.A);
    }
    ImGui::End();

    ImGui::Begin("SpotLight");
    {
      hdx::SpotLight& Light = SpotLight_.Get();

      float Position[3] = { Light.Position.x, Light.Position.y, Light.Position.z };
      ImGui::InputFloat3("Position", Position);
      Light.Position = hdx::float3(Position[0], Position[1], Position[2]);

      float Direction[3] = { Light.Direction.x, Light.Direction.y, Light.Direction.z };
      ImGui::InputFloat3("Direction", Direction);
      Light.Direction = hdx::float3(Direction[0], Direction[1], Direction[2]);

      ImGui::InputFloat("Itensity", &Light.Itensity);

      ImGui::InputFloat("Range", &Light.Range);

      ImGui::SliderFloat("Angle", reinterpret_cast<float*>(&Light.Angle), 0.0f, hdx::Math::ToRadian(180.0f));

      float Color[3] = { Light.Color.R, Light.Color.G, Light.Color.B };
      ImGui::ColorPicker3("Color", Color);
      Light.Color = hdx::ColorF(Color[0], Color[1], Color[2], Light.Color.A);
    }
    ImGui::End();

    ImGui::Begin("Danbo");
    {
      float Position[3] = { Danbo_.Position.x, Danbo_.Position.y, Danbo_.Position.z };
      ImGui::InputFloat3("Position", Position);
      Danbo_.Position = hdx::float3(Position[0], Position[1], Position[2]);

      float Rotation[3] = { Danbo_.Rotation.x, Danbo_.Rotation.y, Danbo_.Rotation.z };
      ImGui::InputFloat3("Rotation", Rotation);
      Danbo_.Rotation = hdx::float3(Rotation[0], Rotation[1], Rotation[2]);

      float Scalling[3] = { Danbo_.Scalling.x, Danbo_.Scalling.y, Danbo_.Scalling.z };
      ImGui::InputFloat3("Scalling", Scalling);
      Danbo_.Scalling = hdx::float3(Scalling[0], Scalling[1], Scalling[2]);
    }
    ImGui::End();
    Danbo_.Model.Update(_DeltaTime, &Danbo_.MotionData);
    Danbo_.Draw(true);

    Floor_.Draw(DirectX::XMMatrixScaling(5.0f, 5.0f, 5.0f)
      * DirectX::XMMatrixRotationX(hdx::Math::ToRadian(90.0f)));
    Floor_.Draw(DirectX::XMMatrixScaling(5.0f, 5.0f, 5.0f)
      * DirectX::XMMatrixTranslation(0.0f, 2.5f, 2.5f));
  }
};

void Main()
{
  hdx::System::SetWindowSize(1280, 720);
  hdx::System::ShowCursor(true);
  hdx::System::SetTitle("HDXlib");
  hdx::System::SetFPS(0);

  std::unique_ptr<ITest> pTest;
  pTest = std::make_unique<Test1>();

  while (hdx::System::Update())
  {
    const int FPS = hdx::System::GetFPS();
    const float DeltaTime = hdx::System::GetDeltaTime();
    ImGui::Begin("DeltaTime");
    {
      ImGui::Text("DeltaTime %f", DeltaTime);
      ImGui::Text("FPS:%d", FPS);
    }
    ImGui::End();

    pTest->Update(DeltaTime);
  }
}
