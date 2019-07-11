#pragma once

#include "Physical.h"
#include "AnimBlendAssociation.h"

enum {
	PHONE_STATE_FREE,
	PHONE_STATE_1,
	PHONE_STATE_2,
	PHONE_STATE_MESSAGE_REMOVED,
	PHONE_STATE_ONETIME_MESSAGE_SET,
	PHONE_STATE_REPEATED_MESSAGE_SET,
	PHONE_STATE_REPEATED_MESSAGE_SHOWN_ONCE,
	PHONE_STATE_ONETIME_MESSAGE_SHOWN,
	PHONE_STATE_REPEATED_MESSAGE_SHOWN,
	PHONE_STATE_9
};

struct CPhone
{
	CVector m_vecPos;
	uint16 *m_apMessages[6];
	uint32 m_lastTimeRepeatedMsgShown;
	CEntity *m_pEntity; // it's building pool index in save files
	int32 m_nState;
	uint8 field_30;
};

static_assert(sizeof(CPhone) == 0x34, "CPhone: error");

class CPhoneInfo {
	static bool &isPhonePickedUp;
	static bool &isPhoneBeingPickedUp;
	static CPhone *&pickedUpPhone;
public:
	int32 m_nMax;
	int32 m_nNum;
	CPhone m_aPhones[50];

	CPhoneInfo() { }
	~CPhoneInfo() { }

	int FindNearestFreePhone(CVector*);
	bool PhoneAtThisPosition(CVector);
	bool HasMessageBeenDisplayed(int);
	bool IsMessageBeingDisplayed(int);
	void Load(CPhoneInfo *source, uint8 buffer);
	void SetPhoneMessage_JustOnce(int phoneId, uint16 *msg1, uint16 *msg2, uint16 *msg3, uint16 *msg4, uint16 *msg5, uint16 *msg6);
	void SetPhoneMessage_Repeatedly(int phoneId, uint16 *msg1, uint16 *msg2, uint16 *msg3, uint16 *msg4, uint16 *msg5, uint16 *msg6);
};

extern CPhoneInfo &gPhoneInfo;

void PhonePutDownCB(CAnimBlendAssociation *assoc, void *arg);
void PhonePickUpCB(CAnimBlendAssociation *assoc, void *arg);