#include "pch.h"
#include "RenderTargetGroup.h"
#include "Engine.h"

void RenderTargetGroup::Create(RENDER_TARGET_GROUP_TYPE groupType, vector<RenderTarget>& rtVec,
	shared_ptr<Texture> dsTexture)
{
	m_groupType = groupType;
	m_rtVec = rtVec;
	m_rtCount = static_cast<uint32>(rtVec.size());
	m_dsTexture = dsTexture;
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = m_rtCount;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heapDesc.NodeMask = 0;
	DEVICE->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_rtvHeap));
	m_rtvHeapSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	m_rtvHeapBegin = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
	m_dsvHeapBegin = m_dsTexture->GetDSV()->GetCPUDescriptorHandleForHeapStart();
	for (uint32 i = 0; i < m_rtCount; i++)
	{
		uint32 destSize = 1;
		D3D12_CPU_DESCRIPTOR_HANDLE destHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeapBegin, i * m_rtvHeapSize);
		uint32 srcSize = 1;
		ComPtr<ID3D12DescriptorHeap> srcRtvHeapBegin = m_rtVec[i].target->GetRTV();
		D3D12_CPU_DESCRIPTOR_HANDLE srcHandle = srcRtvHeapBegin->GetCPUDescriptorHandleForHeapStart();
		DEVICE->CopyDescriptors(1, &destHandle, &destSize, 1, &srcHandle, &srcSize, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}
}

void RenderTargetGroup::OMSetRenderTargets(uint32 count, uint32 offset)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeapBegin, offset * m_rtvHeapSize);
	CMD_LIST->OMSetRenderTargets(count, &rtvHandle, FALSE/*1°³*/, &m_dsvHeapBegin);
}

void RenderTargetGroup::OMSetRenderTargets()
{
	CMD_LIST->OMSetRenderTargets(m_rtCount, &m_rtvHeapBegin, TRUE/*´ÙÁß*/, &m_dsvHeapBegin);
}

void RenderTargetGroup::ClearRenderTargetView(uint32 index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeapBegin, index * m_rtvHeapSize);
	CMD_LIST->ClearRenderTargetView(rtvHandle, m_rtVec[index].clearColor, 0, nullptr);
	CMD_LIST->ClearDepthStencilView(m_dsvHeapBegin, D3D12_CLEAR_FLAG_DEPTH, 1.f, 0, 0,
		nullptr);
}

void RenderTargetGroup::ClearRenderTargetView()
{
	for (uint32 i = 0; i < m_rtCount; i++)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(m_rtvHeapBegin, i * m_rtvHeapSize);
		CMD_LIST->ClearRenderTargetView(rtvHandle, m_rtVec[i].clearColor, 0, nullptr);
	}
	CMD_LIST->ClearDepthStencilView(m_dsvHeapBegin, D3D12_CLEAR_FLAG_DEPTH, 1.f, 0, 0,
		nullptr);
}
