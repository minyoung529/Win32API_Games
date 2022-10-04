#pragma once

class Mesh
{
public:
	void Init(vector<Vertex>& vec);
	void Render();

	void SetTransform(const Transform& t) { m_transform = t; }
	void SetColor(const Color& c) { m_color = c; }

private:
	ComPtr<ID3D12Resource>		m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView = { };
	uint32						m_vertexCount = 0;

	Transform					m_transform = {};
	Color						m_color = {};
};

