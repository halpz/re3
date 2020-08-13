const char *contrast_frag_src =
"uniform sampler2D tex0;\n"
"uniform vec3 u_contrastAdd;\n"
"uniform vec3 u_contrastMult;\n"

"in vec4 v_color;\n"
"in vec2 v_tex0;\n"
"in float v_fog;\n"

"out vec4 color;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 dst = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"
"	color.rgb = dst.rgb*u_contrastMult + u_contrastAdd;\n"
"	color.a = 1.0f;\n"
"}\n"

;
