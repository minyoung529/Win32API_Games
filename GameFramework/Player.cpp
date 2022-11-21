#include "pch.h"
#include "Player.h"
#include "Define.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Bullet.h"
#include "Image.h"
#include "PathManager.h"

Player::Player()
	: m_pImage(nullptr)
{
	// Image �ε�
	wstring strFilePath = PathManager::GetInst()->GetResPath();
	strFilePath += L"Image\\planem.bmp";

	m_pImage = new Image();
	m_pImage->Load(strFilePath);
}

Player::~Player()
{
	if (m_pImage)
	{
		delete m_pImage;
	}
}

void Player::Update()
{
	Vector2 position = GetPos();

	if (KEY_HOLD(KEY::LEFT))
	{
		position.x -= 100.f * DT;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		position.x += 100.f * DT;
	}

	if (KEY_HOLD(KEY::UP))
	{
		position.y -= 100.f * DT;
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		position.y += 100.f * DT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateBullet();
	}


	SetPos(position);
}

void Player::Render(HDC hdc)
{
	int width = (int)m_pImage->GetWidth();
	int height = (int)m_pImage->GetHeight();
	Vector2 pos = GetPos();

	/*
	BitBlt
	(
		hdc,
		(int)(pos.x - (float)(width / 2)),
		(int)(pos.y - (float)(height / 2)),
		width, height,
		m_pImage->GetDC(),
		0, 0, SRCCOPY
	);
	*/

	TransparentBlt
	(
		hdc,
		(int)(pos.x - (float)(width / 2)),
		(int)(pos.y - (float)(height / 2)),
		width, height,
		m_pImage->GetDC(),
		0, 0, width, height, RGB(255, 0, 255)
	);
}

void Player::CreateBullet()
{
	Vector2 vBulletPos = GetPos();
	vBulletPos.y -= GetScale().y / 2.f;

	Bullet* pBullet = new Bullet;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vector2(25.f, 25.f));
	pBullet->SetDir(Vector2(-1.f, -7.f));

	Scene* curScene = SceneManager::GetInst()->GetCurScene();
	curScene->AddObject(pBullet, GROUP_TYPE::BULLET);
}