cbuffer View : register(b1)
{
	matrix view;
}

cbuffer Projection : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;

	matrix transform : INSTANCE_TRANSFORM;
};

// SV -> System Value
struct VertexOutput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// SV : System Value
VertexOutput VS(VertexInput input)
{
	//matrix wvp = mul(world,view);
	//wvp = mul(wvp, projection);
	VertexOutput output;
	output.pos = mul(input.pos, input.transform);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;

	return output;
}