#include "pch.h"
#include "Transform.h"
#include "engine.h"
#include "camera.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM)
{
}

Transform::~Transform()
{
}

void Transform::PushData()
{
	Matrix matWVP = m_matWorld * Camera::s_matView * Camera::s_matProjection;
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&matWVP, sizeof(matWVP));
}

void Transform::FinalUpdate()
{
	// S > scale
	Matrix matScale = Matrix::CreateScale(m_localScale);

	// R > rotation
	Matrix matRotation = Matrix::CreateRotationX(m_localRotation.x);
	matRotation *= Matrix::CreateRotationY(m_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(m_localRotation.z);

	// T > translation
	Matrix matTranslation = Matrix::CreateTranslation(m_localPosition);

	m_matLocal = matScale * matRotation * matTranslation;
	m_matWorld = m_matLocal;

	// 부모가 있다면
	shared_ptr<Transform> parent = GetParent().lock();

	if (parent != nullptr)
	{
		m_matWorld *= parent->GetLocalToWorldMatrix();
	}
}
