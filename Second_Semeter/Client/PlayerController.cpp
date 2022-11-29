#include "pch.h"
#include "PlayerController.h"
#include "Transform.h"
#include "Engine.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (INPUT->GetButton(KEY_TYPE::UP))
		pos.y += m_speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::DOWN))
		pos.y -= m_speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::LEFT))
		pos.x -= m_speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::RIGHT))
		pos.x += m_speed * DELTA_TIME;

	GetTransform()->SetLocalPosition(pos);
}
