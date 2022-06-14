
#ifndef OBJECT_H
#define OBJECT_H

#include "BasisStd.h"

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

protected: 
	FPOINT		pos;
	OBJSIZE		size;
	float		scale;

public:
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(HDC hdc, float deltaTime) = 0;
	virtual void Release() = 0;

protected:
	Object(FPOINT pos, OBJSIZE size) : pos(pos), size(size), scale(1.0f) {}
	Object(FPOINT pos, OBJSIZE size, float scale) : pos(pos), size(size), scale(scale) {}
};

#endif