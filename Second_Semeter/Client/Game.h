#pragma once

class Game
{
public:
	void Init(const WindowInfo& window);
	void Update();
	void Render();
	void Release();

private:
	shared_ptr<class Mesh>		mesh;
	shared_ptr<class Shader>	shader;

	Transform meshTransform;
};