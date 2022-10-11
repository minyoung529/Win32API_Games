#include "pch.h"
#include "engine.h"
#include "Texture.h"

void Texture::Init(const wstring& path)
{
	CreateTexture(path);
	CreateView();
}

void Texture::CreateTexture(const wstring& path)
{
	// 파일 확장자 얻기
	wstring ext = fs::path(path).extension();

	// 로드에서 image에다 넣는다.
	if (ext == L".dds" || ext == L".DDS")
		::LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, nullptr, m_image);

	else if (ext == L".tga" || ext == L".TGA")
		::LoadFromTGAFile(path.c_str(), nullptr, m_image);

	else // png, jpg, jpeg, bmp
		::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, m_image);

	// 비트맵의 텍스쳐로 바꾼다
	HRESULT hr = ::CreateTexture(DEVICE.Get(), m_image.GetMetadata(), &m_tex2D);

	if (FAILED(hr))
		assert(nullptr);

	vector<D3D12_SUBRESOURCE_DATA> subResources;

	// 데이터를 업로드 가능한지 테스트
	hr = ::PrepareUpload
	(
		DEVICE.Get(),
		m_image.GetImages(),
		m_image.GetImageCount(),
		m_image.GetMetadata(),
		subResources
	);

	if (FAILED(hr))
		assert(nullptr);

	const uint64 bufferSize = ::GetRequiredIntermediateSize(m_tex2D.Get(), 0, static_cast<uint32>(subResources.size()));


	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	ComPtr<ID3D12Resource> textureUploadHeap;

	hr = DEVICE->CreateCommittedResource
	(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(textureUploadHeap.GetAddressOf())
	);

	if (FAILED(hr))
	{
		assert(nullptr);
	}

	// 업로드
	::UpdateSubresources
	(
		RESOURCE_CMD_LIST.Get(),
		m_tex2D.Get(),
		textureUploadHeap.Get(),
		0, 0,
		static_cast<unsigned int>(subResources.size()),
		subResources.data()
	);

	// 실제적으로 GPU에 명령을 올림
	g_Engine->GetCmdQueue()->FlushResourceCommandQueue();
}

void Texture::CreateView()
{
	// srv => shader resource view

	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DEVICE->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_srvHeap));

	m_srvHandle = m_srvHeap->GetCPUDescriptorHandleForHeapStart();

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = m_image.GetMetadata().format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Texture2D.MipLevels = 1;
	DEVICE->CreateShaderResourceView(m_tex2D.Get(), &srvDesc, m_srvHandle);
}