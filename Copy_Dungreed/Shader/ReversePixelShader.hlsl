Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer Info : register(b0)
{
	int isRight;
	int padding1;
	int padding2;
	int padding3;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};


float4 PS(PixelInput input) : SV_TARGET
{
	if (isRight == 1)
		input.uv.x = 1 - input.uv.x;

	float4 result = map.Sample(samp, input.uv);

	if (result.x <= 0.1 && result.y <= 0.1 && result.z <= 0.1)
	{
		result.w = 0.0f;
	}

	return result;
}