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

private:
	vector<tKeyInfo> m_vecKey;
};
