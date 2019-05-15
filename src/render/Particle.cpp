#include "common.h"
#include "patcher.h"
#include "Particle.h"

WRAPPER void
CParticle::AddParticle(tParticleType, const CVector &pos, const CVector &velocity, CEntity *ent,
		float size, int32 rotationStep, int32 rotation, int startFrame, int lifeSpan)
{
	EAXJMP(0x50D140);
}
