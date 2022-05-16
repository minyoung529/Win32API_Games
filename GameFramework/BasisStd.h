#ifndef BASIS_STD
#define BASIS_STD

// ----------------------------
// Name : BASIS_STD
// Desc : 기본적으로 사용되는 헤더, 디파인
// ----------------------------

#include <Windows.h>
#include <math.h>
#include <string>
#include <ctime>

#include <map>
#include <vector>
#include <list>

#define PI 3.141592654
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	900

#pragma comment(lib, "winmm.lib")

using namespace std;

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

typedef struct tagOBJECTSIZE
{
	float width;
	float height;
} OBJECTSIZE;

enum class BULLET_TYPE
{
	NORMAL = 0,
	FOLLOW,
	BARRAGE
};
#endif