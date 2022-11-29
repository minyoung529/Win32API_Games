#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"

Transform::Transform() : Component(COMPONENT_TYPE::TRANSFORM)
{
}

Transform::~Transform()
{
}

void Transform::PushData()
{
	TransformParams transformParams = {};

	transformParams.matWorld = m_matWorld;
	transformParams.matView = Camera::s_MatView;
	transformParams.matProjection = Camera::s_MatProjection;
	transformParams.matWV = m_matWorld * Camera::s_MatView;
	transformParams.matWVP = m_matWorld * Camera::s_MatView * Camera::s_MatProjection;

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&transformParams, sizeof(transformParams));
}

void Transform::FinalUpdate()
{
	Matrix matScale = Matrix::CreateScale(m_localScale);
	Matrix matRotation = Matrix::CreateRotationX(m_localRotation.x);
	matRotation *= Matrix::CreateRotationY(m_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(m_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(m_localPosition);

	m_matLocal = matScale * matRotation * matTranslation;
	m_matWorld = m_matLocal;

	shared_ptr<Transform> parent = GetParent().lock();
	if (parent != nullptr)
	{
		m_matWorld *= parent->GetLocalToWorldMatrix();
	}
}
