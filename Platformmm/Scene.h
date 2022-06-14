#ifndef	  CSCENE_H
#define	  CSCENE_H

#include "BBasisStd.h"

class CScene
{
public:
	CScene() = default;
	virtual ~CScene() = default;

public:
	virtual					void Init() = 0;
	virtual					void Update(float dt) = 0;
	virtual					void Render(HDC hdc, float dt) = 0;
	virtual					void Release() = 0;
};
#endif // CSCENE_H