cbuffer Color : register(b0)
{
	int selected;
	float value1;
	float value2;
	float value3;
	float value4;
	float3 padding;
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
	else
		result.w = value4;

	return result;
}

float4 SetAlpha(float2 uv)
{
	float4 result = map.Sample(samp, uv);

	if (result.w < 1)
		result.w = 0;
	else
		result.w = value4;

	return result;
}

float4 PS(PixelInput input) : SV_TARGET
{
	if (selected == 1)
		return SetColor(input.uv);
	if (selected == 2)
		return SetAlpha(input.uv);
	
	return map.Sample(samp, input.uv);
}