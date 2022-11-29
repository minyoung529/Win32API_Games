#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

public:
	void PushData();
	virtual void FinalUpdate() override;

public:
	const Vec3& GetLocalPosition()	{ return m_localPosition;	}
	const Vec3& GetLocalRotation()	{ return m_localRotation;	}
	const Vec3& GetLocalScale()		{ return m_localScale;		}

	void SetLocalPosition(const Vec3& position) { m_localPosition = position;	}
	void SetLocalRotation(const Vec3& rotation) { m_localRotation = rotation;	}
	void SetLocalScale(const Vec3& scale)		{ m_localScale = scale;			}

	const Matrix& GetLocalToWorldMatrix() { return m_matWorld; }
	const Vec3& GetWorldPosition() { return m_matWorld.Translation(); }

	Vec3 GetRight()		{ return m_matWorld.Right();	}
	Vec3 GetUp()		{ return m_matWorld.Up();		}
	Vec3 GetLook()		{ return m_matWorld.Backward(); }

public:
	void SetParent(shared_ptr<Transform> parent)	{ m_parent = parent;	}
	weak_ptr<Transform> GetParent()					{ return m_parent;		}		

private:
	// Parent ±âÁØ Local °ª
	Vec3				m_localPosition = {};
	Vec3				m_localRotation = {};
	Vec3				m_localScale = {1.f, 1.f, 1.f};

	Matrix				m_matLocal = {};
	Matrix				m_matWorld = {};

	weak_ptr<Transform> m_parent;
};

