#include "Camera.h"

Camera::Camera()
{
	pCameraInfo = nullptr;
	flag = -1;
}

Camera::~Camera()
{
}

void Camera::Init(int width, int height, int backWidth, int backHeight)
{
	if (pCameraInfo)
	{
		Release();
	}

	pCameraInfo = new CAMERA_INFO;
	pCameraInfo->width = width;
	pCameraInfo->height = height;
	pCameraInfo->backWidth = backWidth;
	pCameraInfo->backHeight = backHeight;
}

void Camera::Release()
{
	SAFE_DELETE(pCameraInfo)
}

bool Camera::CheckCameraX()
{
	if (!pCameraInfo) return false;

	if (pCameraInfo->x - pCameraInfo->width / 2 <= 0 ||
		pCameraInfo->x + pCameraInfo->width / 2 >= pCameraInfo->backWidth)
		return false;

	return true;
}

bool Camera::CheckCameraY()
{
	if (!pCameraInfo)return false;

	if (pCameraInfo->y - pCameraInfo->height / 2 <= 0 ||
		pCameraInfo->y + pCameraInfo->height / 2 >= pCameraInfo->backHeight)
		return false;

	return true;
}

void Camera::CameraShake()
{
	flag *= -1;
}