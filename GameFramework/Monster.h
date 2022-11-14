#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	~Monster();

private:
	float m_fSpeed;
	float m_fMaxDistance;
	float m_fDir;
	Vector2 m_vCenterPos;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float speed) { m_fSpeed = speed; }
	void SetCenterPosition(Vector2 pos) { m_vCenterPos = pos; }
	void SetMoveDistance(float distance) { m_fMaxDistance = distance; }


public:
	virtual void Update() override;
};

