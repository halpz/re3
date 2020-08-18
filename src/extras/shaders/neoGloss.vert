uniform vec3 u_eye;


layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec4 in_color;
layout(location = 3) in vec2 in_tex0;

out vec3 v_normal;
out vec3 v_light;
out vec2 v_tex0;
out float v_fog;

void
main(void)
{
	vec4 Vertex = u_world * vec4(in_pos, 1.0);
	gl_Position = u_proj * u_view * Vertex;
	vec3 Normal = mat3(u_world) * in_normal;

	v_tex0 = in_tex0;

	vec3 viewVec = normalize(u_eye - Vertex.xyz);
	vec3 Light = normalize(viewVec - u_lightDirection[0].xyz);
	v_normal = 0.5*(1.0 + vec3(0.0, 0.0, 1.0));    // compress
	v_light  = 0.5*(1.0 + Light);                  //

	v_fog = DoFog(gl_Position.w);
}
