#include "pch.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include "Image.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	map<wstring, Image*>::iterator iter;

	for (iter = m_mapImage.begin(); iter != m_mapImage.end(); iter++)
	{
		delete iter->second;
	}

	m_mapImage.clear();
}

Image* ResourceManager::ImgLoad(const wstring& _strKey, const wstring& _strRelativePath)
{
	Image* pImage = ImgFind(_strKey);

	if (pImage)
	{
		return pImage;
	}

	wstring strFilePath = PathManager::GetInst()->GetResPath();
	strFilePath += _strRelativePath;

	pImage = new Image();
	pImage->Load(strFilePath);
	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);

	m_mapImage.insert({ _strKey, pImage });

	return pImage;
}

Image* ResourceManager::ImgFind(const wstring& _strKey)
{
	map<wstring, Image*>::iterator iter = m_mapImage.find(_strKey);

	if (iter == m_mapImage.end())
	{
		return nullptr;
	}

	return iter->second;
}
