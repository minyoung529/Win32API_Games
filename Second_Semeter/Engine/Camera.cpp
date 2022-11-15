#include "pch.h"
#include "Camera.h"
#include "Engine.h"
#include "Transform.h"

Matrix Camera::s_matView;
Matrix Camera::s_matProjection;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{

}

Camera::~Camera()
{
}

void Camera::FinalUpdate()
{
	// 카메라 월드 행렬의 역행렬
	m_matView = GetTransform()->GetLocalToWorldMatrix().Invert();

	float width = static_cast<float>(g_Engine->GetWindow().width);
	float height = static_cast<float>(g_Engine->GetWindow().height);

	if (m_type == PROJECTION_TYPE::PERSPECTIVE)
	{
		m_matProjection = ::XMMatrixPerspectiveFovLH(m_fov, width / height, m_near, m_far);
	}
	else
	{
		m_matProjection = ::XMMatrixOrthographicLH(width * m_scale, height * m_scale, m_far, m_far);
	}

	s_matView = m_matView;
	s_matProjection = m_matProjection;
}
