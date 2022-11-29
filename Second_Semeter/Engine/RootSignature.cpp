#include "pch.h"
#include "RootSignature.h"
#include "Engine.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	CreateSamplerDesc();
	CreateRootSignature();
}

void RootSignature::CreateSamplerDesc()
{
	m_samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);
}

void RootSignature::CreateRootSignature()
{
	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 1), // b1~b4
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, SRV_REGISTER_COUNT, 0), // t0~t5
	};

	CD3DX12_ROOT_PARAMETER param[2];
	param[0].InitAsDescriptorTable(_countof(ranges), ranges);
	param[1].InitAsConstantBufferView(static_cast<uint32>(CBV_REGISTER::b0));


	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(param), param, 1, &m_samplerDesc);
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;

	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);

	DEVICE->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&m_signature));
}
