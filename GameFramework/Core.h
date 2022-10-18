#pragma once

// 동적 싱글톤
/* 싱글톤 1
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

	// 다른 데에서 만들어지지 않는다!
private:
	Core();
	~Core();
};
*/

// 정적 싱글톤
/* 2번째 싱글톤 */
class Core
{
public:
	SINGLE(Core);
	
private:
	Core();
	~Core();
};