#include "MonsterManager.h"
#include "KingPig.h"

MonsterManager::MonsterManager()
{
	instanceID = 0;
	player = nullptr;
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Init()
{
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		monsters[i]->Init();
	}
}

void MonsterManager::Update(float deltaTime)
{
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		if (monsters[i]->IsDead())
		{
			monsters[i]->Release();
			delete monsters[i];
			monsters.erase(monsters.begin() + i);
		}
		else
		{
			monsters[i]->Update(deltaTime);
		}
	}
}

void MonsterManager::Render(HDC hdc)
{
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		monsters[i]->Render(hdc);
	}
}

void MonsterManager::Release()
{
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		monsters[i]->Release();
		delete monsters[i];
		monsters.erase(monsters.begin() + i);
	}
}

void MonsterManager::SetPlayer(Player* player)
{
	this->player = player;

	for (size_t i = 0; i < monsters.size(); ++i)
	{
		monsters[i]->SetPlayer(player);
	}
}

void MonsterManager::RegisterMonster(MONSTER_TYPE type, FPOINT pos)
{
	Monster* monster = nullptr;

	switch (type)
	{
	case KING_PIG:
		monster = new KingPig(type, pos, 20.f);
		break;
	}

	if (monster)
	{
		monsters.push_back(monster);
		monster->SetId(instanceID++);
	}
}

void MonsterManager::RemoveMonster(int id)
{
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		if (monsters[i]->GetID() == id)
		{
			monsters[i]->SetIsDead(true);
		}
	}
}

void MonsterManager::ClearMonster()
{
	for (size_t i = 0; i < monsters.size(); ++i)
	{
		monsters[i]->Release();
		delete monsters[i];
		monsters.erase(monsters.begin() + i);
	}

	monsters.clear();
}
