uniform sampler2D tex0;

in vec4 v_color;
in vec2 v_tex0;
in float v_fog;

out vec4 color;

void
main(void)
{
	color = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));
	color.rgb = mix(u_fogColor.rgb, color.rgb, v_fog);
	DoAlphaTest(color.a);
}

