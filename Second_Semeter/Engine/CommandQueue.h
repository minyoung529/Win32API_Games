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

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return m_cmdQueue; }
	ComPtr< ID3D12GraphicsCommandList> GetCmdList() { return m_cmdList; }

private:
	// ����� �������� ����ߴٰ� �ѹ��� ��û�ϴ� �뵵
	ComPtr<ID3D12CommandQueue>			m_cmdQueue;
	ComPtr<ID3D12CommandAllocator>		m_cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	m_cmdList;

	// ��Ÿ��
	// CPU/GPU ����ȭ�� ���� ������ ����
	ComPtr<ID3D12Fence>					m_fence;
	uint32								m_fenceValue = 0;
	HANDLE								m_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				m_swapChain;
};

