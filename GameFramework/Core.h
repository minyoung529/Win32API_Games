#pragma once

// ���� �̱���
/* �̱��� 1
class Core
{
private:
	static Core* g_pInst;

public:
	static Core* GetInst()
	{
		if (g_pInst == nullptr)
		{
			g_pInst = new Core;
		}

		return g_pInst;
	}

	static void Release()
	{
		delete g_pInst;
		g_pInst = nullptr;
	}

	// �ٸ� ������ ��������� �ʴ´�!
private:
	Core();
	~Core();
};
*/

// ���� �̱���
/* 2��° �̱��� */
class Core
{
public:
	SINGLE(Core);
	
private:
	Core();
	~Core();
};