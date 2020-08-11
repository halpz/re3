uniform sampler2D tex0;
uniform vec3 u_contrastAdd;
uniform vec3 u_contrastMult;

in vec4 v_color;
in vec2 v_tex0;
in float v_fog;

out vec4 color;

void
main(void)
{
	vec4 dst = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));
	color.rgb = dst.rgb*u_contrastMult + u_contrastAdd;
	color.a = 1.0f;
}

