#pragma once
#include "Component.h"

class Terrain : public Component
{
public:
	Terrain();
	virtual ~Terrain();

public:
	void Init(int32 sizeX, int32 sizeZ);
	virtual void FinalUpdate() override;

private:
	int32 m_sizeX;
	int32 m_sizeZ;
	float m_maxTesselation = 4.0f;	// 셰이더에서 연산하기 때문에 float

	shared_ptr<class Material> m_material;
};