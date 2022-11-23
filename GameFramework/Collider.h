#pragma once
class Object;
class Collider
{
private:
	Object* m_pOwner;		// collider �����ϴ� ������Ʈ
	Vector2 m_vOffsetPos;	// ��ġ
	Vector2 m_vFinalPos;	// �� ������ ���� ���� ��ġ
	Vector2 m_vScale;		// ũ��

	friend class Object;	 

public:
	virtual void FinalUpdate() final;
	void Render(HDC hdc);

public:
	void SetOffsetPos(Vector2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }
	Vector2 GetOffsetPos() { return m_vOffsetPos; }
	Vector2 GetSclae() { return m_vScale; }
};

