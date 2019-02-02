struct VS_IN
{
  float4 position : POSITION;
  float2 texcoord : TEXCOORD;
  column_major float4x4 ndc_transform : NDC_TRANSFORM;
  float4 texcoord_transform : TEXCOORD_TRANSFORM;
  float4 color : COLOR;
};

struct VS_OUT
{
  float4 pos : SV_POSITION;
  float4 color : COLOR;
  float2 texcoord : TEXCOORD;
};
