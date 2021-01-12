#include "standardConstants.h"

#define surfEmissive (surfProps.w)

float4		emissive	: register(c41);
float4		ambient		: register(c42);

struct VS_in
{
	float4 Position		: POSITION;
	float3 Normal		: NORMAL;
	float2 TexCoord		: TEXCOORD0;
	float4 Prelight		: COLOR0;
};

struct VS_out {
	float4 Position		: POSITION;
	float3 TexCoord0	: TEXCOORD0;	// also fog
	float4 Color		: COLOR0;
};


VS_out main(in VS_in input)
{
	VS_out output;

	output.Position = mul(combinedMat, input.Position);
	float3 Vertex = mul(worldMat, input.Position).xyz;
	float3 Normal = mul(normalMat, input.Normal);

	output.TexCoord0.xy = input.TexCoord;

	output.Color = input.Prelight;
	output.Color.rgb *= ambient.rgb;
	output.Color.rgb += emissive.rgb*surfEmissive;

	output.Color = clamp(output.Color, 0.0, 1.0);
	output.Color.a *= matCol.a;

	output.TexCoord0.z = clamp((output.Position.w - fogEnd)*fogRange, fogDisable, 1.0);

	return output;
}
