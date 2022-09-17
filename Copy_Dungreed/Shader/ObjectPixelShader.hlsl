cbuffer Color : register(b0)
{
	int selected;
	float3 rgb;
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
	float4 color = map.Sample(samp, uv);
	color.x = rgb.x;
	color.y = rgb.y;
	color.z = rgb.z;

	return color;
}

float4 PS(PixelInput input) : SV_TARGET
{
	if (selected > 0)
		return SetColor(input.uv);
	
	return map.Sample(samp, input.uv);
}