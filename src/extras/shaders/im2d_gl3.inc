const char *im2d_vert_src =
"uniform vec4 u_xform;\n"

"layout(location = 0) in vec4 in_pos;\n"
"layout(location = 2) in vec4 in_color;\n"
"layout(location = 3) in vec2 in_tex0;\n"

"out vec4 v_color;\n"
"out vec2 v_tex0;\n"
"out float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	gl_Position = in_pos;\n"
"	gl_Position.w = 1.0;\n"
"	gl_Position.xy = gl_Position.xy * u_xform.xy + u_xform.zw;\n"
"	v_fog = DoFog(gl_Position.z);\n"
"	gl_Position.xyz *= gl_Position.w;\n"
"	v_color = in_color;\n"
"	v_tex0 = in_tex0;\n"
"}\n"
;
