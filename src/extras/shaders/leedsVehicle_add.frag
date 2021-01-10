uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float u_fxparams;

#define shininess (u_fxparams)

FSIN vec4 v_color;
FSIN vec2 v_tex0;
FSIN vec2 v_tex1;
FSIN float v_fog;

void
main(void)
{
	vec4 pass1 = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));
	vec4 pass2 = texture(tex1, vec2(v_tex1.x, 1.0-v_tex1.y));
	pass2.a *= shininess;

	pass1.rgb = mix(u_fogColor.rgb, pass1.rgb, v_fog);
	pass2.rgb = mix(vec3(0.0, 0.0, 0.0), pass2.rgb, v_fog);

	// We simulate drawing this in two passes.
	// We premultiply alpha so render state should be one.
	vec4 color;
	color.rgb = pass1.rgb*pass1.a + pass2.rgb*pass2.a;
	color.a = pass1.a;

	DoAlphaTest(color.a);

	FRAGCOLOR(color);
}
