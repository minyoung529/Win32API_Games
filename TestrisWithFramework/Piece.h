#ifndef PIECE_H
#define PIECE_H

#include "Object.h"

class Piece : public Object
{
private:
	POINT position;
	PIECE_COLOR color;

public:
	Piece();
	Piece(POINT pos, PIECE_COLOR color);
	~Piece();

public:
	POINT GetPos() const
	{
		return position;
	}
	void SetPos(POINT pos)
	{
		position = pos;
	}

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

#endif