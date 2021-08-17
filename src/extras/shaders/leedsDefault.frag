uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float u_shininess;
uniform vec4 u_colorscale;

FSIN vec4 v_color;
FSIN vec2 v_tex0;
#if defined(PASS_BLEND) || defined(PASS_ADD)
FSIN vec2 v_tex1;
#endif
FSIN float v_fog;

void
main(void)
{
	vec4 pass1 = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y))*u_colorscale;
	pass1.rgb = clamp(pass1.rgb, 0.0, 1.0);
	pass1.rgb = mix(u_fogColor.rgb, pass1.rgb, v_fog);

	vec4 color;
#if defined(PASS_BLEND) || defined(PASS_ADD)
	vec4 pass2 = texture(tex1, vec2(v_tex1.x, 1.0-v_tex1.y));
	pass2.a *= u_shininess;
	pass2.rgb = mix(vec3(0.0, 0.0, 0.0), pass2.rgb, v_fog);

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

	DoAlphaTest(color.a);

	FRAGCOLOR(color);
}
