uniform vec4 u_xform;

layout(location = 0) in vec4 in_pos;
layout(location = 2) in vec4 in_color;
layout(location = 3) in vec2 in_tex0;

out vec4 v_color;
out vec2 v_tex0;
out float v_fog;

void
main(void)
{
	gl_Position = in_pos;
	gl_Position.w = 1.0;
	gl_Position.xy = gl_Position.xy * u_xform.xy + u_xform.zw;
	v_fog = DoFog(gl_Position.z);
	gl_Position.xyz *= gl_Position.w;
	v_color = in_color;
	v_tex0 = in_tex0;
}
