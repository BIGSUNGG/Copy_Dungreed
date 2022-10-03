cbuffer Color : register(b0)
{
	int selected = 0;
	float value1 = 0;
	float value2 = 0;
	float value3 = 0;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

// SV -> System Value
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 SetColor(float2 uv)
{
	float4 result = map.Sample(samp, uv);

	result.x = value1;
	result.y = value2;
	result.z = value3;

	if (result.w < 1)
		result.w = 0;

	return result;
}

float4 PS(PixelInput input) : SV_TARGET
{
	if (selected == 1)
		return SetColor(input.uv);
	
	return map.Sample(samp, input.uv);
}