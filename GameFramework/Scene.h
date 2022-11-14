#pragma once

// 전방선언
// 접근은 내용물이 없기 때문에 불가능
// => 빠르다 (include > 복붙)
class Object;

class Scene
{
public:
	Scene();
	virtual ~Scene();

private:
	vector<Object*> m_vecObj[(int)GROUP_TYPE::END];
	wstring			m_strName;

public:
	void SetName(const wstring& _strName)
	{
		m_strName = _strName;
	}
	const wstring& GetName() { return m_strName; }

public:
	virtual void Enter() abstract;
	virtual void Exit() abstract;
	void Update();
	void Render(HDC hdc);

public:
	// inline: 클래스 내부에서 정의해서 함수 호출 비용을 줄임, 디버깅 용이
	void AddObject(Object* _pObj, GROUP_TYPE _eType)
	{
		m_vecObj[(UINT)_eType].push_back(_pObj);
	}
};