#ifndef OBJECT_H
#define OBJECT_H

#include "BasisStd.h"

class Object
{
private:
	int id;
	TAG tag;

public:
	Object()
		: id(-1)
		, tag(TAG::NOT)
	{}

	Object(TAG tag)
		: id(-1)
		, tag(tag)
	{}

	virtual ~Object() {}

public:
	virtual void Init() {}
	virtual void Update(float deltaTime) {}
	virtual void Render(HDC hdc) {}
	virtual void Release() {}


	void SetId(int _id) { id = _id; }
	int GetId() { return id; }

	void SetTag(TAG _tag) { tag = _tag; }
	TAG GetTag() { return tag; }

};
#endif