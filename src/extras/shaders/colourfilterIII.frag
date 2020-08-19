uniform sampler2D tex0;
uniform vec4 u_blurcolor;

in vec4 v_color;
in vec2 v_tex0;
in float v_fog;

out vec4 color;

void
main(void)
{
	float a = u_blurcolor.a;
	vec4 dst = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));
	vec4 prev = dst;
	for(int i = 0; i < 5; i++){
		vec4 tmp = dst*(1.0-a) + prev*u_blurcolor*a;
		prev = clamp(tmp, 0.0, 1.0);
	}
	color.rgb = prev.rgb;
	color.a = 1.0f;
}

