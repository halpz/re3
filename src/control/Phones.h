#pragma once

#include "Physical.h"
#include "AnimBlendAssociation.h"

struct CPhone
{
	CVector m_vecPos;
	uint16 *m_apMessages[6];
	int32 field_24;
	CEntity *m_pEntity;
	int32 m_nState;
	uint8 field_30;
};

static_assert(sizeof(CPhone) == 0x34, "CPhone: error");

class CPhoneInfo {
public:
	int32 m_nMax;
	int32 m_nNum;
	CPhone m_aPhones[50];

	CPhoneInfo() { }
	~CPhoneInfo() { }

	int FindNearestFreePhone(CVector*);
	bool PhoneAtThisPosition(CVector);
};

extern CPhoneInfo &gPhoneInfo;

void PhonePutDownCB(CAnimBlendAssociation *assoc, void *arg);
void PhonePickUpCB(CAnimBlendAssociation *assoc, void *arg);