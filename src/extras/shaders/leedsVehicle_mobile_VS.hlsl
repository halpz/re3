#include "standardConstants.h"

float4		emissive	: register(c41);
float4		ambient		: register(c42);
float4x4	viewMat		: register(c43);

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
	float2 ReflData		: TEXCOORD2;
	float4 Color		: COLOR0;
};

#define NdotV (output.ReflData.x)
#define lightingCont (output.ReflData.y)

VS_out main(in VS_in input)
{
	VS_out output;

	output.Position = mul(combinedMat, input.Position);
	float3 V = mul(worldMat, input.Position).xyz;
	float3 N = mul(normalMat, input.Normal);

	output.TexCoord0.xy = input.TexCoord;

	float4 ViewNormal = mul(viewMat, float4(N, 0.0));
	output.TexCoord1 = (ViewNormal.xy + float2(1.0, 1.0))*0.5;

	output.Color = input.Prelight;
	float4 combinedAmbient = lerp(emissive, ambient, N.z);
	output.Color.rgb += combinedAmbient.rgb * surfAmbient;

	int i;
	for(i = 0; i < numDirLights; i++)
		output.Color.xyz += DoDirLight(lights[i+firstDirLight], N)*surfDiffuse;
	lightingCont = max(0.5, (output.Color.r + output.Color.g + output.Color.b) / 3.0);
	output.Color *= matCol;

	// for fresnel
	float3 camPos = mul(-viewMat._m03_m13_m23, (float3x3)(viewMat));
	float3 viewVec = normalize(V.xyz - camPos);
	NdotV = 1.0 - dot(-N.xyz, viewVec.xyz);

	output.TexCoord0.z = clamp((output.Position.w - fogEnd)*fogRange, fogDisable, 1.0);

	return output;
}
