#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(vector<Vertex>& vec)
{
	m_vertexCount = static_cast<uint32>(vec.size());

	uint32 bufferSize = m_vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_vertexBuffer));

	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0);
	m_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &vec[0], bufferSize);
	m_vertexBuffer->Unmap(0, nullptr);

	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
	m_vertexBufferView.StrideInBytes = sizeof(Vertex);
	m_vertexBufferView.SizeInBytes = bufferSize;
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &m_vertexBufferView);

	g_Engine->GetConstantBuf()->PushData(0, &m_transform, sizeof(m_transform));
	g_Engine->GetConstantBuf()->PushData(1, &m_color, sizeof(m_color));

	CMD_LIST->DrawInstanced(m_vertexCount, 1, 0, 0);
}
