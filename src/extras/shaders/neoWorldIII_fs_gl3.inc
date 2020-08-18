const char *neoWorldIII_frag_src =
"uniform sampler2D tex0;\n"
"uniform sampler2D tex1;\n"

"uniform vec4 u_lightMap;\n"

"in vec4 v_color;\n"
"in vec2 v_tex0;\n"
"in vec2 v_tex1;\n"
"in float v_fog;\n"

"out vec4 color;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 t0 = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"
"	vec4 t1 = texture(tex1, vec2(v_tex1.x, 1.0-v_tex1.y));\n"

"	color = t0*v_color*(1 + u_lightMap*(2*t1-1));\n"
"	color.a = v_color.a*t0.a*u_lightMap.a;\n"

"	color.rgb = mix(u_fogColor.rgb, color.rgb, v_fog);\n"
"	DoAlphaTest(color.a);\n"
"}\n"

;
