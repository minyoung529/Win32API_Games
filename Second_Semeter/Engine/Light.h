#pragma once
#include "Component.h"

enum class LIGHT_TYPE : uint8
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

struct LightColor
{
	Vec4 diffuse;
	Vec4 ambient;
	Vec4 specular;
};

// 쉐이더 데이터는 16바이트 배수로 처리(padding처리)
struct LightInfo
{
	LightColor	color;
	Vec4		position;
	Vec4		direction;
	int32		lightType;
	float		range;
	float		angle;
	int32		padding;
};

struct LightParams
{
	uint32		lightCount;
	Vec3		padding;
	LightInfo	lights[50];
};

class Light : public Component
{
public:
	Light();
	virtual ~Light();

	virtual void FinalUpdate() override;

public:
	const LightInfo& GetLightInfo() { return m_lightInfo; }

	void SetLightDirection(const Vec3& direction) { m_lightInfo.direction = direction; }

	void SetAmbient(const Vec3& ambient) { m_lightInfo.color.ambient = ambient; }
	void SetDiffuse(const Vec3& diffuse) { m_lightInfo.color.diffuse = diffuse; }
	void SetSpecular(const Vec3 & specular) { m_lightInfo.color.specular = specular; }

	void SetLightType(LIGHT_TYPE type) { m_lightInfo.lightType = static_cast<int32>(type); }
	void SetLightRange(float range) { m_lightInfo.range = range; }
	void SetLightAngle(float angle) { m_lightInfo.angle = angle; }

private:
	LightInfo	m_lightInfo = {};
};

