#pragma once
#include "Object.h"

class Player :  public Object
{
public:
	virtual void Update() override;

private:
	void CreateBullet();
};

