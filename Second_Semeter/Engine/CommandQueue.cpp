#include "pch.h"
#include "CommandQueue.h"
#include "engine.h"

CommandQueue::CommandQueue()
{
}

CommandQueue::~CommandQueue()
{
	::CloseHandle(fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	this->swapChain = swapChain;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&cmdQueue));
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&cmdList));

	// Queue, Alloc, List�� ��� ������ �� ����

	// cmd List ��� ���
	cmdList->Close();
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
	fenceValue++;

	cmdQueue->Signal(fence.Get(), fenceValue);

	if (fence->GetCompletedValue() < fenceValue)
	{
		fence->SetEventOnCompletion(fenceValue, fenceEvent);
		::WaitForSingleObject(fenceEvent, INFINITE);
	}
}

// �׸��� ��
// �غ� �۾��̶� ���̴��� �Ѿ�� ���ҽ��� ����
void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	cmdAlloc->Reset();
	cmdList->Reset(cmdAlloc.Get(), nullptr);

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition
	(
		swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT, // ȭ�� ���
		D3D12_RESOURCE_STATE_RENDER_TARGET// ���� �����
	); 

	// ���̴����� ������� �ϴ� �ڷ���
	cmdList->SetGraphicsRootSignature(ROOT_SIGNATURE.Get());
	engine->GetConstantBuffer()->Clear();

	cmdList->ResourceBarrier(1, &barrier);

	// Set the viewport and scissor rect. This needs to be reset whenever the command list is reset.
	cmdList->RSSetViewports(1, vp);
	cmdList->RSSetScissorRects(1, rect);

	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = swapChain->GetBackRTV();
	cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);
}

// �׸� ��
void CommandQueue::RenderEnd()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition
	(
		swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,		// ���� �����
		D3D12_RESOURCE_STATE_PRESENT			// ȭ�� ���
	); 

	cmdList->ResourceBarrier(1, &barrier);
	cmdList->Close();

	// Ŀ�ǵ� ����Ʈ ����
	ID3D12CommandList* cmdListArr[] = { cmdList.Get() };
	cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	// ȭ�鿡 ǥ���ϰ�
	swapChain->Present();

	// Wait until frame commands are complete. This waiting is inefficient and is
	// done for simplicity. Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	// ���
	WaitSync();
	// ��ɾ� ó�� ������ ����
	swapChain->SwapIndex();
}
