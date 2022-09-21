#pragma once
class Shader
{
public:
	// ���̴� ��θ� �޾ƿ�
	void Init(const wstring& path);
	void Render();


private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	
	void CreateVertexShader(const wstring& path, const string& name, const string& version);

	void CreatePixelShader(const wstring& path, const string& name, const string& version);


private:
	// ���̴�
	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3DBlob> psBlob;
	ComPtr<ID3DBlob> errBlob;

	// ���� ���������� ���ð� �ٲ� ��
	ComPtr<ID3D12PipelineState> pipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};

};