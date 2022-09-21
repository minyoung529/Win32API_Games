#include "pch.h"
#include "Mesh.h"
#include "engine.h"

void Mesh::Init(vector<Vertex>& vec)
{
	vertexCount = static_cast<uint32>(vec.size());

	// ���� ������ * ������ ����
	uint32 bufferSize = vertexCount * sizeof(Vertex);

	// ���ε� ���� �ϳ��� ����� (CPU, GPU ���� ����)
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource
	(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertexBuffer)
	);

	// vector => vertexBuffer�� ���� ������ �ű�
	void* vertexDaataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0);
	// ���ؽ� ���۸� ���ؼ� ������ Ǯ���� (������ ��)
	// Ư�� ��ġ �����͸� ����
	vertexBuffer->Map(0, &readRange, &vertexDaataBuffer);
	// ����
	memcpy(vertexDaataBuffer, &vec[0], bufferSize);
	vertexBuffer->Unmap(0, nullptr);

	// �������� ����Ű�� �־�� ��
	// �ּ�, ������ �ϳ��� ũ��, ����� ������ �ִ´�.
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	// �� ������ ũ��
	// vertexbuffer ������ vertexBufferView�� �Ѵ�.
	vertexBufferView.StrideInBytes = sizeof(Vertex);
	vertexBufferView.SizeInBytes = bufferSize;
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &vertexBufferView);

	engine->GetConstantBuffer()->PushData(0, &transform, sizeof(transform));

	CMD_LIST->DrawInstanced(vertexCount, 1, 0, 0);
}