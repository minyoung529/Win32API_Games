#ifndef BASIS_STD
#define BASIS_STD

// --------------------------------------
// Desc : 기본적으로 사용되는 헤더, 디파인
// --------------------------------------

#include <Windows.h>
#include <math.h>
#include <string>// Name : BASIS_STD

#include <map>
#include <list>
#include <vector>

#define SCREEN_WIDTH	960
#define SCREEN_HEIGHT	720

#define PI	3.141592

#define SAFE_DELETE(p){ if(p) { delete(p); (p) = nullptr; }}

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

enum STAGE
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE_COUNT
};

#endif