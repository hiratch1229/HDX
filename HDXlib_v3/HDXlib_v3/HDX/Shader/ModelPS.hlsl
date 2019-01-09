#include "Model.hlsli"

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseMapSamplerState : register(s0);

float4 main(VS_OUT In) : SV_TARGET
{
    return DiffuseMap.Sample(DiffuseMapSamplerState, In.Texcoord) * In.Color;
}
