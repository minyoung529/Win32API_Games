#ifndef	  BIMAGE_H
#define	  BIMAGE_H

#include "BBasisStd.h"

class BImage
{
public:
	BImage();
	BImage(TCHAR* strLoadFile);
	~BImage();

protected:
	HBITMAP					m_BitmapHandle;
	BITMAP					m_BitmapInfo;

public:
	bool					Load(TCHAR* strLoadFile);
	bool					Load(HBITMAP BitmapHandle);
	bool					Release();

public:
	bool					IsEmpty() const;
	HBITMAP					GetBitmapHandle() const;
	const BITMAP&			GetBitmapInfo() const;

public:
	void					DrawBitmap(HDC hdc, int x, int y, int width, int height) const;

private:
	void					drawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const;
	
private:
	static DWORD			m_TransparentColor;

public:
	static void				SetTransparentColor(DWORD color);
	static DWORD			GetTransparentColor();
};
#endif // BIMAGE_H