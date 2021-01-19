struct VS_out {
	float4 Position		: POSITION;
	float3 TexCoord0	: TEXCOORD0;
	float2 TexCoord1	: TEXCOORD1;
	float2 ReflData		: TEXCOORD2;
	float4 Color		: COLOR0;
};

#define NdotV (input.ReflData.x)
#define lightingCont (input.ReflData.y)

sampler2D diffTex : register(s0);
sampler2D envTex : register(s1);

float4 fogColor : register(c0);

float4 fxparams : register(c2);
float3 skyTop : register(c3);
float3 skyBot : register(c4);

#define shininess (fxparams.x)

#define power (4.0)

#define preMult (1.0)
#define postMult (1.0)
#define minRefl (0.25)
#define maxRefl (3.0)
#define minOpacity (1.0)
#define maxOpacity (1.0)


float4 main(VS_out input) : COLOR
{
	float4 pass1 = input.Color*tex2D(diffTex, input.TexCoord0.xy);

	float3 envtex = tex2D(envTex, float2(input.TexCoord1.x, 1.0-input.TexCoord1.y)).rgb;	// V flipped
	float3 skyColour = lerp(skyBot, skyTop, envtex.g);
	float3 envOut = lerp(envtex.rrr, skyColour, envtex.b);

	float fresnel = lerp(shininess, shininess * 2.0, NdotV);
	fresnel = pow(NdotV * preMult, power);
	fresnel = clamp(fresnel * postMult, 0.0, 1.0);
	float reflectivity = lightingCont * lerp(minRefl, maxRefl, fresnel)*shininess;

	float opacity = lerp(minOpacity, maxOpacity, fresnel)*pass1.a;
	float4 color = pass1 + float4(reflectivity * envOut, 0.0);
	color.a = opacity;

	color.rgb = lerp(fogColor.rgb, color.rgb, input.TexCoord0.z);

	return color;
}
