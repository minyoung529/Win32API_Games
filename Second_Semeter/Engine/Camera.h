#pragma once
#include "Component.h"

enum class PROJECTION_TYPE
{
	PERSPECTIVE,	// 원근 투영
	ORTHOGRAPHIC	// 직교 투영
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

public:
	virtual void FinalUpdate() override;

private:
	PROJECTION_TYPE m_type = PROJECTION_TYPE::PERSPECTIVE;
	
	float m_near = 1.f;
	float m_far = 1000.f;

	float m_fov = XM_PI / 4.f;
	float m_scale = 1.f;

	Matrix m_matView = {};
	Matrix m_matProjection = {};

public:
	static Matrix s_matView;
	static Matrix s_matProjection;
};

