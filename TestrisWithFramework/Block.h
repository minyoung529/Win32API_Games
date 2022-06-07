#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"
#include "BasisSystem.h"

#define POINTNUM 		4
#define	DELAYTIME		1000

#define HANDLE_POS_X	10
#define HANDLE_POS_Y	2

#define PREVIEW_POS_X	18
#define PREVIEW_POS_Y	2

class Block : public Object
{
public:
	Block();
	Block(TETRIS_TYPE type, BLOCK_STATE state);
	~Block();

public:
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	int  GetGlobalX(const int x) const;
	int  GetGlobalY(const int y) const;

	void InitBlock(TETRIS_TYPE type);

	// 90도 회전
	void RightRotatePiece(LONG& x, LONG& y);
	void RightRotateBlock();
	void LeftRotatePiece(LONG& x, LONG& y);
	void LeftRotateBlock();

	bool IsRightRotateBlock(POINT pt[]);

	// 좌우 충돌
	bool CheckOutOfLeft(const POINT center, const POINT pt[]) const;
	bool CheckOutOfRight(const POINT center, const POINT pt[]) const;

	// 충돌 체크
	bool ReachTheGround(const POINT center) const;
	bool CheckOutOfRange(const POINT center, const POINT pt[]) const;

	// 새로 그리기
	void RemoveBlockMakePiece();

public:
	void SetState(BLOCK_STATE state)
	{
		this->state = state;
	}

	BLOCK_STATE GetState()
	{
		return state;
	}

	void SetType(TETRIS_TYPE type)
	{
		this->type = type;
	}

	TETRIS_TYPE GetType()
	{
		return type;
	}

	void SetCenter(POINT point)
	{
		center = point;
	}

	void SetCenterX(const int x)
	{
		center.x = x;
	}

	void SetCenterY(const int y)
	{
		center.y = y;
	}

private:
	POINT			point[POINTNUM];	// 블럭 상대 위치 좌표
	POINT			center;				// 블럭 중심 좌표
	PIECE_COLOR		color;				// 블럭 색상
	TETRIS_TYPE		type;				// 블럭 타입 (모양)
	BLOCK_STATE		state;				// 블럭 현재 상태

	int				startTime;
	int				delayTime;

	InputState		inputState;			// 블럭 입력 처리 
};
#endif // BLOCK_H