#pragma once

#define PI					3.141592	
#define DEG2RAD				PI/180			// degree to radian

#define HOUR_COLOR			RGB(243,97,166)	// 시침(버튼) 색상
#define MINUTE_COLOR		RGB(107,102,255)// 분침(버튼) 색상
#define SECOND_COLOR		RGB(47,157,39)	// 초침(버튼) 색상

#define CIRCLE_COLOR		RGB(255,216,216)// 원 색상
#define GRADUATION_COLOR	RGB(95,0,255)	// 눈금 색상
#define STROKE_COLOR		RGB(0,0,66)		// 시계 테두리 색상

#define SOUND_COLOR			RGB(250,237,125)// 사운드 버튼 색상

#define TIMER_DEFAULT		1				// 0.06초에 한번씩 돌아가는 타이머 코드
#define TIMER_SECOND		2				// 1초에 한번씩 돌아가는 타이머 코드

#define SCREEN_WIDTH		400				// 화면 가로
#define SCREEN_HEIGHT		550				// 화면 새로

// 상태 온오프 플래그 (비트마스크)
#define	HOUR				1
#define	MINUTE				2
#define	SECOND				4
#define	SOUND				8

