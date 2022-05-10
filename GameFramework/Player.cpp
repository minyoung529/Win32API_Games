#include "Player.h"

Player::Player() :
	Object(FPOINT{}, OBJECTSIZE{}), speed(0.f)
{
	memset(&inputState, 0, sizeof(InputState));
}

Player::Player(FPOINT pos, OBJECTSIZE size, float speed) :
	Object(pos, size),
	speed(speed)
{
}

Player::~Player()
{
}

void Player::Init()
{
	playerImage.Load(TEXT("Data/airplane.bmp"));

	size.width = playerImage.GetBitmapInfo().bmWidth;
	size.height = playerImage.GetBitmapInfo().bmHeight;
}

void Player::Update(float deltaTime)
{
	if (!engine) return;

	engine->Input.KeyCheck(VK_LEFT, inputState.keyLeft);
	engine->Input.KeyCheck(VK_RIGHT, inputState.keyRight);
	engine->Input.KeyCheck(VK_UP, inputState.keyUp);
	engine->Input.KeyCheck(VK_DOWN, inputState.keyDown);
	engine->Input.KeyCheck(VK_SPACE, inputState.KeySpace);

	if (inputState.keyLeft == KEY_DOWN)
		pos.x -= speed * deltaTime;

	if (inputState.keyRight == KEY_DOWN)
		pos.x += speed * deltaTime;

	if (inputState.keyUp == KEY_DOWN)
		pos.y -= speed * deltaTime;

	if (inputState.keyDown == KEY_DOWN)
		pos.y += speed * deltaTime;

	if (inputState.KeySpace == KEY_PUSH)
		CreateBullet();

	UpdateBullet(deltaTime);
}

void Player::Render(HDC hdc, float deltaTime)
{
	playerImage.DrawBitmap(hdc, (int)pos.x, (int)pos.y);
	RenderBullet(hdc, deltaTime);
}

void Player::Release()
{
	playerImage.Release();
	ReleaseBullet();
}

void Player::CreateBullet()
{
	float posX = pos.x + size.width * 0.5f;

	Bullet* bullet = new Bullet(FPOINT{ posX, pos.y }, OBJECTSIZE{}, 400);

	if (bullet)
	{
		bullet->Init();
		bullets.push_back(bullet);
	}
}

void Player::UpdateBullet(float deltaTime)
{
	list<Bullet*>::iterator iter = bullets.begin();

	while (iter != bullets.end())
	{
		(*iter)->Update(deltaTime);

		if (!(*iter)->IsValid() || (*iter)->IsCollision())
		{
			(*iter)->Release();
			delete (*iter);
			bullets.erase(iter++);
		}
		else
			iter++;
	}
}

void Player::RenderBullet(HDC hdc, float deltaTime)
{
	list<Bullet*>::iterator iter = bullets.begin();

	while (iter != bullets.end())
	{
		(*iter)->Render(hdc, deltaTime);
		iter++;
	}
}

void Player::ReleaseBullet()
{
	list<Bullet*>::iterator iter = bullets.begin();

	while (iter != bullets.end())
	{
		(*iter)->Release();
		delete (*iter);
		bullets.erase(iter++);
	}

	bullets.clear();
}