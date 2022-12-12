#ifndef _SKYBOX_HLSLI_
#define _SKYBOX_HLSLI_

#include "Params.hlsl"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;
    
    float4 viewPos = mul(float4(input.pos, 0), matView);
    float4 clipSpacePos = mul(viewPos, matProjection);
    
    // 프로젝션 행렬 
    // w로 모두 나누는데 (z == 1)이어야 하므로 z = w
    output.pos = clipSpacePos.xyww;
    output.uv = input.uv;
    
    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = tex_0.Sample(sam_0, input.uv);
    return color;
}

#endif // _SKYBOX_HLSLI_