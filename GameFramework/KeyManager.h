#pragma once

struct tKeyInfo
{
	KEY_STATE	eState;	// 키 상태값
	bool		bPrevCheck;	// 이전 프레임에 눌렸는지
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
