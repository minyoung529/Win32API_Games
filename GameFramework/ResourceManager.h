#pragma once
class Image;

class ResourceManager
{
public:
	SINGLE(ResourceManager)

private:
	map<wstring, Image*> m_mapImage;

private:
	ResourceManager();
	~ResourceManager();

public:
	Image* ImgLoad(const wstring& _strKey, const wstring& _strRelativePath);

public:
	Image* ImgFind(const wstring& _strKey);
};
