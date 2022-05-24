#include "BasisStd.h"

#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

protected:
	FPOINT		pos;
	OBJECTSIZE	size;
	float		scale;

public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hdc, float deltaTime) = 0;
	virtual void Release() = 0;

protected:
	Object(FPOINT pos, OBJECTSIZE size) : pos(pos), size(size), scale(1.0f){}
	Object(FPOINT pos, OBJECTSIZE size, float scale) : pos(pos), size(size), scale(scale){}
};

#endif