#pragma once
class Collider;

union COLLIDER_ID
{
	struct
	{
		UINT left_id;
		UINT right_id;
	};

	ULONGLONG id;
};

class CollisionManager
{
private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];
	map<ULONGLONG, bool> m_mapCollInfo;

public:
	SINGLE(CollisionManager);

private:
	CollisionManager();
	~CollisionManager();

public:
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void CheckReset();
	void CollisionGroupUpdate(GROUP_TYPE row, GROUP_TYPE col);
	
private:
	bool IsCollision(Collider* left, Collider* right);
};

