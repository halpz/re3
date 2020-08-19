const char *neoVehicle_frag_src =
"uniform sampler2D tex0;\n"
"uniform sampler2D tex1;\n"

"in vec4 v_color;\n"
"in vec4 v_reflcolor;\n"
"in vec2 v_tex0;\n"
"in vec2 v_tex1;\n"
"in float v_fog;\n"

"out vec4 color;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 pass1 = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"
"	vec3 envmap = texture(tex1, vec2(v_tex1.x, 1.0-v_tex1.y)).rgb;\n"
"	pass1.rgb = mix(pass1.rgb, envmap, v_reflcolor.a);\n"
"	pass1.rgb = mix(u_fogColor.rgb, pass1.rgb, v_fog);\n"
"//	pass1.rgb += v_reflcolor.rgb * v_fog;\n"

"	vec3 pass2 = v_reflcolor.rgb * v_fog;\n"

"	color.rgb = pass1.rgb*pass1.a + pass2;\n"
"	color.a = pass1.a;\n"

"//	color.rgb = mix(u_fogColor.rgb, color.rgb, v_fog);\n"
"	DoAlphaTest(color.a);\n"
"}\n"
;
