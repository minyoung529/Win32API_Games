#pragma once

class Engine
{
public:
	void Init(const WindowInfo& window);
	void Render();

public:
	void ResizeWindow(int32 width, int32 height);

private:
	WindowInfo	m_window;
};