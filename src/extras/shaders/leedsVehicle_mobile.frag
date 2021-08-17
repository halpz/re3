uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float u_shininess;
uniform vec3 u_skyTop;
uniform vec3 u_skyBot;

// matfx:
// case 1	normal envmap
// 	custom1 (4.0,  1.0, 1.0, coef)
// 	custom2 (0.25, 3.0, 1.0, 1.0)
// case 2	too strong
// 	custom1 (4.0, 1.0, 2.0, coef)
// 	custom2 (0.5, 3.0, 1.0, 1.0)
// ???:		practically no fresnel
// 	custom1 (4.0, 1.25, 0.01, coef)
// 	custom2 (1.0, 2.0,  1.1,  2.0)

#define power (4.0)

#define preMult (1.0)
#define postMult (1.0)
#define minRefl (0.25)
#define maxRefl (3.0)
#define minOpacity (1.0)
#define maxOpacity (1.0)

//#define preMult (1.0)
//#define postMult (2.0)
//#define minRefl (0.5)
//#define maxRefl (3.0)
//#define minOpacity (1.0)
//#define maxOpacity (1.0)

//#define preMult (1.25)
//#define postMult (0.01)
//#define minRefl (1.0)
//#define maxRefl (2.0)
//#define minOpacity (1.1)
//#define maxOpacity (2.0)

FSIN vec4 v_color;
FSIN vec2 v_tex0;
FSIN vec2 v_tex1;
FSIN float v_fog;
FSIN vec2 v_reflData;

#define v_NdotV (v_reflData.x)
#define v_lightingCont (v_reflData.y)

void
main(void)
{
	vec4 pass1 = v_color*texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));

	vec3 envtex = texture(tex1, v_tex1).rgb;	// V flipped
	vec3 skyColour = mix(u_skyBot, u_skyTop, envtex.g);
	vec3 envOut = mix(envtex.rrr, skyColour, envtex.b);

	float fresnel = mix(u_shininess, u_shininess * 2.0, v_NdotV);
	fresnel = pow(v_NdotV * preMult, power);
	fresnel = clamp(fresnel * postMult, 0.0, 1.0);
	float reflectivity = v_lightingCont * mix(minRefl, maxRefl, fresnel)*u_shininess;

	float opacity = mix(minOpacity, maxOpacity, fresnel)*pass1.a;
	vec4 color = pass1 + vec4(reflectivity * envOut, 0.0);
	color.a = opacity;

	color.rgb = mix(u_fogColor.rgb, color.rgb, v_fog);

	DoAlphaTest(color.a);

	FRAGCOLOR(color);
}
