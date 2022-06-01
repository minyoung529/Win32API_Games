#pragma once
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Singleton.h"
#include "Piece.h"
#include "Block.h"

class ObjectManager : public Singleton<ObjectManager>
{
private:
	int		score;
	bool	isGameOver;
	int		instanceID;
	vector<Object*> objectList;

public:
	ObjectManager();
	~ObjectManager();

public:
	void Init();
	void Update(float deltaTime);
	void Render(HDC hdc);
	void Release();

public:
	void SetScore(int score)
	{
		this->score = score;
	}

	int GetScore() { return score; }

	int GetObjectSize() { return objectList.size(); }

	bool GetGameOver() { return isGameOver; }

	void SetGameOver(bool gameOver)
	{
		isGameOver = gameOver;
	}

	vector<Object*> GetGameObjectList()
	{
		return objectList;
	}

public:
	void RegisterObject(Object* object);
	void RemoveObject(int id);

	void CreatePrevBlock();
	void CreateGameBlock();

	bool CheckOverlapWithPiece(const POINT center, const POINT pt[]) const;
};

#endif // OBJECTMANAGER_H