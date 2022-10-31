#pragma once
class Object
{
private:
	Vector2		m_ptPos;
	Vector2		m_ptScale;

public:
	void SetPos(Vector2 pos) { m_ptPos = pos; }
	void SetScale(Vector2 scale) { m_ptScale = scale; }

	const Vector2& GetPos() { return m_ptPos; }
	const Vector2& GetScale() { return m_ptScale; }

public:
	Object();
	~Object();
};