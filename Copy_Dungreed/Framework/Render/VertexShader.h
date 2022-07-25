#pragma once
class VertexShader : public Shader
{
public:
	VertexShader(std::wstring file);
	~VertexShader();

	void CreateBlob(std::wstring file);
	void CreateInputLayout();
	void CreateVertexShader();

	virtual void Set() override;

private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	_inputLayout; // 어떤 정보인지 알려주는 서식
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	_vertexShader; // 받은 정점으로 WVP -> 3D에 있던 것을 2D 옮기는 작업

	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> _reflection;
};

