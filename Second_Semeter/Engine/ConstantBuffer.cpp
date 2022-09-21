#include "pch.h"
#include "ConstantBuffer.h"
#include "engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	if (cbvBuffer)
	{
		cbvBuffer->Unmap(0, nullptr);
		cbvBuffer = nullptr;
	}
}

void ConstantBuffer::Init(uint32 size, uint32 count)
{
	// 상수 버퍼: 256바이트 배수로 만들어야 한다

	// 상수 버퍼의 사이즈 + 255, 반전 and 연산
	elementSize = (size + 255) & ~255;
	elementCount = count;
	CreateBuffer();
}

void ConstantBuffer::Clear()
{
	currentIndex = 0;
}

void ConstantBuffer::PushData(int32 rootParamIndex, void* buffer, uint32 size)
{
	assert(currentIndex < elementCount);

	// 다음 배열의 시작 => currentIndex * elementSize
	::memcpy(&mapedBuffer[currentIndex * elementSize], buffer, size);

	D3D12_GPU_VIRTUAL_ADDRESS address = GetGPUVirtualAddress(currentIndex);
	
	CMD_LIST->SetGraphicsRootConstantBufferView(rootParamIndex, address);

	currentIndex++;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGPUVirtualAddress(uint32 index)
{
	// 가상메모리
	D3D12_GPU_VIRTUAL_ADDRESS objCBAdress = cbvBuffer->GetGPUVirtualAddress();
	objCBAdress += index * elementSize;
	return objCBAdress;
}

void ConstantBuffer::CreateBuffer()
{
	// 버퍼를 만들고
	uint32 bufferSize = elementSize * elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&cbvBuffer));

	// 무형의 void 포인터
	// cvb 버퍼에 maped 버퍼를 연결했고, 기존에 빈 공간인 maped 버퍼에서 데이터를 채우면
	// cvb 버퍼가 가지고 있는다??
	cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mapedBuffer));
}