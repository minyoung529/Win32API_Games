// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#define PI					3.141592
#define DEG2RAD				PI/180

#define HOUR_COLOR			RGB(243,97,166)
#define MINUTE_COLOR		RGB(107,102,255)
#define SECOND_COLOR		RGB(47,157,39)

#define CIRCLE_COLOR		RGB(255,216,216)
#define GRADUATION_COLOR	RGB(95,0,255)
#define STROKE_COLOR		RGB(0,0,66)

#define SOUND_COLOR			RGB(250,237,125)

#define MAX_LOADSTRING		100


#define SECOND_TIMER		1
#define RENDER_TIMER		2		