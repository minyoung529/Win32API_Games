#pragma once

#include "BBasisSys.h"

class Sample : public BEngine
{
public:
	Sample();
	~Sample();

public:
	virtual void			Init() override;
	virtual void			Update(float dt) override;
	virtual void			Render(HDC hdc, float dt) override;
	virtual void			Release() override;
};