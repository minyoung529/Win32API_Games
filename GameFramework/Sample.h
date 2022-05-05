
#include"Engine.h"

class Sample : public Engine
{
public:
	Sample();
	~Sample();

public:
	virtual void Init()								override;
	virtual void Update(float deltaTime)			override;
	virtual void Render(HDC hdc, float deltaTime)	override;
	virtual void Release()							override;

private:
	Image bitmapFile;
	InputState inputState;

private:
	int posX;
	int posY;
	int moveSpeed;
};