const char *colourfilterLCS_frag_src =
"uniform sampler2D tex0;\n"
"uniform vec4 u_blurcolor;\n"

"FSIN vec4 v_color;\n"
"FSIN vec2 v_tex0;\n"
"FSIN float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 dst = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"
"	dst += dst*u_blurcolor;\n"

"	vec4 color;\n"
"	color.rgb = dst.rgb;\n"
"	color.a = 1.0;\n"

"	FRAGCOLOR(color);\n"
"}\n"

;
