#include "standardConstants.h"

#define surfEmissive (surfProps.w)

#define vertContrast (1.5)
#define vertBrightness (0.25)
#define ambientContrast (1.2)
#define ambientBrightness (0.1)
#define emissiveContrast (1.25)
#define emissiveBrightness (0.05)

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

	float4 vertCol = input.Prelight;
	float4 amb = ambient;
	float4 emiss = emissive;

	vertCol.xyz = ((vertCol.xyz - 0.5) * max(vertContrast, 0.0)) + 0.5;
	vertCol.xyz += vertBrightness;
	vertCol.xyz = max(vertCol.xyz, float3(0.0,0.0,0.0));
	
	amb.xyz = ((amb.xyz - 0.5) * max(ambientContrast, 0.0)) + 0.5;
	amb.xyz += ambientBrightness;
	amb.xyz = max(amb.xyz, float3(0.0,0.0,0.0));
	
	emiss.xyz = ((emiss.xyz - 0.5) * max(emissiveContrast, 0.0)) + 0.5;
	emiss.xyz += emissiveBrightness;
	emiss.xyz = max(emiss.xyz, float3(0.0,0.0,0.0));
	output.Color.xyz = emiss.xyz + (vertCol.xyz * amb.xyz);
	output.Color.w = vertCol.w;

	output.Color = clamp(output.Color, 0.0, 1.0);
	output.Color.a *= matCol.a;

	output.TexCoord0.z = clamp((output.Position.w - fogEnd)*fogRange, fogDisable, 1.0);

	return output;
}
