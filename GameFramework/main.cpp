#include "framework.h"
#include "GameFramework.h"
#include "pch.h"
#include "BWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	BWindow window;
	window.Run(hInstance, lpCmdLine, nCmdShow);
}