#include "common.h"
#include "patcher.h"
#include "ParticleObject.h"

WRAPPER void CParticleObject::AddObject(uint16 type, const CVector &pos, uint8 remove) { EAXJMP(0x4BC4D0); }
WRAPPER void CParticleObject::AddObject(uint16 type, const CVector &pos, float size, uint8 remove) { EAXJMP(0x4BC520); }
WRAPPER void CParticleObject::AddObject(uint16 type, const CVector &pos, const CVector &dir, float size, uint8 remove) { EAXJMP(0x4BC570); }
WRAPPER void CParticleObject::AddObject(uint16 type, const CVector &pos, const CVector &dir, float size, uint32, const RwRGBA &col, uint8 remove) { EAXJMP(0x4BC5B0); }

// Converted from static void __cdecl CParticleObject::Initialise() 0x42C760
void CParticleObject::Initialise()
{
	((void (__cdecl *)())0x4BC440)();
}

// Converted from static void __cdecl CParticleObject::UpdateAll() 0x4BCA30
void CParticleObject::UpdateAll()
{
	((void (__cdecl *)())0x4BCA30)();
}

class CParticleObject_ : public CParticleObject
{
public:
	void dtor() { CParticleObject::~CParticleObject(); }
};

STARTPATCHES
	InjectHook(0x4BC420, &CParticleObject_::dtor, PATCH_JUMP);
ENDPATCHES
