#include "Fbx.hlsli"

VS_OUT main(VS_IN vin)
{
  float3 p = { 0,0,0 };
  float3 n = { 0,0,0 };
  for (int i = 0; i < 4; ++i)
  {
    row_major float4x4 bone_transform = bone_transforms[vin.BoneIndices[i]];

    p += (vin.BoneWeights[i] * mul(vin.position, bone_transform)).xyz;
    n += (vin.BoneWeights[i] * mul(float4(vin.normal.xyz, 0), bone_transform)).xyz;
  }

  vin.position = float4(p, 1.0f);
  vin.normal = float4(n, 0.0f);

  VS_OUT vout;
  vout.position = mul(vin.position, world_view_projection);
  vout.texcoord = vin.texcoord;

  vin.normal.w = 0;
  float4 N = normalize(mul(vin.normal, world));
  float4 L = normalize(-light_direction);

  vout.color = material_color * max(0.8f, dot(L, N));
  vout.color.a = material_color.a;

  //float4 Influence = { 0,0,0,1 };
  //for (int i = 0; i < 4; ++i)
  //{
  //  float Weight = vin.BoneWeights[i];
  //  if (Weight > 0.0f)
  //  {
  //    switch (vin.BoneIndices[i])
  //    {
  //    case 0: Influence.r = Weight; break;
  //    case 1: Influence.g = Weight; break;
  //    case 2: Influence.b = Weight; break;
  //    }
  //  }
  //}
  //
  //vout.color = Influence;

  return vout;
}
