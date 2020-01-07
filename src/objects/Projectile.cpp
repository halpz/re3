#include "common.h"
#include "patcher.h"
#include "Projectile.h"

CProjectile::CProjectile(int32 model) : CObject()
{
	m_fMass = 1.0f;
	m_fTurnMass = 1.0f;
	m_fAirResistance = 0.99f;
	m_fElasticity = 0.75f;
	m_fBuoyancy = GRAVITY * m_fMass * 0.1f;
	bExplosionProof = true;
	SetModelIndex(model);
	ObjectCreatedBy = MISSION_OBJECT;
}

class CProjectile_ : public CProjectile
{
public:
	CProjectile* ctor(int32 model) { return ::new (this) CProjectile(model); }
	void dtor(void) { CProjectile::~CProjectile(); }
};

STARTPATCHES
	InjectHook(0x4BFE30, &CProjectile_::ctor, PATCH_JUMP);
	InjectHook(0x4BFED0, &CProjectile_::dtor, PATCH_JUMP);
ENDPATCHES
