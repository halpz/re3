#include "standardConstants.h"

#ifdef ENVMAP
float4x4	texMat	: register(c41);
#endif
#ifdef SKIN
float4x3 boneMatrices[64] : register(c41);
#endif

struct VS_in
{
	float4 Position		: POSITION;
	float3 Normal		: NORMAL;
	float2 TexCoord		: TEXCOORD0;
	float4 Prelight		: COLOR0;
#ifdef SKIN
	float4 Weights		: BLENDWEIGHT;
	int4 Indices		: BLENDINDICES;
#endif
};

struct VS_out {
	float4 Position		: POSITION;
	float3 TexCoord0	: TEXCOORD0;	// also fog
#ifdef ENVMAP
	float2 TexCoord1	: TEXCOORD1;
#endif
	float4 Color		: COLOR0;
};


VS_out main(in VS_in input)
{
	VS_out output;

#ifdef SKIN
	int j;
	float3 SkinVertex = float3(0.0, 0.0, 0.0);
	float3 SkinNormal = float3(0.0, 0.0, 0.0);
	for(j = 0; j < 4; j++){
		SkinVertex += mul(input.Position, boneMatrices[input.Indices[j]]).xyz * input.Weights[j];
		SkinNormal += mul(input.Normal, (float3x3)boneMatrices[input.Indices[j]]).xyz * input.Weights[j];
	}
	output.Position = mul(combinedMat, SkinVertex);
//	float3 V = mul(worldMat, SkinVertex).xyz;
	float3 N = mul(normalMat, SkinNormal);
#else
	output.Position = mul(combinedMat, input.Position);
//	float3 V = mul(worldMat, input.Position).xyz;
	float3 N = mul(normalMat, input.Normal);
#endif

	output.TexCoord0.xy = input.TexCoord;
#ifdef ENVMAP
	output.TexCoord1 = mul(texMat, float4(N, 1.0)).xy;
#endif

	output.Color = input.Prelight;
	output.Color.rgb += ambientLight.rgb * surfAmbient;

	int i;
	for(i = 0; i < numDirLights; i++)
		output.Color.xyz += DoDirLight(lights[i+firstDirLight], N)*surfDiffuse;
	// PS2 clamps before material color
	// PSP clamps after...maybe another constant for this?
	output.Color = clamp(output.Color, 0.0, 1.0);
	output.Color *= matCol;

	output.TexCoord0.z = clamp((output.Position.w - fogEnd)*fogRange, fogDisable, 1.0);

	return output;
}
