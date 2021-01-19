struct VS_out {
	float4 Position		: POSITION;
	float3 TexCoord0	: TEXCOORD0;
	float4 Color		: COLOR0;
};

sampler2D tex0 : register(s0);

float4 fogColor : register(c0);
float4 colorscale : register(c1);

float4 main(VS_out input) : COLOR
{
	float4 color = input.Color;
	color *= tex2D(tex0, input.TexCoord0.xy)*colorscale;
	color.rgb = clamp(color.rgb, 0.0, 1.0);
	color.rgb = lerp(fogColor.rgb, color.rgb, input.TexCoord0.z);
	return color;
}
