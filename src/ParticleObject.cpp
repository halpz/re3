#include "common.h"
#include "patcher.h"
#include "ParticleObject.h"

WRAPPER void CParticleObject::AddObject(uint16, const CVector &pos, bool remove) { EAXJMP(0x4BC4D0); }


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