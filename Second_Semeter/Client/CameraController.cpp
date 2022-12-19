#include "pch.h"
#include "CameraController.h"
#include "Input.h"
#include "Timer.h"
#include "Engine.h"
#include "Transform.h"
#include "SceneManager.h"

CameraController::CameraController()
{
}

CameraController::~CameraController()
{
}

void CameraController::LateUpdate()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	float speed = m_speed;

	if (INPUT->GetButton(KEY_TYPE::LSHIFT))
		speed *= 10;

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * speed * DELTA_TIME;
	GetTransform()->SetLocalPosition(pos);

	
	if (INPUT->GetButton(KEY_TYPE::Q))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.x += DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}
	if (INPUT->GetButton(KEY_TYPE::E))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.x -= DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}
	if (INPUT->GetButton(KEY_TYPE::Z))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.y += DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}
	if (INPUT->GetButton(KEY_TYPE::C))
	{
		Vec3 rot = GetTransform()->GetLocalRotation();
		rot.y -= DELTA_TIME * 0.5f;
		GetTransform()->SetLocalRotation(rot);
	}	

	if (INPUT->GetButtonDown(KEY_TYPE::LBUTTON))
	{
		const POINT& pos = INPUT->GetMousePos();
		shared_ptr<GameObject> obj = GET_SINGLE(SceneManager)->Pick(pos.x, pos.y);
	}
}
