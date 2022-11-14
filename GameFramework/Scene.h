#pragma once

// ���漱��
// ������ ���빰�� ���� ������ �Ұ���
// => ������ (include > ����)
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
	// inline: Ŭ���� ���ο��� �����ؼ� �Լ� ȣ�� ����� ����, ����� ����
	void AddObject(Object* _pObj, GROUP_TYPE _eType)
	{
		m_vecObj[(UINT)_eType].push_back(_pObj);
	}
};