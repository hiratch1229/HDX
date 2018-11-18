struct VS_IN
{
  float4 position : POSITION;
  float4 color : COLOR;
  float2 texcoord : TEXCOORD;
};

struct VS_OUT
{
  float4 position : SV_POSITION;
  float4 color : COLOR;
  float2 texcoord : TEXCOORD;
};

cbuffer VertexBuffer : register(b0)
{
  float4x4 ProjectionMatrix;
}
