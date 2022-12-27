#include "pch.h"
#include "Camera.h"
#include "Engine.h"
#include "Transform.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Material.h"

Matrix Camera::s_MatView;
Matrix Camera::s_MatProjection;

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
		m_matProjection = ::XMMatrixPerspectiveFovLH(m_fov, width / height, m_near, m_far);
	else
		m_matProjection = ::XMMatrixOrthographicLH(width * m_scale, height * m_scale, m_near, m_far);

	m_frustum.FinalUpdate();
}

void Camera::Render()
{
	s_MatView = m_matView;
	s_MatProjection = m_matProjection;
}

void Camera::SortGameObject()
{
	shared_ptr<Scene> scene = GET_SINGLE(SceneManager)->GetActiveScene();
	const vector<shared_ptr<GameObject>>& gmaeObjects = scene->GetGameObjects();

	m_vecDeferred.clear();
	m_vecForward.clear();

	for (const shared_ptr<GameObject>& gameObject : gmaeObjects)
	{
		if (gameObject->GetMeshRenderer() == nullptr)
			continue;

		if (IsCulled(gameObject->GetLayerIndex()))
			continue;

		if (gameObject->GetCheckFrustum())
		{
			if (m_frustum.ContainsSphere
			(gameObject->GetTransform()->GetWorldPosition(),
				gameObject->GetTransform()->GetBoundingSphereRadius()) == false)
				continue;
		}

		SHADER_TYPE shaderType = gameObject->GetMeshRenderer()->GetMaterial()->GetShader()->GetShaderType();

		// deferred를 먼저 렌더링하기 위해
		// => WHY => 먼저 블렌드하기 위해서@!@
		switch (shaderType)
		{
		case SHADER_TYPE::DEFERRED:
			m_vecDeferred.push_back(gameObject);
			break;

		case SHADER_TYPE::FORWARD:
			m_vecForward.push_back(gameObject);
			break;
		}
	}
}

void Camera::Render_Deferred()
{
	s_MatView = m_matView;
	s_MatProjection = m_matProjection;

	for (auto& gameObject : m_vecDeferred)
	{
		gameObject->GetMeshRenderer()->Render();
	}
}

void Camera::Render_Forward()
{
	s_MatView = m_matView;
	s_MatProjection = m_matProjection;

	for (auto& gameObject : m_vecForward)
	{
		gameObject->GetMeshRenderer()->Render();
	}
}