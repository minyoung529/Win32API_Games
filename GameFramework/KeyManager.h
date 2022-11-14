#pragma once

struct tKeyInfo
{
	KEY_STATE	eState;	// Ű ���°�
	bool		bPrevCheck;	// ���� �����ӿ� ���ȴ���
};

class KeyManager
{
public:
	SINGLE(KeyManager);

private:
	KeyManager();
	~KeyManager();

public:
	void Init();
	void Update();
	KEY_STATE GetKey(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}

private:
	vector<tKeyInfo> m_vecKey;
};
