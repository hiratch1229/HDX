#define MAX_BONES 32
struct VS_IN
{
    float4 Position : POSITION;
    float4 Normal : NORMAL;
    float2 Texcoord : TEXCOORD;
    float4 BoneWeights : WEIGHTS;
    uint4 BoneIndices : BONES;

    row_major float4x4 World : WORLD;
    float4 MaterialColor : COLOR;
};

struct VS_OUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 Texcoord : TEXCOORD;
};

cbuffer CONSTANT_BUFFER : register(b0)
{
    row_major float4x4 ViewProjectionMatrix;
    row_major float4x4 GlobalTransform;
    float4 LightDirection;
    float4 DiffuseColor;

    row_major float4x4 BoneTransforms[MAX_BONES];
};
