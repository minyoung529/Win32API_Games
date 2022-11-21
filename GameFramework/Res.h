#pragma once
class Res
{
private:
	wstring m_strKey;			// 리소스 키
	wstring m_strRelativePath;	// 상대 경로 => 컴퓨터마다 다르기 때문에 release로 배포할 때 문제 X

public:
	Res();
	~Res();

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePAth(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativeKey() { return m_strRelativePath; }
};

