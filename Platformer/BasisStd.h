#ifndef BASIS_STD
#define BASIS_STD

// ----------------------------
// Desc : 기본적으로 사용되는 헤더, 디파인
// ----------------------------

#include <Windows.h>
#include <math.h>
#include <string>// Name : BASIS_STD

#include <map>
#include <list>
#include <vector>

#define SCREEN_WIDTH	960
#define SCREEN_HEIGHT	720

#define PI	3.141592

using namespace std;

typedef struct tagFPOINT
{
	float x;
	float y;
}FPOINT;

typedef struct tagOBJSIZE
{
	int width;
	int height;
}OBJSIZE;

#endif