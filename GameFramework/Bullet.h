#pragma once
#include "Object.h"
class Bullet : public Object
{
private:
	int m_fDir;

public:
	Bullet();
	~Bullet();

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	void SetDir(bool _b)
	{
		m_fDir = (_b) ? -1.f : 1.f;
	}
};

