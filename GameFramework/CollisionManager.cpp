#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	for (UINT row = 0; row < (UINT)GROUP_TYPE::END; row++)
	{
		for (UINT col = row; col < (UINT)GROUP_TYPE::END; col++)
		{
			if (m_arrCheck[row] & (1 << col))
			{
				CollisionGroupUpdate((GROUP_TYPE)row, (GROUP_TYPE)col);
			}
		}
	}
}

void CollisionManager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 반만 쓴다! 
	// 작은 값을 행으로, 큰 값은 열(비트)로

	UINT row = (UINT)_eLeft;
	UINT col = (UINT)_eRight;

	if (col < row)
		swap(col, row);

	// 체크가 이미 되어있다면
	if (m_arrCheck[row] &= (1 << col))
	{
		m_arrCheck[row] &= ~(1 << col);
	}
	else
	{
		m_arrCheck[row] != (1 << col);
	}
}

void CollisionManager::CheckReset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}

void CollisionManager::CollisionGroupUpdate(GROUP_TYPE left, GROUP_TYPE right)
{
	Scene* pCurScne = SceneManager::GetInst()->GetCurScene();
	const vector<Object*>& vecLeft = pCurScne->GetGroupObject(left);
	const vector<Object*>& vecRight = pCurScne->GetGroupObject(right);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecLeft.size(); j++)
		{
			if (vecRight[i]->GetCollider() == nullptr
				|| vecLeft[i] == vecRight[j]) // 자기 자신 충돌
				continue;

			Collider* pLeftCol = vecLeft[i]->GetCollider();
			Collider* pRightCol = vecRight[i]->GetCollider();

			COLLIDER_ID id;
			id.left_id = pLeftCol->GetID();
			id.right_id = pRightCol->GetID();

			iter = m_mapCollInfo.find(id.id);

			// 충돌한 적 X
			if (iter == m_mapCollInfo.end())
			{
				m_mapCollInfo.insert({ id.id, false });
				iter = m_mapCollInfo.find(id.id);
			}

			// 충돌
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중
				if (iter->second)
				{
					pLeftCol->StayCollision(pRightCol);
					pRightCol->StayCollision(pLeftCol);
				}
				// 이전 충돌 X
				else
				{
					pLeftCol->EnterCollision(pRightCol);
					pRightCol->EnterCollision(pLeftCol);
					iter->second = true;
				}
			}
			else
			{
				if (iter->second)
				{
					pLeftCol->ExitCollision(pRightCol);
					pRightCol->ExitCollision(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* left, Collider* right)
{
	Vector2 leftPos = left->GetFinalPos();
	Vector2 rightPos = right->GetFinalPos();

	Vector2 leftScale = left->GetScale();
	Vector2 rightScale = right->GetScale();

	if (abs(rightPos.x - leftPos.x) < (leftScale.x + rightScale.x) / 2.f
	 && abs(rightPos.y - leftPos.y) < (leftScale.y + rightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}
