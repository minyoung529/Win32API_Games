#ifndef _UTILS_HLSLI_
#define _UTILS_HLSLI_

#include "Params.hlsli"

LightColor CalculateLightColor(int lightIndex, float3 viewNormal, float3 viewPos)
{
	LightColor color = (LightColor)0.0f;
	float3 viewLightDir = (float3) 0.0f;
	float diffuseRatio = 0.0f;
	float specularRatio = 0.0f;
	float distanceRatio = 1.0f;

	// directional light
	if (g_light[lightIndex].lightType == 0)
	{
		// Diffuse (����Ʈ �ڻ���)
		viewLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), matView).xyz);
		diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

		// ���� ����Ʈ
		diffuseRatio = pow((diffuseRatio * 0.5f) + 0.5f, 2);

		// �����̴�
		float step = 10;
		diffuseRatio = ceil(diffuseRatio * step) / step;
	}

	// Specular
	 float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));
	//float3 reflectionDir = reflect(viewLightDir, viewNormal);

	// viewPos > ī�޶� ��Ŀ����� �ڽ��� ��ġ (ī�޶� �ٶ󺸴� ����)
	float3 eyeDir = normalize(viewPos);
	specularRatio = saturate(dot(-eyeDir, reflectionDir));
	specularRatio = pow(specularRatio, 2.f);

	color.diffuse = g_light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
	color.ambient = g_light[lightIndex].color.ambient * distanceRatio;
	color.specular = g_light[lightIndex].color.specular * specularRatio * distanceRatio;

	return color;
}

#endif // _UTILS_HLSLI_