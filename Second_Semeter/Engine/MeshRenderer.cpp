#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

MeshRenderer::MeshRenderer() : Component(COMPONENT_TYPE::MESHRENDERER)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	if (m_material)
		m_material->Update();

	if (m_mesh)
		m_mesh->Update();
}

void MeshRenderer::Render()
{
	GetTransform()->PushData();

	if (m_material)
		m_material->Render();

	if (m_mesh)
		m_mesh->Render();
}
