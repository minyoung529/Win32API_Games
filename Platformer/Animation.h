#ifndef ANIMATION_H
#define ANIMATION_H

#include "BasisStd.h"

class Animation
{
public:
	Animation();
	~Animation();

public:
	void Init(int totalW, int otalH, int frameW, int frameH);
	void Release();

	void SetDefinePlayFrame(bool reverse = false, bool loop = false);
	void SetPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	void SetFPS(int framePerSec);

	void FrameUpdate(float deltaTime);

	void Start();
	void Stop();
	void Pause();
	void Resume();

public:
	inline bool IsPlay() { return isPlay; }
	inline POINT GetFramePos() { return frameList[playList[curPlayIndex]]; }
	inline int GetFrameWidth() { return frameWidth; }
	inline int GetFrameHeight() { return frameHeight; }
	

private:
	vector<POINT> frameList;	// 애니메이션 프레임 저장용
	vector<int> playList;		// 애니메이션 플레이 인덱스 저장용

	int frameNum;				// 애니메이션 프레임 개수
	int frameWidth;				// 프레임 가로크기
	int frameHeight;			// 프레임 세로크기

	float frameUpdateSec;		// 프레임 경과 시간
	float elapsedSec;			// 델타 타임

	DWORD curPlayIndex;			// 현재 플레이 인덱스
	bool isPlay;				// 애니메이션 재생 여부
	bool isLoop;				// 애니메이션 루프 여부 
};
#endif // ANIMATION_H