const char *leedsVehicle_add_frag_src =
"uniform sampler2D tex0;\n"
"uniform sampler2D tex1;\n"

"uniform float u_fxparams;\n"

"#define shininess (u_fxparams)\n"

"FSIN vec4 v_color;\n"
"FSIN vec2 v_tex0;\n"
"FSIN vec2 v_tex1;\n"
"FSIN float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 pass1 = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"
"	vec4 pass2 = texture(tex1, vec2(v_tex1.x, 1.0-v_tex1.y));\n"
"	pass2.a *= shininess;\n"

"	pass1.rgb = mix(u_fogColor.rgb, pass1.rgb, v_fog);\n"
"	pass2.rgb = mix(vec3(0.0, 0.0, 0.0), pass2.rgb, v_fog);\n"

"	// We simulate drawing this in two passes.\n"
"	// We premultiply alpha so render state should be one.\n"
"	vec4 color;\n"
"	color.rgb = pass1.rgb*pass1.a + pass2.rgb*pass2.a;\n"
"	color.a = pass1.a;\n"

"	DoAlphaTest(color.a);\n"

"	FRAGCOLOR(color);\n"
"}\n"
;
