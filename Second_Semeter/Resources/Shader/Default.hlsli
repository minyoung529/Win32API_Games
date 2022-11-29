#ifndef _DEFAULT_HLSLI_
#define _DEFAULT_HLSLI_

#include "Params.hlsli"
#include "Utils.hlsli"

struct VS_IN
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};

struct VS_OUT
{
	float4 pos : SV_Position;
	float2 uv : TEXCOORD;
	float3 viewPos : POSITION;
	float3 viewNormal : NORMAL;
};

VS_OUT VS_Main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.pos = mul(float4(input.pos, 1.f), matWVP);
	output.uv = input.uv;

	// 모든 정점, normal => 같은 space
	output.viewPos = mul(float4(input.pos, 1.0f), matWV).xyz;
	output.viewNormal = normalize(mul(float4(input.normal, 0.f), matWV).xyz);

	return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	// lighting
	LightColor totalColor = (LightColor)0.0f;

	for (int i = 0; i < g_lightCount; i++)
	{
		LightColor color = CalculateLightColor(i, input.viewNormal, input.viewPos);

		totalColor.diffuse += color.diffuse;
		totalColor.ambient += color.ambient;
		totalColor.specular += color.specular;
	}

	color.xyz = (totalColor.diffuse.xyz * color.xyz)
			  + (totalColor.ambient.xyz * color.xyz)
			  + (totalColor.specular.xyz);

	return color;
}

#endif // _DEFAULT_HLSLI_