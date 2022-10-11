#include "pch.h"
#include "CommandQueue.h"
#include "Engine.h"

CommandQueue::CommandQueue()
{
}

CommandQueue::~CommandQueue()
{
	::CloseHandle(m_fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	m_swapChain = swapChain;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_cmdQueue));
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&m_cmdList));

	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_resCmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_resCmdAlloc.Get(), nullptr, IID_PPV_ARGS(&m_resCmdList));

	// cmdList ���� ���
	m_cmdList->Close();

	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
	m_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
	m_fenceValue++;

	m_cmdQueue->Signal(m_fence.Get(), m_fenceValue);

	if (m_fence->GetCompletedValue() < m_fenceValue)
	{
		m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent);
		::WaitForSingleObject(m_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	m_cmdAlloc->Reset();
	m_cmdList->Reset(m_cmdAlloc.Get(), nullptr);
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		m_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT, // ȭ�� ���
		D3D12_RESOURCE_STATE_RENDER_TARGET); // ���� �����

	m_cmdList->SetGraphicsRootSignature(ROOT_SIGNATURE.Get());
	g_Engine->GetConstantBuf()->Clear();
	g_Engine->GetTableDescHeap()->Clear();

	ID3D12DescriptorHeap* descHeap = g_Engine->GetTableDescHeap()->GetDescriptorHeap().Get();
	m_cmdList->SetDescriptorHeaps(1, &descHeap);

	m_cmdList->ResourceBarrier(1, &barrier);
	// Set the viewport and scissor rect. This needs to be reset whenever the command list is reset.
	m_cmdList->RSSetViewports(1, vp);
	m_cmdList->RSSetScissorRects(1, rect);
	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = m_swapChain->GetBackRTV();
	m_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	m_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);
}

void CommandQueue::RenderEnd()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition
	(
		m_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, // ���� �����
		D3D12_RESOURCE_STATE_PRESENT // ȭ�� ���
	); 

	m_cmdList->ResourceBarrier(1, &barrier);
	m_cmdList->Close();
	// Ŀ�ǵ� ����Ʈ ����
	ID3D12CommandList* cmdListArr[] = { m_cmdList.Get() };
	m_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);
	m_swapChain->Present();
	// Wait until frame commands are complete. This waiting is inefficient and is
	// done for simplicity. Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	WaitSync();
	m_swapChain->SwapIndex();
}

void CommandQueue::FlushResourceCommandQueue()
{
	// ���� �������� Ÿ�� �ʱ� ����
	// ���ο� ���ҽ� ����Ʈ ����

	m_resCmdList->Close();

	ID3D12CommandList* cmdListArr[] = { m_resCmdList.Get() };
	m_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	WaitSync();

	m_resCmdAlloc->Reset();
	m_resCmdList->Reset(m_resCmdAlloc.Get(), nullptr);
}