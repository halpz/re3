#pragma once

#include "Ped.h"

class CCivilianPed : public CPed
{
	bool m_bLookForVacantCars;
	uint32 m_nLookForVacantCarsCounter;
	bool m_bStealCarEvenIfThereIsSomeoneInIt; // unused
	bool m_bJustStoleACar;
	uint32 m_nStealWishList[16];
	bool m_bAttractorUnk;
	int32 m_nAttractorCycleState;
public:
	CCivilianPed(ePedType, uint32);
	~CCivilianPed(void) { }

	void CivilianAI(void);
	void ProcessControl(void);
	void UseNearbyAttractors(void);
	void FindNearbyAttractorsSectorList(CPtrList&, float&, C2dEffect*&, CEntity*&);
	bool IsAttractedTo(int8);
	void EnterVacantNearbyCars(void);
	bool IsOnStealWishList(int32);
};
#ifndef PED_SKIN
VALIDATE_SIZE(CCivilianPed, 0x53C);
#endif
