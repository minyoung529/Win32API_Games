#pragma once
#include "Object.h"

class Material;

struct IndexBufferInfo
{
	ComPtr<ID3D12Resource>		buffer;
	D3D12_INDEX_BUFFER_VIEW		bufferView;
	DXGI_FORMAT					format;
	uint32						count;
};

class Mesh : public Object
{
public:
	Mesh();
	virtual ~Mesh();

public:
	void Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexBuffer);
	void Update();
	void Render(uint32 idx = 0);

public:
	static shared_ptr<Mesh> CreateFromFBX(const struct FbxMeshInfo* meshInfo);

private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBuffer(const vector<uint32>& buffer);

private:
	ComPtr<ID3D12Resource>		m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView = { };
	uint32						m_vertexCount = 0;

	vector<IndexBufferInfo>		m_vecIndexInfo;
};

