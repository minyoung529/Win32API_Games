#include "pch.h"
#include "Image.h"
#include "Core.h"

Image::Image()
	: m_hBit(0)
	, m_hDC(0)
{
}

Image::~Image()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

void Image::Load(const wstring& _strFieldPath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFieldPath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBit);

	// 비트맵과 연결할 DC
	m_hDC = CreateCompatibleDC(Core::GetInst()->GetMainDC());
	SelectObject(m_hDC, m_hBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
