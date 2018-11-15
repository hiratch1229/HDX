struct VS_IN
{
  float4 position : POSITION;
  float4 normal : NORMAL;
  float2 texcoord : TEXCOORD;
  float4 BoneWeights : WEIGHTS;
  uint4 BoneIndices : BONES;
};

struct VS_OUT
{
  float4 position : SV_POSITION;
  float4 color : COLOR;
  float2 texcoord : TEXCOORD;
};

#define MAX_BONES 4
cbuffer CONSTANT_BUFFER : register(b0)
{
  row_major float4x4 world_view_projection;
  row_major float4x4 world;
  float4 material_color;
  float4 light_direction;

  row_major float4x4 bone_transforms[MAX_BONES];
};
