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
	void _RenderText(UINT fps, float deltaTime);

public:
	virtual void	Init();
	virtual void	Update(float deltaTime);
	virtual void	Render(HDC hdc, float deltaTime);
	virtual void	Release();

private:
	LARGE_INTEGER	prevCount;
	LARGE_INTEGER	curCount;
	LARGE_INTEGER	frequency;

	float			deltaTime;	// 프레임간 시간 값
	float			accumulate;		// 누적 시간
	UINT			callCount;
	UINT			fps;

public: 
	Input			Input;
	BSound			Sound;
	SceneManager*	mSceneManager;
};

#endif