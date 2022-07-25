#pragma once
class SRV
{
public:
	SRV(std::wstring file);
	~SRV();

	void CreateSRV(std::wstring file);
	void SetSRV(UINT slot);

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
};

