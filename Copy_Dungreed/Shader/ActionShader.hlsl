cbuffer Frame : register(b0)
{
	float2 startPos;
	float2 maxSize;
	float2 size;
	float2 padding;
}

Texture2D map : register(t0);
SamplerState samp : register(s0);

// SV -> System Value
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// 후면버퍼에 그릴 내용
// 1프레임당 호출 횟수 : 1280 x 720 만큼 호출
float4 PS(PixelInput input) : SV_TARGET
{
	float2 spriteUV;
	spriteUV.x = input.uv.x * (size.x / maxSize.x) + (startPos.x / maxSize.x);
	spriteUV.y = input.uv.y * (size.y / maxSize.y) + (startPos.y / maxSize.y);

	return map.Sample(samp, spriteUV);
}