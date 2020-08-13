const char *colourfilterVC_frag_src =
"uniform sampler2D tex0;\n"
"uniform vec4 u_blurcolor;\n"

"in vec4 v_color;\n"
"in vec2 v_tex0;\n"
"in float v_fog;\n"

"out vec4 color;\n"

"void\n"
"main(void)\n"
"{\n"
"	float a = u_blurcolor.a;\n"

"	vec4 doublec = clamp(u_blurcolor*2, 0.0, 1.0);\n"
"	vec4 dst = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"
"	vec4 prev = dst;\n"
"	for(int i = 0; i < 5; i++){\n"
"//		vec4 doublec = clamp(u_blurcolor*2, 0.0, 1.0);\n"
"		vec4 tmp = dst*(1.0-a) + prev*doublec*a;\n"
"		tmp += prev*u_blurcolor;\n"
"		tmp += prev*u_blurcolor;\n"
"		prev = clamp(tmp, 0.0, 1.0);\n"
"	}\n"
"	color.rgb = prev.rgb;\n"
"	color.a = 1.0f;\n"
"}\n"

;
