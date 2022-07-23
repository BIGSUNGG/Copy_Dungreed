#pragma once
class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void CreateSampler();
	void SetSamplerState(UINT slot);
	void Changed();
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> _samplerState;
	D3D11_SAMPLER_DESC _desc;
};

