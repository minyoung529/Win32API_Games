#pragma once
class Object;
class Collider
{
private:
	Object* m_pOwner;		// collider 소유하는 오브젝트
	Vector2 m_vOffsetPos;	// 위치
	Vector2 m_vFinalPos;	// 매 프레임 계산된 최종 위치
	Vector2 m_vScale;		// 크기

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

