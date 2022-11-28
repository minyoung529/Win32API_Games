#pragma once
class Object;
class Collider
{
public:
	Collider();
	~Collider();

	Collider(const Collider& origin);

private:
	Object* m_pOwner;		// collider 소유하는 오브젝트
	Vector2 m_vOffsetPos;	// 위치
	Vector2 m_vFinalPos;	// 매 프레임 계산된 최종 위치
	Vector2 m_vScale;		// 크기
	UINT m_id;				// 충돌체 고유 ID
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

