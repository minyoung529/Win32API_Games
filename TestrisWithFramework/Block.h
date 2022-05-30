#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"
#include "BasisSystem.h"

#define POINTNUM 	4
#define	DELAYTIME	1000

class Block : public Object
{
private:
	POINT			point[POINTNUM];	// 블록 상대 위치 좌표
	POINT			center;				// 블록 중심 좌표
	PIECE_COLOR		color;				// 블록 색상
	TETRIS_TYPE		type;				// 블록 타입 (모양)

	int				startTime;
	int				delayTime;

	InputState		inputState;			// 블럭 입력 처리 

public:
	Block();
	Block(TETRIS_TYPE type);
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

	// 90
	void RightRotatePiece(LONG& x, LONG& y);
	void RightRotateBlock();
	void LeftRotatePiece(LONG& x, LONG& y);
	void LeftRotateBlock();
};
#endif // BLOCK_H