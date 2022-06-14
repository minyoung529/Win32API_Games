#include "BImage.h"

DWORD BImage::m_TransparentColor = RGB(255, 0, 255);

BImage::BImage() : m_BitmapHandle(nullptr)
{
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}

BImage::BImage(TCHAR* strLoadFile) : BImage()
{
	this->Load(strLoadFile);
}

BImage::~BImage()
{
	if (!this->IsEmpty())
		DeleteObject(m_BitmapHandle);
}

bool BImage::IsEmpty() const
{
	return m_BitmapHandle == NULL;
}

bool BImage::Load(TCHAR* strLoadFile)
{
	m_BitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(NULL), strLoadFile, IMAGE_BITMAP, 0, 0, 
					 LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (this->IsEmpty())
		return false;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

bool BImage::Load(HBITMAP BitmapHandle)
{
	if (!this->IsEmpty())
		DeleteObject(m_BitmapHandle);

	m_BitmapHandle = BitmapHandle;
	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

bool BImage::Release()
{
	if (!this->IsEmpty())
		DeleteObject(m_BitmapHandle);

	return true;
}

HBITMAP BImage::GetBitmapHandle() const
{
	return m_BitmapHandle;
}

const BITMAP& BImage::GetBitmapInfo() const
{
	return m_BitmapInfo;
}

void BImage::DrawBitmap(HDC hdc, int x, int y, int width, int height) const
{
	if (width == 0)
		width = m_BitmapInfo.bmWidth;
	if (height == 0)
		height = m_BitmapInfo.bmHeight;

	this->drawBitmapByCropping(hdc, x, y, width, height, 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight);
}

void BImage::drawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const
{
	HDC hMemDC;

	hMemDC = CreateCompatibleDC(hdc);

	SelectObject(hMemDC, m_BitmapHandle);

	GdiTransparentBlt(
		hdc, x, y, width, height,		
		hMemDC, sx, sy, sw, sh, GetTransparentColor());

	DeleteDC(hMemDC);
}

void BImage::SetTransparentColor(DWORD color)
{
	m_TransparentColor = color;
}

DWORD BImage::GetTransparentColor()
{
	return m_TransparentColor;
}