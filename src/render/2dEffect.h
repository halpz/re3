class C2dEffect
{
public:
	struct Light {
		float dist;
		float outerRange;
		float size;
		float innerRange;
		uint8 flash;
		uint8 wet;
		uint8 flare;
		uint8 shadowIntens;
		uint8 flag;
		RwTexture *corona;
		RwTexture *shadow;
	};
	struct Particle {
		int particleType;
		float dir[3];
		float scale;
	};
	struct Attractor {
		CVector dir;
		uint8 flag;
		uint8 probability;
	};

	CVector pos;
	RwRGBA col;
	uint8 type;
	union {
		Light light;
		Particle particle;
		Attractor attractor;
	};

	C2dEffect(void) {}
};
static_assert(sizeof(C2dEffect) == 0x34, "C2dEffect: error");
