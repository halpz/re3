#include "common.h"

#include "World.h"
#include "Vehicle.h"
#include "PlayerPed.h"
#include "Pools.h"
#include "References.h"

CReference CReferences::aRefs[NUMREFERENCES];
CReference *CReferences::pEmptyList;

void
CReferences::Init(void)
{
	int i;
	pEmptyList = &aRefs[0];
	for(i = 0; i < NUMREFERENCES; i++){
		aRefs[i].pentity = nil;
		aRefs[i].next = &aRefs[i+1];
	}
	aRefs[NUMREFERENCES-1].next = nil;
}

void
CReferences::RemoveReferencesToPlayer(void)
{
	if(FindPlayerVehicle())
		FindPlayerVehicle()->ResolveReferences();
	if(FindPlayerPed())
		FindPlayerPed()->ResolveReferences();
}

void
CReferences::PruneAllReferencesInWorld(void)
{
	int i;
	CEntity *e;

	i = CPools::GetPedPool()->GetSize();
	while(--i >= 0){
		e = CPools::GetPedPool()->GetSlot(i);
		if(e)
			e->PruneReferences();
	}

	i = CPools::GetVehiclePool()->GetSize();
	while(--i >= 0){
		e = CPools::GetVehiclePool()->GetSlot(i);
		if(e)
			e->PruneReferences();
	}

	i = CPools::GetObjectPool()->GetSize();
	while(--i >= 0){
		e = CPools::GetObjectPool()->GetSlot(i);
		if(e)
			e->PruneReferences();
	}
}
