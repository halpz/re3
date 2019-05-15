#include "common.h"
#include "patcher.h"
#include "Entity.h"
#include "World.h"

CPtrList *CWorld::ms_bigBuildingsList = (CPtrList*)0x6FAB60;
CPtrList &CWorld::ms_listMovingEntityPtrs = *(CPtrList*)0x8F433C;
CSector (*CWorld::ms_aSectors)[NUMSECTORS_X] = (CSector (*)[NUMSECTORS_Y])0x665608;
uint16 &CWorld::ms_nCurrentScanCode = *(uint16*)0x95CC64;

bool &CWorld::bNoMoreCollisionTorque = *(bool*)0x95CDCC;

void
CWorld::ClearScanCodes(void)
{
	CPtrNode *node;
	for(int i = 0; i < NUMSECTORS_Y; i++)
	for(int j = 0; j < NUMSECTORS_X; j++){
		CSector *s = &ms_aSectors[i][j];
		for(node = s->m_lists[ENTITYLIST_BUILDINGS].first; node; node = node->next)
			((CEntity*)node->item)->m_scanCode = 0;
		for(node = s->m_lists[ENTITYLIST_VEHICLES].first; node; node = node->next)
			((CEntity*)node->item)->m_scanCode = 0;
		for(node = s->m_lists[ENTITYLIST_PEDS].first; node; node = node->next)
			((CEntity*)node->item)->m_scanCode = 0;
		for(node = s->m_lists[ENTITYLIST_OBJECTS].first; node; node = node->next)
			((CEntity*)node->item)->m_scanCode = 0;
		for(node = s->m_lists[ENTITYLIST_DUMMIES].first; node; node = node->next)
			((CEntity*)node->item)->m_scanCode = 0;
	}
}

STARTPATCHES
	InjectHook(0x4B1F60, CWorld::ClearScanCodes, PATCH_JUMP);
ENDPATCHES

WRAPPER CVector &FindPlayerCoors(CVector &v) { EAXJMP(0x4A1030); }
WRAPPER CVehicle *FindPlayerVehicle(void) { EAXJMP(0x4A10C0); }
WRAPPER CVehicle *FindPlayerTrain(void) { EAXJMP(0x4A1120); }
