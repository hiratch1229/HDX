#include "HDX/Shader/Model/Model.hlsli"
#include "HDX/Shader/Model/Light.hlsli"

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseMapSamplerState : register(s0);

cbuffer ConstantBuffer : register(b1)
{
  PointLight PLight;
}

cbuffer ConstantBuffer : register(b2)
{
  SpotLight SLight;
}

float4 main(VS_OUT _In) : SV_TARGET
{
  float4 Color = 0.0f;

  Color += PLight.Calc(_In.World, _In.Normal);
  Color += SLight.Calc(_In.World, _In.Normal);

  float4 DiffuseColor = DiffuseMap.Sample(DiffuseMapSamplerState, _In.Texcoord) * _In.Color;

  Color += DiffuseColor;
  Color.a = DiffuseColor.a;

  return Color;
}
