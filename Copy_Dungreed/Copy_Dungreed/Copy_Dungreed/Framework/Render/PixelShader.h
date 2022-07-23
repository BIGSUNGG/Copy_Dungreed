#pragma once
class Shader;

class PixelShader : public Shader
{
public:
	PixelShader(std::wstring file);
	~PixelShader();

	void CreatePixelblob(std::wstring file);
	void CreatePixelShader();

	virtual void Set() override;

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
};

