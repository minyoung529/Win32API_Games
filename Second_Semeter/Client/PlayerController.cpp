#include "pch.h"
#include "PlayerController.h"
#include "Transform.h"
#include "engine.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update()
{
	Vec3 pos = GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos.y += m_speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::S))
		pos.y -= m_speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::A))
		pos.x -= m_speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::D))
		pos.x += m_speed * DELTA_TIME;

	GetTransform()->SetPosition(pos);
}