uniform vec4 u_amb;
uniform vec4 u_emiss;

#define surfEmissive (u_surfProps.w)

#define vertContrast (1.5)
#define vertBrightness (0.25)
#define ambientContrast (1.2)
#define ambientBrightness (0.1)
#define emissiveContrast (1.25)
#define emissiveBrightness (0.05)


VSIN(ATTRIB_POS)	vec3 in_pos;

VSOUT vec4 v_color;
VSOUT vec2 v_tex0;
VSOUT float v_fog;

void
main(void)
{
	vec4 Vertex = u_world * vec4(in_pos, 1.0);
	gl_Position = u_proj * u_view * Vertex;
	vec3 Normal = mat3(u_world) * in_normal;

	v_tex0 = in_tex0;

	vec4 vertCol = in_color;
	vec4 amb = u_amb;
	vec4 emiss = u_emiss;

	vertCol.xyz = ((vertCol.xyz - 0.5) * max(vertContrast, 0.0)) + 0.5;
	vertCol.xyz += vertBrightness;
	vertCol.xyz = max(vertCol.xyz, vec3(0.0,0.0,0.0));
	
	amb.xyz = ((amb.xyz - 0.5) * max(ambientContrast, 0.0)) + 0.5;
	amb.xyz += ambientBrightness;
	amb.xyz = max(amb.xyz, vec3(0.0,0.0,0.0));
	
	emiss.xyz = ((emiss.xyz - 0.5) * max(emissiveContrast, 0.0)) + 0.5;
	emiss.xyz += emissiveBrightness;
	emiss.xyz = max(emiss.xyz, vec3(0.0,0.0,0.0));
	v_color.xyz = emiss.xyz + (vertCol.xyz * amb.xyz);
	v_color.w = vertCol.w;


	v_color = clamp(v_color, 0.0, 1.0);
	v_color.a *= u_matColor.a;

	v_fog = DoFog(gl_Position.w);
}
