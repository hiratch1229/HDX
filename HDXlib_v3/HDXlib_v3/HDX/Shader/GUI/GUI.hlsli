struct VS_IN
{
  float2 position : POSITION;
  float2 texcoord : TEXCOORD;
  float4 color : COLOR;
};

struct VS_OUT
{
  float4 pos : SV_POSITION;
  float4 color : COLOR;
  float2 texcoord : TEXCOORD;
};

