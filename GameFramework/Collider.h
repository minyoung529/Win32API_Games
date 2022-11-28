#pragma once
class Object;
class Collider
{
public:
	Collider();
	~Collider();

	Collider(const Collider& origin);

private:
	Object* m_pOwner;		// collider �����ϴ� ������Ʈ
	Vector2 m_vOffsetPos;	// ��ġ
	Vector2 m_vFinalPos;	// �� ������ ���� ���� ��ġ
	Vector2 m_vScale;		// ũ��
	UINT m_id;				// �浹ü ���� ID
	static UINT g_iNextID;	// 

	friend class Object;


public:
	virtual void FinalUpdate() final;
	void Render(HDC hdc);

	void EnterCollision(Collider* _pOther);
	void StayCollision(Collider* _pOther);
	void ExitCollision(Collider* _pOther);

public:
	void SetOffsetPos(Vector2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }
	Vector2 GetOffsetPos() { return m_vOffsetPos; }
	Vector2 GetSclae() { return m_vScale; }
	UINT GetID() { return m_id; }

public:
	Collider& operator= (Collider& origin) = delete;
};

