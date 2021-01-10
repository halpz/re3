struct VS_out {
	float4 Position		: POSITION;
	float3 TexCoord0	: TEXCOORD0;
	float2 TexCoord1	: TEXCOORD1;
	float4 Color		: COLOR0;
};

sampler2D diffTex : register(s0);
sampler2D envTex : register(s1);

float4 fogColor : register(c0);

float4 fxparams : register(c1);

#define shininess (fxparams.x)

float4 main(VS_out input) : COLOR
{
	float4 pass1 = input.Color*tex2D(diffTex, input.TexCoord0.xy);
	float4 pass2 = tex2D(envTex, input.TexCoord1.xy);
	pass2.a *= shininess;

	pass1.rgb = lerp(fogColor.rgb, pass1.rgb, input.TexCoord0.z);
	pass2.rgb = lerp(float3(0.0, 0.0, 0.0), pass2.rgb, input.TexCoord0.z);

	// We simulate drawing this in two passes.
	// We premultiply alpha so render state should be one.
	float4 color;
	color.rgb = pass1.rgb*pass1.a*(1.0-pass2.a) + pass2.rgb*pass2.a;
	color.a = pass1.a*(1.0-pass2.a) + pass2.a;

	return color;
}
