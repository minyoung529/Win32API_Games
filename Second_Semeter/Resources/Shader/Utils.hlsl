#ifndef _UTILS_HLSLI_
#define _UTILS_HLSLI_

#include "Params.hlsl"

LightColor CalculateLightColor(int lightIndex, float3 viewNormal, float3 viewPos)
{
    LightColor color = (LightColor) 0.0f;
    float3 viewLightDir = (float3) 0.0f;
    float diffuseRatio = 0.0f;
    float specularRatio = 0.0f;
    float distanceRatio = 1.0f;

    if (g_light[lightIndex].lightType == 0)	// Directional light
    {
		// Diffuse (����Ʈ �ڻ���)
        viewLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), matView).xyz);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

		// ���� ����Ʈ
        diffuseRatio = pow((diffuseRatio * 0.5f) + 0.5f, 2);

		// �����̴�
		//float step = 3;
		//diffuseRatio = ceil(diffuseRatio * step) / step;
    }
    else if (g_light[lightIndex].lightType == 1)	// Point Light
    {
		// ����Ʈ CC ��ġ�� ī�޶� �������� ��ȯ
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.0f), matView).xyz;
        viewLightDir = normalize(viewPos - viewLightPos);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        float dist = distance(viewPos, viewLightPos);

        if (g_light[lightIndex].range == 0.f)
        {
            distanceRatio = 0.f;
        }
        else
        {
            distanceRatio = saturate(1.f - pow(dist / g_light[lightIndex].range, 2));
        }
    }
    else // spot light
    {
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.0f), matView);
        viewLightDir = normalize(viewPos - viewLightPos);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
	
        if (g_light[lightIndex].range == 0.f)
        {
            distanceRatio = 0.f;
        }
        else
        {
            float halfAngle = g_light[lightIndex].angle / 2;
            float3 viewLightVec = viewPos - viewLightPos;
            
            // �������� ���ϱ� 0.f�� �ִ´� 
            float3 viewCenterLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), matView).xyz);
            
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            distanceRatio = saturate(1.f - centerDist / g_light[lightIndex].range);
            
            float lightAngle = acos(dot(normalize(viewLightDir), viewCenterLightDir));
            
            if(centerDist < 0.f || centerDist > g_light[lightIndex].range)
            {
                distanceRatio = 0.f;
            }
            else if(lightAngle > halfAngle)
            {
                distanceRatio = 0.f;
            }
            else
            {
                distanceRatio = saturate(1.f - pow(centerDist / g_light[lightIndex].range, 15));
            }
        }
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

