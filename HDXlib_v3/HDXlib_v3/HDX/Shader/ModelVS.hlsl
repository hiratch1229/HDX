#include "Model.hlsli"

VS_OUT main(VS_IN In)
{
    float3 p = { 0, 0, 0 };
    float3 n = { 0, 0, 0 };
    for (int i = 0; i < 4; ++i)
    {
        row_major float4x4 BoneTransform = BoneTransforms[In.BoneIndices[i]];

        p += (In.BoneWeights[i] * mul(In.Position, BoneTransform)).xyz;
        n += (In.BoneWeights[i] * mul(float4(In.Normal.xyz, 0), BoneTransform)).xyz;
    }

    In.Position = float4(p, 1.0f);
    In.Normal = float4(n, 0.0f);

    VS_OUT Out;
       
    Out.Position = mul(In.Position, mul(In.World, ViewProjectionMatrix));
    Out.Texcoord = In.Texcoord;

    In.Normal.w = 0;
    float4 N = normalize(mul(In.Normal, In.World));
    float4 L = normalize(-LightDirection);

    Out.Color = In.MaterialColor * max(0.2f, dot(L, N));
    Out.Color.a = In.MaterialColor.a;

    return Out;

    //VS_OUT Out;
       
    //Out.Position = mul(In.Position, mul(In.World, ViewProjectionMatrix));
    //Out.Texcoord = In.Texcoord;

    //In.Normal.w = 0;
    //float4 N = normalize(mul(In.Normal, In.World));
    //float4 L = normalize(-LightDirection);

    //Out.Color = In.MaterialColor * max(0.2f, dot(L, N));
    //Out.Color.a = In.MaterialColor.a;

    //return Out;
}
