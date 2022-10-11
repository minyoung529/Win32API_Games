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
	// 명령을 차곡차곡 기록했다가 한번에 요청하는 용도
	// GPU에 명령 리스트에 있는 명령들을 GPU에 요청?
	ComPtr<ID3D12CommandQueue>			m_cmdQueue;
	// list를 생성하기 위해 필요함
	ComPtr<ID3D12CommandAllocator>		m_cmdAlloc;
	// queue에게 명령을 넣기 위해 필요함?
	ComPtr<ID3D12GraphicsCommandList>	m_cmdList;

	// alloc > list > queue

	// 새로 만든 이유:
	// 텍스쳐를 올려줄 건데 매 프레임마다 올릴 필요 없으므로
	// 새로운 걸 만들어서 처음에만 올려준다!
	ComPtr<ID3D12CommandAllocator>		m_resCmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>	m_resCmdList;

	// 울타리
	// CPU/GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					m_fence;
	uint32								m_fenceValue = 0;
	HANDLE								m_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				m_swapChain;
};

