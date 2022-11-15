#include "pch.h"
#include "Material.h"
#include "Engine.h"
#include "Shader.h"

void Material::PushData()
{
	// CBV 업로드
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->PushData(&m_params, sizeof(m_params));

	// SRV 업로드
	for (size_t i = 0; i < m_textures.size(); ++i)
	{
		if (m_textures[i] == nullptr)
			continue;

		SRV_REGISTER reg = SRV_REGISTER(static_cast<uint8>(SRV_REGISTER::t0) + i);
		g_Engine->GetTableDescHeap()->SetSRV(m_textures[i]->GetCpuHandle(), reg);
	}

	m_shader->Render();
}