#include "standardConstants.h"

float4x4	texMat	: register(c41);

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
	float2 TexCoord1	: TEXCOORD1;
	float4 Color		: COLOR0;
};


VS_out main(in VS_in input)
{
	VS_out output;

	output.Position = mul(combinedMat, input.Position);
	float3 V = mul(worldMat, input.Position).xyz;
	float3 N = mul(normalMat, input.Normal);

	output.TexCoord0.xy = input.TexCoord;
	output.TexCoord1 = mul(texMat, float4(N, 1.0)).xy;

	output.Color = input.Prelight;
	output.Color.rgb += ambientLight.rgb * surfAmbient;

	int i;
	for(i = 0; i < numDirLights; i++)
		output.Color.xyz += DoDirLight(lights[i+firstDirLight], N)*surfDiffuse;
	// PS2 clamps before material color
	output.Color = clamp(output.Color, 0.0, 1.0);
	output.Color *= matCol;

	output.TexCoord0.z = clamp((output.Position.w - fogEnd)*fogRange, fogDisable, 1.0);

	return output;
}
