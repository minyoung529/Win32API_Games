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
	vector<POINT> frameList;	// �ִϸ��̼� ������ �����
	vector<int> playList;		// �ִϸ��̼� �÷��� �ε��� �����

	int frameNum;				// �ִϸ��̼� ������ ����
	int frameWidth;				// ������ ����ũ��
	int frameHeight;			// ������ ����ũ��

	float frameUpdateSec;		// ������ ��� �ð�
	float elapsedSec;			// ��Ÿ Ÿ��

	DWORD curPlayIndex;			// ���� �÷��� �ε���
	bool isPlay;				// �ִϸ��̼� ��� ����
	bool isLoop;				// �ִϸ��̼� ���� ���� 
};
#endif // ANIMATION_H