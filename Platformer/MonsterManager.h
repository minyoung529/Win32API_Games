#ifndef MONSTERMANAGER_H
#define MONSTERMNAGER_H

#include "Singleton.h"
#include "Monster.h"

class MonsterManager : public Singleton<MonsterManager>
{
public:
	MonsterManager();
	~MonsterManager();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Release();

public:
	void SetPlayer(Player* player);

public:
	void RegisterMonster(MONSTER_TYPE type, FPOINT pos);
	void RemoveMonster(int id);
	void ClearMonster();

	vector<Monster*>& GetMonsters() { return monsters; }

private:
	int instanceID;
	Player* player;

	vector<Monster*> monsters;
};
#endif