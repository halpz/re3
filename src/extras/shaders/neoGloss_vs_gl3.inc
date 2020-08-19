const char *neoGloss_vert_src =
"uniform vec3 u_eye;\n"


"layout(location = 0) in vec3 in_pos;\n"
"layout(location = 1) in vec3 in_normal;\n"
"layout(location = 2) in vec4 in_color;\n"
"layout(location = 3) in vec2 in_tex0;\n"

"out vec3 v_normal;\n"
"out vec3 v_light;\n"
"out vec2 v_tex0;\n"
"out float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 Vertex = u_world * vec4(in_pos, 1.0);\n"
"	gl_Position = u_proj * u_view * Vertex;\n"
"	vec3 Normal = mat3(u_world) * in_normal;\n"

"	v_tex0 = in_tex0;\n"

"	vec3 viewVec = normalize(u_eye - Vertex.xyz);\n"
"	vec3 Light = normalize(viewVec - u_lightDirection[0].xyz);\n"
"	v_normal = 0.5*(1.0 + vec3(0.0, 0.0, 1.0));    // compress\n"
"	v_light  = 0.5*(1.0 + Light);                  //\n"

"	v_fog = DoFog(gl_Position.w);\n"
"}\n"
;
