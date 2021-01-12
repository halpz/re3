uniform vec4 u_amb;
uniform vec4 u_emiss;

VSIN(ATTRIB_POS)	vec3 in_pos;

VSOUT vec4 v_color;
VSOUT vec2 v_tex0;
VSOUT vec2 v_tex1;
VSOUT float v_fog;
VSOUT vec2 v_reflData;

#define v_NdotV (v_reflData.x)
#define v_lightingCont (v_reflData.y)

void
main(void)
{
	vec4 Vertex = u_world * vec4(in_pos, 1.0);
	gl_Position = u_proj * u_view * Vertex;
	vec3 Normal = mat3(u_world) * in_normal;

	v_tex0 = in_tex0;

	vec3 ViewNormal = mat3(u_view) * Normal;
	v_tex1 = (ViewNormal.xy + vec2(1.0, 1.0))*0.5;

	v_color = in_color;
	vec4 combinedAmbient = mix(u_emiss, u_amb, Normal.z);
	v_color.rgb += combinedAmbient.rgb*surfAmbient;
	v_color.rgb += DoDynamicLight(Vertex.xyz, Normal)*surfDiffuse;
	v_lightingCont = max(0.5, (v_color.r + v_color.g + v_color.b) / 3.0);
	v_color *= u_matColor;

	// for fresnel
	vec3 camPos = -u_view[3].xyz * mat3(u_view);
	vec3 viewVec = normalize(Vertex.xyz - camPos);
	v_NdotV = 1.0 - dot(-Normal.xyz, viewVec.xyz);

	v_fog = DoFog(gl_Position.w);
}
