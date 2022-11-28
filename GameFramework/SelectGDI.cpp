#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hdc(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)
{
	HPEN hColorPen = Core::GetInst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hColorPen);

}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	: m_hdc(_dc)
	, m_hDefaultBrush(nullptr)
	, m_hDefaultPen(nullptr)

{
	HBRUSH hColorBrush = Core::GetInst()->GetBrush(_eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hColorBrush);

}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hdc, m_hDefaultPen);
	SelectObject(m_hdc, m_hDefaultBrush);
}
