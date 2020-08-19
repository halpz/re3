uniform sampler2D tex0;

uniform vec4 u_reflProps;

#define glossMult (u_reflProps.x)

in vec3 v_normal;
in vec3 v_light;
in vec2 v_tex0;
in float v_fog;

out vec4 color;

void
main(void)
{
	color = texture(tex0, vec2(v_tex0.x, 1.0-v_tex0.y));
	vec3 n = 2.0*v_normal-1.0;            // unpack
	vec3 v = 2.0*v_light-1.0;             //

	float s = dot(n, v);
	color = s*s*s*s*s*s*s*s*color*v_fog*glossMult;

	DoAlphaTest(color.a);
}

