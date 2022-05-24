#include "Player.h"

Player::Player() :
	Object(FPOINT{}, OBJECTSIZE{}), speed(0.f), rect{}, maxHp(100.f), hpRect{}
{
	hp = maxHp;
	memset(&inputState, 0, sizeof(InputState));
}

Player::Player(FPOINT pos, OBJECTSIZE size, float speed) :
	Object(pos, size),
	speed(speed),
	maxHp(100.f),
	rect{},
	hpRect{}
{
	hp = maxHp;
	memset(&inputState, 0, sizeof(InputState));
}

Player::Player(FPOINT pos, OBJECTSIZE size, float speed, float scale) :
	Object(pos, size),
	speed(speed),
	maxHp(100.f),
	rect{},
	hpRect{}
{
	hp = maxHp;
	this->scale = scale;
	memset(&inputState, 0, sizeof(InputState));
}

Player::~Player()
{
}

void Player::Init()
{
	hp = maxHp;

	playerImage.Load(TEXT("Data/airplane.bmp"));

	size.width = playerImage.GetBitmapInfo().bmWidth;
	size.height = playerImage.GetBitmapInfo().bmHeight;

	rect.left = pos.x;
	rect.right = pos.x + size.width * scale;
	rect.top = pos.y;
	rect.bottom = pos.y + size.height * scale;

	hpRect.left = pos.x;
	hpRect.right = pos.x + size.width * scale;

	hpRect.top = pos.y - 20.f + size.width * scale;
	hpRect.bottom = pos.y + size.width * scale;
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

	rect.left = pos.x;
	rect.right = pos.x + (int)(size.width * scale);
	rect.top = pos.y;
	rect.bottom = pos.y + (int)(size.height * scale);

	float right = (hp / maxHp) * (int)(size.width * scale);
	hpRect.left = pos.x;
	hpRect.right = pos.x + (int)right;

	if (hpRect.right < pos.x)
		hpRect.right = pos.x;

	hpRect.top = pos.y - 10.f + (int)(size.width * scale);
	hpRect.bottom = pos.y + (int)(size.width * scale);

	UpdateBullet(deltaTime);
}

void Player::Render(HDC hdc, float deltaTime)
{
	playerImage.DrawBitmap(hdc, (int)pos.x, (int)pos.y, size.width * scale, size.height * scale);

	RenderBullet(hdc, deltaTime);

	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, hpRect.left, hpRect.top, hpRect.right, hpRect.bottom);
	DeleteObject(brush);
}

void Player::Release()
{
	playerImage.Release();
	ReleaseBullet();
}

void Player::CreateBullet()
{
	float posX = pos.x + size.width * 0.5f * scale;

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