#include "HDX/Shader/Model/Model.hlsli"
#include "HDX/Shader/Model/Bone.hlsli"
#include "HDX/Shader/Model/Light.hlsli"

cbuffer ConstantBuffer : register(b1)
{
  DirectionalLight DLight;
}

VS_OUT main(VS_IN In)
{
  Bone BoneInfluence;
  BoneInfluence.Position = float3(0.0f, 0.0f, 0.0f);
  BoneInfluence.Normal = float3(0.0f, 0.0f, 0.0f);

  for (int i = 0; i < 4; ++i)
  {
    Bone Temp = Calc(In.Position, In.Normal, BoneTransforms[In.BoneIndices[i]], In.BoneWeights[i]);
    BoneInfluence.Position += Temp.Position;
    BoneInfluence.Normal += Temp.Normal;
  }
  
  In.Position = float4(BoneInfluence.Position, 1.0f);
  In.Normal = float4(BoneInfluence.Normal, 0.0f);

  VS_OUT Out;

  const float4 World = mul(In.Position, mul(In.World, GlobalTransform));

  Out.World = World.xyz;
  Out.Position = mul(World, ViewProjectionMatrix);
  Out.Texcoord = In.Texcoord;
  Out.Normal = normalize(mul(In.Normal, In.World)).xyz;

  Out.Color = In.MaterialColor * DiffuseColor * DLight.Calc(Out.Normal)*0.5f;
  Out.Color.a = In.MaterialColor.a * DiffuseColor.a;

  return Out;
}
