#pragma once
class PathManager
{
public:
	SINGLE(PathManager);

private:
	wchar_t m_szResPath[255];


private:
	PathManager();
	~PathManager();

public:
	void Init();

public:
	const wchar_t* GetResPath() { return m_szResPath; }
};

