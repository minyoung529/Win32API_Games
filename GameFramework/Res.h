#pragma once
class Res
{
private:
	wstring m_strKey;			// ���ҽ� Ű
	wstring m_strRelativePath;	// ��� ��� => ��ǻ�͸��� �ٸ��� ������ release�� ������ �� ���� X

public:
	Res();
	~Res();

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePAth(const wstring& _strPath) { m_strRelativePath = _strPath; }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRelativeKey() { return m_strRelativePath; }
};

