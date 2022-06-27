#include "Image.h"

DWORD Image::transparentColor = RGB(255, 0, 255);

Image::Image() : bitmapHandle(nullptr)
{
	memset(&bitmap, 0, sizeof(bitmap));
}

Image::Image(LPCTSTR strLoadFile)
{
	this->Load(strLoadFile);
}

bool Image::IsEmpty()
{
	return (bitmapHandle == nullptr);
}


Image::~Image()
{
	if (!IsEmpty())
	{
		DeleteObject(GetBitmapHandle());
	}
}

bool Image::Load(LPCTSTR strLoadFile)
{
	bitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(nullptr),
		strLoadFile,
		IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (this->IsEmpty())
		return false;

	GetObject(bitmapHandle, sizeof(bitmap), &bitmap);
	return true;
}

bool Image::Load(HBITMAP hBitmap)
{
	if (hBitmap == nullptr) return false;

	if (this->IsEmpty())
	{
		DeleteObject(bitmapHandle);
	}

	bitmapHandle = hBitmap;
	GetObject(bitmapHandle, sizeof(bitmapHandle), &bitmap);

	return true;
}

void Image::Release()
{
	if (!this->IsEmpty())
	{
		DeleteObject(bitmapHandle);
	}
}

HBITMAP Image::GetBitmapHandle()
{
	return bitmapHandle;
}

const BITMAP& Image::GetBitmap()
{
	return bitmap;
}

void Image::DrawBitmap(HDC hdc, int x, int y, int width, int height)
{
	if (width == 0)
		width = bitmap.bmWidth;

	if (height == 0)
		height = bitmap.bmHeight;

	this->DrawBitmapByCropping(hdc, x, y, width, height, 0, 0, bitmap.bmWidth, bitmap.bmHeight);
}

void Image::DrawAniRender(HDC hdc, int x, int y, Animation* ani)
{
	if (!ani) return;

	DrawBitmapByCropping(hdc, x, y,
		ani->GetFrameWidth(), ani->GetFrameHeight(),
		ani->GetFramePos().x, ani->GetFramePos().y,
		ani->GetFrameWidth(), ani->GetFrameHeight());
}

void Image::DrawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int swidth, int sheight)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(hMemDC, bitmapHandle);

	GdiTransparentBlt(hdc, x, y, width, height,
		hMemDC, sx, sy, swidth, sheight, GetTransparentsColor());

	SelectObject(hMemDC, oldBitmap);
	DeleteDC(hMemDC);
}

void Image::DrawLoopRender(HDC hdc, RECT drawArea, int offsetX, int offsetY)
{
	if (offsetX < 0) offsetX = 0;
	if (offsetY < 0) offsetY = 0;

	RECT destination = {};
	RECT source = {};

	int drawAreaX = drawArea.left;					// 그려질 영역의 left
	int drawAreaY = drawArea.top;					// 그려질 영역의 top
	int drawAreaW = drawArea.right - drawAreaX;		// 그려질 영역의 넓이
	int drawAreaH = drawArea.bottom - drawAreaY;	// 그려질 영역의 높이

	int sourceWidth = 0;	// 그려질 영역의 높이

	source.top = offsetY % bitmap.bmHeight;
	source.bottom = bitmap.bmHeight;

	for (int x = 0; x < drawAreaW; x += sourceWidth)
	{
		source.left = (x + offsetX) % bitmap.bmWidth;
		source.right = bitmap.bmWidth;

		sourceWidth = source.right - source.left;

		if (x + sourceWidth > drawAreaW)
		{
			source.right -= (x + sourceWidth) - drawAreaW;
			sourceWidth = source.right - source.left;
		}

		destination.left = x + drawAreaX;
		destination.right = destination.left + sourceWidth;

		int width = source.right - source.left;
		int height = source.bottom - source.top;

		DrawBitmapByCropping
		(
			hdc,
			destination.left, destination.top, width, height,
			source.left, source.top, width, height
		);
	}
}


void Image::SetTransparentColor(DWORD color)
{
	transparentColor = color;
}

DWORD Image::GetTransparentsColor()
{
	return	transparentColor;
}