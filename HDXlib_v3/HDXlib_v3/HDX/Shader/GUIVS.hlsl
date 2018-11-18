#include "GUI.hlsli"

VS_OUT main(VS_IN vin)
{
  VS_OUT vout;
  vout.position = mul(float4(vin.position.xy, 0.0f, 1.0f), ProjectionMatrix);
  vout.color = vin.color;
  vout.texcoord = vin.texcoord;

  return vout;
}
