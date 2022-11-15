#pragma once
#include "MonoBehaviour.h"

class CameraController: public MonoBehaviour
{
public:
	CameraController();
	virtual ~CameraController();

public:
	virtual void LateUpdate() override;

private:
	float m_speed = 100.f;
};

