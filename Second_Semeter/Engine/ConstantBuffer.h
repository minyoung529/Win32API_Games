#pragma once
// 업로드 버퍼의 가상 주소를 가질 수 있는 상수 버퍼를 만들어야 한다.
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

public:
	/// <summary>
	/// 업로드 버퍼도 사이즈만큼 연결이 되어있어야 함
	/// 공용 버퍼 쓰지 않는다
	/// </summary>
	/// <param name="size">상수 버퍼의 사이즈</param>
	/// <param name="count">만들 개수</param>
	void Init(uint32 size, uint32 count);

	void Clear();
	void PushData(int32 rootParamIndex, void* buffer, uint32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress(uint32 index);

private:
	void CreateBuffer();

private:
	// constant buffer view
	ComPtr<ID3D12Resource>	cbvBuffer;
	BYTE*					mapedBuffer = nullptr;
	uint32					elementSize = 0;
	uint32					elementCount = 0;
	// 몇 번째 인덱스의 데이터가 접근되고 있는지
	uint32					currentIndex = 0;
};