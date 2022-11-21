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
};
