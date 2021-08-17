const char *leedsDefault_frag_src =
"uniform sampler2D tex0;\n"
"uniform sampler2D tex1;\n"

"uniform float u_shininess;\n"
"uniform vec4 u_colorscale;\n"

"FSIN vec4 v_color;\n"
"FSIN vec2 v_tex0;\n"
"#if defined(PASS_BLEND) || defined(PASS_ADD)\n"
"FSIN vec2 v_tex1;\n"
"#endif\n"
"FSIN float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 pass1 = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y))*u_colorscale;\n"
"	pass1.rgb = clamp(pass1.rgb, 0.0, 1.0);\n"
"	pass1.rgb = mix(u_fogColor.rgb, pass1.rgb, v_fog);\n"

"	vec4 color;\n"
"#if defined(PASS_BLEND) || defined(PASS_ADD)\n"
"	vec4 pass2 = texture(tex1, vec2(v_tex1.x, 1.0-v_tex1.y));\n"
"	pass2.a *= u_shininess;\n"
"	pass2.rgb = mix(vec3(0.0, 0.0, 0.0), pass2.rgb, v_fog);\n"

"	// We simulate drawing this in two passes.\n"
"#if defined(PASS_ADD)\n"
"	// First pass with standard blending, second with addition\n"
"	// We premultiply alpha so render state should be one.\n"
"	color.rgb = pass1.rgb*pass1.a + pass2.rgb*pass2.a;\n"
"	color.a = pass1.a;\n"
"#elif defined(PASS_BLEND)\n"
"	// We premultiply alpha so render state should be one.\n"
"	color.rgb = pass1.rgb*pass1.a*(1.0-pass2.a) + pass2.rgb*pass2.a;\n"
"	color.a = pass1.a*(1.0-pass2.a) + pass2.a;\n"
"#endif\n"

"#else\n"
"	color = pass1;\n"
"#endif\n"

"	DoAlphaTest(color.a);\n"

"	FRAGCOLOR(color);\n"
"}\n"
;
