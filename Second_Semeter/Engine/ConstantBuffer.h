#pragma once
// ���ε� ������ ���� �ּҸ� ���� �� �ִ� ��� ���۸� ������ �Ѵ�.
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

public:
	/// <summary>
	/// ���ε� ���۵� �����ŭ ������ �Ǿ��־�� ��
	/// ���� ���� ���� �ʴ´�
	/// </summary>
	/// <param name="size">��� ������ ������</param>
	/// <param name="count">���� ����</param>
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
	// �� ��° �ε����� �����Ͱ� ���ٵǰ� �ִ���
	uint32					currentIndex = 0;
};