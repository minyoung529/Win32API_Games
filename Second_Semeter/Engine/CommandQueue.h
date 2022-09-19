#pragma once

class SwapChain;

class CommandQueue
{
public:
	CommandQueue();
	~CommandQueue();

public:
	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return cmdList; }

private:
	// ����� �������� ����ߴٰ� �ѹ��� ��û�ϴ� �뵵
	ComPtr<ID3D12CommandQueue>			cmdQueue;
	ComPtr<ID3D12CommandAllocator>		cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	cmdList;

	// ��Ÿ��
	// CPU / GPU ����ȭ�� ���� ������ ����
	ComPtr<ID3D12Fence>					fence;
	uint32								fenceValue = 0;
	HANDLE								fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				swapChain;
};