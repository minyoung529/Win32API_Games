#pragma once

class Game
{
public:
	void Init(const WindowInfo& window);
	void Update();
	void Render();
	void Release();

private:
	shared_ptr<class Mesh>		m_mesh;
	shared_ptr<class Shader>	m_shader;

	Transform m_meshTrans;
};

