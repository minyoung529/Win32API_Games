#pragma once

class Texture;

class Mesh
{
public:
	void Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexBuffer);
	void Render();

	void SetTransform(const Transform& t) { m_transform = t; }
	void SetColor(const Color& c) { m_color = c; }
	void SetTexture(shared_ptr<Texture> tex) { m_tex = tex; }

private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBuffer(const vector<uint32>& buffer);

private:
	ComPtr<ID3D12Resource>		m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView = { };
	uint32						m_vertexCount = 0;

	ComPtr<ID3D12Resource>		m_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW		m_indexBufferView = { };
	uint32						m_indexCount = 0;

	Transform					m_transform = {};
	Color						m_color = {};
	shared_ptr<Texture>			m_tex;
};

