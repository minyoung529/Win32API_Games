#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	score = 0;
	isGameOver = false;
	instanceID = 0;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Init()
{
	// size_t => objectList.size()의 반환형 맞춘다

	for (size_t i = 0; i < objectList.size(); ++i)
	{
		objectList[i]->Init();
	}
}

void ObjectManager::Update(float deltaTime)
{
	for (size_t i = 0; i < objectList.size(); ++i)
		objectList[i]->Update(deltaTime);
}

void ObjectManager::Render(HDC hdc)
{
	for (size_t i = 0; i < objectList.size(); ++i)
		objectList[i]->Render(hdc);
}

void ObjectManager::Release()
{
	for (size_t i = 0; i < objectList.size(); ++i)
		objectList[i]->Release();
}

void ObjectManager::RegisterObject(Object* object)
{
	object->SetId(instanceID++);
	objectList.push_back(object);
}

void ObjectManager::RemoveObject(int id)
{
	for (size_t i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetId() == id)
		{
			objectList.erase(objectList.begin() + i);
			break;
		}
	}
}

void ObjectManager::CreatePrevBlock()
{
	TETRIS_TYPE random = static_cast<TETRIS_TYPE>(rand() % 7);
	Block* block = new Block(random, BLOCK_STATE::PREVIEW);

	RegisterObject(block);
}

void ObjectManager::CreateGameBlock()
{
	TETRIS_TYPE random = static_cast<TETRIS_TYPE>(rand() % 7);
	Block* block = new Block(random, BLOCK_STATE::HANDLENOW);

	RegisterObject(block);
}

bool ObjectManager::CheckOverlapWithPiece(const POINT center, const POINT pt[]) const
{
	vector<Object*> pieces;

	for (size_t i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetTag() == TAG::PIECE)
		{
			pieces.push_back(objectList[i]);
		}
	}

	for (size_t i = 0; i < pieces.size(); ++i)
	{
		for (int j = 0; j < POINTNUM; ++j)
		{
			Piece* piece = dynamic_cast<Piece*>(pieces[i]);
			if (piece->GetPos().x == center.x + pt[j].x &&
				piece->GetPos().y == center.y + pt[j].y)
			{
				return true;
			}
		}
	}

	return false;
}