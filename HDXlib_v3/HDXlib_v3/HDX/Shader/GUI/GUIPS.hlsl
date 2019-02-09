#include "GUI.hlsli"

sampler Sampler;
Texture2D Texture;

float4 main(VS_OUT In) : SV_TARGET
{
  return In.color * Texture.Sample(Sampler, In.texcoord);
}
