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

	x = x - ani->GetFrameWidth() / 2;
	y = y - ani->GetFrameHeight() / 2;

	DrawBitmapByCropping(hdc, x, y,
		ani->GetFrameWidth(), ani->GetFrameHeight(),
		ani->GetFramePos().x, ani->GetFramePos().y,
		ani->GetFrameWidth(), ani->GetFrameHeight());
}

void Image::DrawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int swidth, int sheight)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP oldBitmap = (HBITMAP) SelectObject(hMemDC, bitmapHandle);

 	GdiTransparentBlt(hdc, x, y, width, height,
					  hMemDC, sx, sy, swidth, sheight, GetTransparentsColor());

	SelectObject(hMemDC, oldBitmap);
	DeleteDC(hMemDC);
}


void Image::SetTransparentColor(DWORD color)
{
	transparentColor = color;
}

DWORD Image::GetTransparentsColor()
{
	return	transparentColor;
}