#pragma once
class Shader
{
public:
	// 셰이더 경로를 받아옴
	void Init(const wstring& path);
	void Render();


private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	
	void CreateVertexShader(const wstring& path, const string& name, const string& version);

	void CreatePixelShader(const wstring& path, const string& name, const string& version);


private:
	// 셰이더
	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3DBlob> psBlob;
	ComPtr<ID3DBlob> errBlob;

	// 렌더 파이프라인 세팅값 바꿀 것
	ComPtr<ID3D12PipelineState> pipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};

};