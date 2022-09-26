#pragma once

class Mesh
{
public:
	void Init(vector<Vertex>& vec);
	void Render();

	void SetTransform(const Transform& t) { transform = t; }
	void SetColor(const Color& c) { color = c; }

private:
	ComPtr<ID3D12Resource>		vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	vertexBufferView = {};
	uint32						vertexCount = 0;

	Transform					transform = {};
	Color						color = {};
};

