#ifndef	  BINPUT_H
#define	  BINPUT_H

#include "BBasisStd.h"

enum keyState{
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_DOWN,
	KEY_HOLD
};

struct TInputState
{
	DWORD		dwKeyUP;
	DWORD		dwKeyDOWN;
	DWORD		dwKeyLEFT;
	DWORD		dwKeyRIGHT;
	DWORD		dwKeySpace;
	DWORD		dwKeyW;
	DWORD		dwKeyA;
	DWORD		dwKeyS;
	DWORD		dwKeyD;
	DWORD		dwMouseLB;
	DWORD		dwMouseRB;
	DWORD		dwKeyM;
};

class BInput
{
public:
	BInput();
	~BInput();

private:
	BOOL			m_IsKey;
	BYTE			m_byKey[256];
	BYTE			m_byOldKey[256];

public:
	void			Init();
	void			Update();
	void			Release();

	void			KeyCheck(DWORD dwCheckKey, DWORD& dwStateKey);
	int				ScanToASCII(DWORD scancode, WORD* result);
};
#endif // BINPUT_H