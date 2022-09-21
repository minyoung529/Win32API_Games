#include "pch.h"
#include "Mesh.h"
#include "engine.h"

void Mesh::Init(vector<Vertex>& vec)
{
	vertexCount = static_cast<uint32>(vec.size());

	// 벡터 사이즈 * 정점의 개수
	uint32 bufferSize = vertexCount * sizeof(Vertex);

	// 업로드 버퍼 하나를 만든다 (CPU, GPU 접근 가능)
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

	// vector => vertexBuffer로 정점 정보를 옮김
	void* vertexDaataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0);
	// 버텍스 버퍼를 통해서 데이터 풀어줌 (연결할 때)
	// 특정 위치 데이터를 복사
	vertexBuffer->Map(0, &readRange, &vertexDaataBuffer);
	// 복사
	memcpy(vertexDaataBuffer, &vec[0], bufferSize);
	vertexBuffer->Unmap(0, nullptr);

	// 누군가가 가리키고 있어야 함
	// 주소, 정점의 하나의 크기, 사이즈를 가지고 있는다.
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	// 한 정점의 크기
	// vertexbuffer 접근은 vertexBufferView가 한다.
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