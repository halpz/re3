uniform sampler2D tex0;
uniform vec4 u_colorscale;

FSIN vec4 v_color;
FSIN vec2 v_tex0;
FSIN float v_fog;

void
main(void)
{
	vec4 color;
	color = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y))*u_colorscale;
	color.rgb = clamp(color.rgb, 0.0, 1.0);
	color.rgb = mix(u_fogColor.rgb, color.rgb, v_fog);
	DoAlphaTest(color.a);

	FRAGCOLOR(color);
}

