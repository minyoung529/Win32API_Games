#ifndef CAMERA_H
#define CAMERA_H

#include "BasisStd.h"

typedef struct tagCameraInfo
{
	float x;
	float y;

	int width;		// 보여질 영역 가로 크기
	int height;		// 보여질 영역 세로 크기

	int backWidth;		// 배경 이미지 가로
	int backHeight;		// 배경 이미지 세로
}CAMERA_INFO;

class Camera
{
public:
	Camera();
	~Camera();

public:
	void Init(int width, int height, int backWidth, int backHeight);
	void Release();

	bool CheckCameraX();
	bool CheckCameraY();

	void CameraShake();

	void SetX(float x) { pCameraInfo->x = x; }
	float GetX() { return pCameraInfo->x; }

	void SetPos(float x, float y) { pCameraInfo->x = x; pCameraInfo->y = y; }

	void SetY(float y) { pCameraInfo->y = y; }
	float GetY() { return pCameraInfo->y; }

	void SetWidth(int width) { pCameraInfo->width = width; }
	int GetWidth() { return pCameraInfo->width; }

	void SetHeight(int height) { pCameraInfo->height = height; }
	int GetHeight() { return pCameraInfo->height; }

	void SetBackWidth(int backWidth) { pCameraInfo->backWidth = backWidth; }
	int GetBackWidth() { return  pCameraInfo->backWidth; }

	void SetBackHeight(int backHeight) { pCameraInfo->backHeight = backHeight; }
	int GetBackHeight() { return  pCameraInfo->backHeight; }

	int GetLeft()
	{
		if (!CheckCameraX())
		{
			return (pCameraInfo->x <= pCameraInfo->backWidth / 2) ?
				0 : pCameraInfo->backWidth - pCameraInfo->width;
		}

		return (int)pCameraInfo->x - pCameraInfo->width / 2;
	}

	int GetTop()
	{
		if (!CheckCameraY())
		{
			return (pCameraInfo->y <= pCameraInfo->backHeight / 2) ?
				0 : pCameraInfo->backHeight - pCameraInfo->height;
		}

		return (int)pCameraInfo->y - pCameraInfo->height / 2;
	}

	RECT GetRect()
	{
		RECT rc =
		{
			(int)pCameraInfo->x - pCameraInfo->width / 2,
			(int)pCameraInfo->y - pCameraInfo->height / 2,
			(int)pCameraInfo->x + pCameraInfo->width / 2,
			(int)pCameraInfo->y + pCameraInfo->height / 2
		};

		return rc;
	}

	void SetIsShaking(bool isShaking)
	{
		this->isShaking = isShaking;
		shakeAmount = (isShaking) ? 6.0f : 0.0f;
	}

	bool GetIsShaking() { return isShaking; }

	float GetShakeNumber() { return shakeAmount * flag; }

private:
	CAMERA_INFO* pCameraInfo;

	bool	isShaking;
	float	shakeAmount;
	int		flag;
};
#endif // CAMERA_H