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

void MeshRenderer::SetMaterial(shared_ptr<Material> material, uint32 idx)
{
	if (m_materials.size() <= static_cast<size_t>(idx))
	{
		m_materials.resize(static_cast<size_t>(idx) + 1);
	}

	m_materials[idx] = material;
}

void MeshRenderer::Update()
{
}

void MeshRenderer::Render()
{
	for (uint32 i = 0; i < m_materials.size(); i++)
	{
		shared_ptr<Material>& material = m_materials[i];

		if (material == nullptr || material->GetShader() == nullptr)
			continue;

		GetTransform()->PushData();
		material->PushData();
		m_mesh->Render(i);
	}
}
