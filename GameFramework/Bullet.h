#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	float m_ftheta;
	Vector2 m_vDir;

public:
	Bullet();
	~Bullet();

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	void SetDir(float theta)
	{
		m_ftheta = theta;
	}

	void SetDir(Vector2 dir)
	{
		m_vDir = dir;
		m_vDir.Normalize();
	}
};

