const char *scale_frag_src =
"uniform sampler2D tex0;\n"
"uniform vec4 u_colorscale;\n"

"FSIN vec4 v_color;\n"
"FSIN vec2 v_tex0;\n"
"FSIN float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 color;\n"
"	color = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y))*u_colorscale;\n"
"	color.rgb = clamp(color.rgb, 0.0, 1.0);\n"
"	color.rgb = mix(u_fogColor.rgb, color.rgb, v_fog);\n"
"	DoAlphaTest(color.a);\n"

"	FRAGCOLOR(color);\n"
"}\n"

;
