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

	Vec3 rot = GetTransform()->GetLocalRotation();

	if (INPUT->GetButton(KEY_TYPE::Q))
		rot.y += DELTA_TIME * 0.5f;

	if (INPUT->GetButton(KEY_TYPE::E))
		rot.y -= DELTA_TIME * 0.5f;

	GetTransform()->SetLocalRotation(rot);
}
