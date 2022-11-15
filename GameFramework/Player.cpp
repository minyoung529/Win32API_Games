#include "pch.h"
#include "Player.h"
#include "Define.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Bullet.h"

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