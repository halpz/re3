const char *leedsVehicle_mobile_frag_src =
"uniform sampler2D tex0;\n"
"uniform sampler2D tex1;\n"

"uniform float u_shininess;\n"
"uniform vec3 u_skyTop;\n"
"uniform vec3 u_skyBot;\n"

"// matfx:\n"
"// case 1	normal envmap\n"
"// 	custom1 (4.0,  1.0, 1.0, coef)\n"
"// 	custom2 (0.25, 3.0, 1.0, 1.0)\n"
"// case 2	too strong\n"
"// 	custom1 (4.0, 1.0, 2.0, coef)\n"
"// 	custom2 (0.5, 3.0, 1.0, 1.0)\n"
"// ???:		practically no fresnel\n"
"// 	custom1 (4.0, 1.25, 0.01, coef)\n"
"// 	custom2 (1.0, 2.0,  1.1,  2.0)\n"

"#define power (4.0)\n"

"#define preMult (1.0)\n"
"#define postMult (1.0)\n"
"#define minRefl (0.25)\n"
"#define maxRefl (3.0)\n"
"#define minOpacity (1.0)\n"
"#define maxOpacity (1.0)\n"

"//#define preMult (1.0)\n"
"//#define postMult (2.0)\n"
"//#define minRefl (0.5)\n"
"//#define maxRefl (3.0)\n"
"//#define minOpacity (1.0)\n"
"//#define maxOpacity (1.0)\n"

"//#define preMult (1.25)\n"
"//#define postMult (0.01)\n"
"//#define minRefl (1.0)\n"
"//#define maxRefl (2.0)\n"
"//#define minOpacity (1.1)\n"
"//#define maxOpacity (2.0)\n"

"FSIN vec4 v_color;\n"
"FSIN vec2 v_tex0;\n"
"FSIN vec2 v_tex1;\n"
"FSIN float v_fog;\n"
"FSIN vec2 v_reflData;\n"

"#define v_NdotV (v_reflData.x)\n"
"#define v_lightingCont (v_reflData.y)\n"

"void\n"
"main(void)\n"
"{\n"
"	vec4 pass1 = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));\n"

"	vec3 envtex = texture(tex1, v_tex1).rgb;	// V flipped\n"
"	vec3 skyColour = mix(u_skyBot, u_skyTop, envtex.g);\n"
"	vec3 envOut = mix(envtex.rrr, skyColour, envtex.b);\n"

"	float fresnel = mix(u_shininess, u_shininess * 2.0, v_NdotV);\n"
"	fresnel = pow(v_NdotV * preMult, power);\n"
"	fresnel = clamp(fresnel * postMult, 0.0, 1.0);\n"
"	float reflectivity = v_lightingCont * mix(minRefl, maxRefl, fresnel)*u_shininess;\n"

"	float opacity = mix(minOpacity, maxOpacity, fresnel)*pass1.a;\n"
"	vec4 color = pass1 + vec4(reflectivity * envOut, 0.0);\n"
"	color.a = opacity;\n"

"	color.rgb = mix(u_fogColor.rgb, color.rgb, v_fog);\n"

"	DoAlphaTest(color.a);\n"

"	FRAGCOLOR(color);\n"
"}\n"
;
