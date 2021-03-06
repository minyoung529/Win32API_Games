#ifndef IMAGE_H
#define IMAGE_H

#include "BasisStd.h"

class Image
{
public :
	Image();
	Image(LPCTSTR strLoadFile);
	~Image();

private:
	HBITMAP			bitmapHandle;
	BITMAP			bitmap;
	static DWORD	transparentColor; // 투명 처리 색상

public:
	bool			Load(LPCTSTR strLoadFile);
	bool			Load(HBITMAP bitmapHandler);
	void			Release();

public:
	void			DrawBitmap(HDC hdc, int x, int y, int width = 0, int height = 0);
	void			DrawBitmapByCropping(HDC hdc, int x, int y, int width, int height,
										 int sx, int sy, int swidth, int sheight);

public:
	bool			IsEmpty();
	HBITMAP			GetBitmapHandle();
	const BITMAP&	GetBitmapInfo();
	
public:
	static void		SetTransparentColor(DWORD color);
	static DWORD	GetTransparentsColor();
};
#endif // IMAGE_H