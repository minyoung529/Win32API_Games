#pragma once
#include "Scene.h"

class Scene_Start :  public Scene
{
public:
	Scene_Start();
	virtual ~Scene_Start() override;

public:
	virtual void Enter() override;
	virtual void Exit() override;
};