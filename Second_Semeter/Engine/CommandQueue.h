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

	void FlushResourceCommandQueue();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return m_cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return m_cmdList; }
	ComPtr<ID3D12GraphicsCommandList> GetResourceCmdList() { return m_resCmdList; }

private:
	// ����� �������� ����ߴٰ� �ѹ��� ��û�ϴ� �뵵
	// GPU�� ��� ����Ʈ�� �ִ� ��ɵ��� GPU�� ��û?
	ComPtr<ID3D12CommandQueue>			m_cmdQueue;
	// list�� �����ϱ� ���� �ʿ���
	ComPtr<ID3D12CommandAllocator>		m_cmdAlloc;
	// queue���� ����� �ֱ� ���� �ʿ���?
	ComPtr<ID3D12GraphicsCommandList>	m_cmdList;

	// alloc > list > queue

	// ���� ���� ����:
	// �ؽ��ĸ� �÷��� �ǵ� �� �����Ӹ��� �ø� �ʿ� �����Ƿ�
	// ���ο� �� ���� ó������ �÷��ش�!
	ComPtr<ID3D12CommandAllocator>		m_resCmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	m_resCmdList;

	// ��Ÿ��
	// CPU/GPU ����ȭ�� ���� ������ ����
	ComPtr<ID3D12Fence>					m_fence;
	uint32								m_fenceValue = 0;
	HANDLE								m_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				m_swapChain;
};

