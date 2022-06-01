#ifndef BASIS_STD
#define BASIS_STD

// ----------------------------
// Name : BASIS_STD
// Desc : �⺻������ ���Ǵ� ���, ������
// ----------------------------

#include <Windows.h>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <ctime>

using namespace std;

#define PI				3.141592654

#define RATIO			30	// ����
#define GAP				1	// �� ���� �� ���� ��

#define BOARDSIZE_X		300 
#define BOARDSIZE_Y		600 

#define MARGIN_ROW		30	// �� ����
#define MARGIN_COLUMN	180 // �� ���� 

#define WINSIZE_X		(BOARDSIZE_X + MARGIN_COLUMN * 2)
#define WINSIZE_Y		(BOARDSIZE_Y + MARGIN_ROW * 2 + 32)

#pragma comment(lib, "winmm.lib")

enum class TAG
{
	NOT,
	PIECE,
	BLOCK
};

enum class PIECE_COLOR
{
	NONE = 0,
	BLUE = 102,
	GRAY,
	GREEN,
	GUIDE,
	ORNAGE,
	PURPLE,
	RED
};

enum class TETRIS_TYPE
{
	I,
	O,
	Z,
	S,
	J,
	L,
	T
};

enum class BLOCK_STATE
{
	PREVIEW,
	HANDLENOW,
	FROZEN
};

#endif // BASISSTD_H