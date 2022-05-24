#ifndef SCENE_H
#define SCENE_H

#include "BasisStd.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

public:
	virtual		void Init() = 0;
	virtual		void Update(float deltaTime) = 0;
	virtual		void Render(HDC hdc, float deltaTime) = 0;
	virtual		void Release() = 0;
};

#endif