enum {
	EFFECT_LIGHT,
	EFFECT_PARTICLE,
	EFFECT_ATTRACTOR
};

class C2dEffect
{
public:
	struct Light {
		float dist;
		float outerRange;
		float size;
		float innerRange;
		uint8 flash;
		uint8 roadReflection;
		uint8 flareType;
		uint8 shadowIntensity;
		uint8 flags;
		RwTexture *corona;
		RwTexture *shadow;
	};
	struct Particle {
		int particleType;
		CVector dir;
		float scale;
	};
	struct Attractor {
		CVector dir;
		uint8 flags;
		uint8 probability;
	};

	CVector pos;
	CRGBA col;
	uint8 type;
	union {
		Light light;
		Particle particle;
		Attractor attractor;
	};

	C2dEffect(void) {}
	void Shutdown(void){
		if(type == 0){	// TODO: enum
			if(light.corona)
				RwTextureDestroy(light.corona);
			if(light.shadow)
				RwTextureDestroy(light.shadow);
		}
	}
};
static_assert(sizeof(C2dEffect) == 0x34, "C2dEffect: error");
