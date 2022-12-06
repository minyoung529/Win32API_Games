#pragma once
#include "Object.h"

enum class RASTERIZER_TYPE
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,	// Default
	WIREFRAME
};

enum class DEPTH_STENCIL_TYPE
{
	LESS,		// Default
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL
};

struct ShaderInfo
{
	RASTERIZER_TYPE rasterizerType = RASTERIZER_TYPE::CULL_BACK;
	DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS;
};

class Shader : public Object
{
public:
	Shader();
	virtual ~Shader();

public:
	void Init(const wstring& path, ShaderInfo info = ShaderInfo());
	void Render();

private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);

	void CreateVertexShader(const wstring& path, const string& name, const string& version);
	void CreatePixelShader(const wstring& path, const string& name, const string& version);

private:
	ComPtr<ID3DBlob>		m_vsBlob;
	ComPtr<ID3DBlob>		m_psBlob;
	ComPtr<ID3DBlob>		m_errBlob;

	ComPtr<ID3D12PipelineState>			m_pipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC	m_pipelineDesc = {};
};

