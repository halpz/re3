struct VS_out {
	float4 Position		: POSITION;
	float3 TexCoord0	: TEXCOORD0;
#if defined(PASS_BLEND) || defined(PASS_ADD)
	float2 TexCoord1	: TEXCOORD1;
#endif
	float4 Color		: COLOR0;
};

sampler2D diffTex : register(s0);
sampler2D envTex : register(s1);

float4 fogColor : register(c0);

float4 colorscale : register(c1);
float4 fxparams : register(c2);

#define shininess (fxparams.x)

float4 main(VS_out input) : COLOR
{
	float4 pass1 = input.Color*tex2D(diffTex, input.TexCoord0.xy)*colorscale;
	pass1.rgb = clamp(pass1.rgb, 0.0, 1.0);
	pass1.rgb = lerp(fogColor.rgb, pass1.rgb, input.TexCoord0.z);

	float4 color;
#if defined(PASS_BLEND) || defined(PASS_ADD)
	float4 pass2 = tex2D(envTex, input.TexCoord1.xy);
	pass2.a *= shininess;
	pass2.rgb = lerp(float3(0.0, 0.0, 0.0), pass2.rgb, input.TexCoord0.z);

	// We simulate drawing this in two passes.
#if defined(PASS_ADD)
	// First pass with standard blending, second with addition
	// We premultiply alpha so render state should be one.
	color.rgb = pass1.rgb*pass1.a + pass2.rgb*pass2.a;
	color.a = pass1.a;
#elif defined(PASS_BLEND)
	// We premultiply alpha so render state should be one.
	color.rgb = pass1.rgb*pass1.a*(1.0-pass2.a) + pass2.rgb*pass2.a;
	color.a = pass1.a*(1.0-pass2.a) + pass2.a;
#endif

#else
	color = pass1;
#endif

	return color;
}
