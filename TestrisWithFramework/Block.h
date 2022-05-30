#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"
#include "BasisSystem.h"

#define POINTNUM 	4
#define	DELAYTIME	1000

class Block : public Object
{
private:
	POINT			point[POINTNUM];	// ��� ��� ��ġ ��ǥ
	POINT			center;				// ��� �߽� ��ǥ
	PIECE_COLOR		color;				// ��� ����
	TETRIS_TYPE		type;				// ��� Ÿ�� (���)

	int				startTime;
	int				delayTime;

	InputState		inputState;			// �� �Է� ó�� 

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