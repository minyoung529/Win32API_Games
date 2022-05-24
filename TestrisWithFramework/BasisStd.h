#ifndef BASIS_STD
#define BASIS_STD

// ----------------------------
// Name : BASIS_STD
// Desc : 기본적으로 사용되는 헤더, 디파인
// ----------------------------

#include <Windows.h>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <ctime>

using namespace std;

#define PI 3.141592654


#define RATIO		30	// 배율
#define GAP			1	// 판 내부 줄 조정 값
#define WINSIZEX	800
#define WINSIZEY	600

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

#endif