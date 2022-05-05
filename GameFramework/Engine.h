#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Image.h"
#include "Input.h"
#include "Sound.h"
#include "SceneManager.h"

class Engine : public Window
{
public:
	Engine();
	~Engine();

public:
	virtual void StartUp()	override;
	virtual void MainLoop()	override;
	virtual void Cleanup()	override;

private:
	void _Update(float deltaTime);
	void _Render(HDC hdc, float deltaTime);
	void _RenderText(float deltaTime);

public:
	virtual void	Init();
	virtual void	Update(float deltaTime);
	virtual void	Render(HDC hdc, float deltaTime);
	virtual void	Release();

private:
	float			interval;
	float			lastTime;
	float			currentTime;

public: 
	Input			Input;
	BSound			Sound;
	SceneManager*	mSceneManager;
};

#endif