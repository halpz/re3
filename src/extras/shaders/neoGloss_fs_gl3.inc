const char *neoGloss_frag_src =
"uniform sampler2D tex0;\n"

"uniform vec4 u_reflProps;\n"

"#define glossMult (u_reflProps.x)\n"

"in vec3 v_normal;\n"
"in vec3 v_light;\n"
"in vec2 v_tex0;\n"
"in float v_fog;\n"

"out vec4 color;\n"

"void\n"
"main(void)\n"
"{\n"
"	color = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"
"	vec3 n = 2.0*v_normal-1.0;            // unpack\n"
"	vec3 v = 2.0*v_light-1.0;             //\n"

"	float s = dot(n, v);\n"
"	color = s*s*s*s*s*s*s*s*color*v_fog*glossMult;\n"

"	DoAlphaTest(color.a);\n"
"}\n"

;
