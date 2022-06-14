#include "Animation.h"

Animation::Animation()
	: frameNum(0)
	, frameHeight(0.f)
	, frameWidth(0.f)
	, isLoop(false)
	, frameUpdateSec(0.f)
	, elapsedSec(0.f)
	, curPlayIndex(0)
	, isPlay(false)
{
}

Animation::~Animation()
{
}

void Animation::Init(int totalW, int totalH, int frameW, int frameH)
{
	// 애니메이션 가로 사이즈
	frameWidth = frameW;
	frameHeight = frameH;

	int frameNumWidth = totalW / frameW;
	int frameNumHeight = totalH / frameH;

	frameNum = frameNumWidth * frameNumHeight;

	for (int i = 0; i < frameNumHeight; ++i)
	{
		for (int j = 0; j < frameNumWidth; ++j)
		{
			POINT framePos = {0,0};

			framePos.x += j * frameWidth;
			framePos.y += i * frameHeight;

			frameList.push_back(framePos);
		}
	}
}

void Animation::Release()
{
}

void Animation::SetDefinePlayFrame(bool reverse, bool loop)
{
	playList.clear();
	isLoop = loop;

	if (reverse)
	{

	}
}

void Animation::SetPlayFrame(int start, int end, bool reverse, bool loop)
{
	isLoop = loop;
	playList.clear();

	if (start > end)
	{
		if (reverse)
		{
			for (int i = start; i >= end; --i)
				playList.push_back(i);
		}
		else
		{
			for (int i = end; i <= start; ++i)
				playList.push_back(i);
		}
	}
	else
	{
		if (reverse)
		{
			for (int i = end; i >= start; --i)
				playList.push_back(i);
		}
		else
		{
			for (int i = start; i <= end; ++i)
				playList.push_back(i);
		}
	}
}

void Animation::SetFPS(int framePerSec)
{
	frameUpdateSec = 1.f / framePerSec;
}

void Animation::FrameUpdate(float deltaTime)
{
	if (isPlay)
	{
		elapsedSec += deltaTime;

		if (elapsedSec >= frameUpdateSec)
		{
			elapsedSec -= frameUpdateSec;

			curPlayIndex++;

			if (curPlayIndex == playList.size())
			{
				if (isLoop)
					curPlayIndex = 0;
				
				else
				{
					--curPlayIndex;
					isPlay = false;
				}
			}
		}
	}
}

void Animation::Start()
{
	isPlay = true;
	curPlayIndex = 0;
}

void Animation::Stop()
{
	isPlay = false;
	curPlayIndex = 0;
}

void Animation::Pause()
{
	isPlay = false;
}

void Animation::Resume()
{
	isPlay = true;
}