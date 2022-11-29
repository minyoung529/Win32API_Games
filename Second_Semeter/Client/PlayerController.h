#pragma once
#include "MonoBehaviour.h"

class PlayerController : public MonoBehaviour
{
public:
	PlayerController();
	virtual ~PlayerController();

public:
	virtual void Update() override;

private:
	float m_speed = 1.0f;
};

