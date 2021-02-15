sampler2D tex : register(s0);
float4 blurcol : register(c10);

//float4 blurcols[10] : register(c15);


float4 main(in float2 texcoord : TEXCOORD0) : COLOR0
{
	float a = blurcol.a;

	float4 doublec = saturate(blurcol*2);
	float4 dst = tex2D(tex, texcoord.xy);
	float4 prev = dst;
	for(int i = 0; i < 5; i++){
//		float4 doublec = saturate(blurcol*2);
		float4 tmp = dst*(1-a) + prev*doublec*a;
		tmp += prev*blurcol;
		tmp += prev*blurcol;
		prev = saturate(tmp);
	}
	prev.a = 1.0;
	return prev;
}
