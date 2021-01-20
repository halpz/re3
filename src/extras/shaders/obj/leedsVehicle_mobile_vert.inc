const char *leedsVehicle_mobile_vert_src =
"uniform vec4 u_amb;\n"
"uniform vec4 u_emiss;\n"

"VSIN(ATTRIB_POS)	vec3 in_pos;\n"

"VSOUT vec4 v_color;\n"
"VSOUT vec2 v_tex0;\n"
"VSOUT vec2 v_tex1;\n"
"VSOUT float v_fog;\n"
"VSOUT vec2 v_reflData;\n"

"#define v_NdotV (v_reflData.x)\n"
"#define v_lightingCont (v_reflData.y)\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 Vertex = u_world * vec4(in_pos, 1.0);\n"
"	gl_Position = u_proj * u_view * Vertex;\n"
"	vec3 Normal = mat3(u_world) * in_normal;\n"

"	v_tex0 = in_tex0;\n"

"	vec3 ViewNormal = mat3(u_view) * Normal;\n"
"	v_tex1 = (ViewNormal.xy + vec2(1.0, 1.0))*0.5;\n"

"	v_color = in_color;\n"
"	vec4 combinedAmbient = mix(u_emiss, u_amb, Normal.z);\n"
"	v_color.rgb += combinedAmbient.rgb*surfAmbient;\n"
"	v_color.rgb += DoDynamicLight(Vertex.xyz, Normal)*surfDiffuse;\n"
"	v_lightingCont = max(0.5, (v_color.r + v_color.g + v_color.b) / 3.0);\n"
"	v_color *= u_matColor;\n"

"	// for fresnel\n"
"	vec3 camPos = -u_view[3].xyz * mat3(u_view);\n"
"	vec3 viewVec = normalize(Vertex.xyz - camPos);\n"
"	v_NdotV = 1.0 - dot(-Normal.xyz, viewVec.xyz);\n"

"	v_fog = DoFog(gl_Position.w);\n"
"}\n"
;
