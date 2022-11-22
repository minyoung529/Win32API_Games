#include "pch.h"
#include "CameraController.h"
#include "Input.h"
#include "Engine.h"
#include "Transform.h"
#include "Timer.h"

CameraController::CameraController()
{
}

CameraController::~CameraController()
{
}

void CameraController::LateUpdate()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * m_speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * m_speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * m_speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * m_speed * DELTA_TIME;

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
}
