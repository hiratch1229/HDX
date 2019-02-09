#include "GUI.hlsli"

cbuffer VertexBuffer : register(b0)
{
  float4x4 ProjectionMatrix;
};

VS_OUT main(VS_IN In)
{
  VS_OUT vout;
  vout.pos = mul(ProjectionMatrix, float4(In.position.xy, 0.0f, 1.0f));
  vout.color = In.color;
  vout.texcoord = In.texcoord;

  return vout;
}
