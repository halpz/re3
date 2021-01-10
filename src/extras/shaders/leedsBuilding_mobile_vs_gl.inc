const char *leedsBuilding_mobile_vert_src =
"uniform vec4 u_amb;\n"
"uniform vec4 u_emiss;\n"

"#define surfEmissive (u_surfProps.w)\n"

"#define vertContrast (1.5)\n"
"#define vertBrightness (0.25)\n"
"#define ambientContrast (1.2)\n"
"#define ambientBrightness (0.1)\n"
"#define emissiveContrast (1.25)\n"
"#define emissiveBrightness (0.05)\n"


"VSIN(ATTRIB_POS)	vec3 in_pos;\n"

"VSOUT vec4 v_color;\n"
"VSOUT vec2 v_tex0;\n"
"VSOUT float v_fog;\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 Vertex = u_world * vec4(in_pos, 1.0);\n"
"	gl_Position = u_proj * u_view * Vertex;\n"
"	vec3 Normal = mat3(u_world) * in_normal;\n"

"	v_tex0 = in_tex0;\n"

"	vec4 vertCol = in_color;\n"
"	vec4 amb = u_amb;\n"
"	vec4 emiss = u_emiss;\n"

"	vertCol.xyz = ((vertCol.xyz - 0.5) * max(vertContrast, 0.0)) + 0.5;\n"
"	vertCol.xyz += vertBrightness;\n"
"	vertCol.xyz = max(vertCol.xyz, vec3(0.0,0.0,0.0));\n"
"	\n"
"	amb.xyz = ((amb.xyz - 0.5) * max(ambientContrast, 0.0)) + 0.5;\n"
"	amb.xyz += ambientBrightness;\n"
"	amb.xyz = max(amb.xyz, vec3(0.0,0.0,0.0));\n"
"	\n"
"	emiss.xyz = ((emiss.xyz - 0.5) * max(emissiveContrast, 0.0)) + 0.5;\n"
"	emiss.xyz += emissiveBrightness;\n"
"	emiss.xyz = max(emiss.xyz, vec3(0.0,0.0,0.0));\n"
"	v_color.xyz = emiss.xyz + (vertCol.xyz * amb.xyz);\n"
"	v_color.w = vertCol.w;\n"


"	v_color = clamp(v_color, 0.0, 1.0);\n"
"	v_color.a *= u_matColor.a;\n"

"	v_fog = DoFog(gl_Position.w);\n"
"}\n"
;
