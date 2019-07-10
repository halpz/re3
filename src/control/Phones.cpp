#include "common.h"
#include "patcher.h"
#include "Phones.h"
#include "Pools.h"

CPhoneInfo &gPhoneInfo = *(CPhoneInfo*)0x732A20;

bool &CPhoneInfo::isPhonePickedUp = *(bool*)0x6283AC;
bool &CPhoneInfo::isPhoneBeingPickedUp = *(bool*)0x6283B4;
CPhone *&CPhoneInfo::pickedUpPhone = *(CPhone**)0x6283B0;

int
CPhoneInfo::FindNearestFreePhone(CVector *pos)
{
	int nearestPhoneId = -1;
	float nearestPhoneDist = 60.0f;

	for (int phoneId = 0; phoneId < m_nMax; phoneId++) {

		if (gPhoneInfo.m_aPhones[phoneId].m_nState == PHONE_STATE_FREE) {
			float phoneDist = (m_aPhones[phoneId].m_vecPos - *pos).Magnitude2D();

			if (phoneDist < nearestPhoneDist) {
				nearestPhoneDist = phoneDist;
				nearestPhoneId = phoneId;
			}
		}
	}
	return nearestPhoneId;
}

bool
CPhoneInfo::PhoneAtThisPosition(CVector pos)
{
	for (int phoneId = 0; phoneId < m_nMax; phoneId++) {
		if (pos.x == m_aPhones[phoneId].m_vecPos.x && pos.y == m_aPhones[phoneId].m_vecPos.y)
			return true;
	}
	return false;
}

bool
CPhoneInfo::HasMessageBeenDisplayed(int phoneId)
{
	if (isPhonePickedUp)
		return false;
	
	int state = m_aPhones[phoneId].m_nState;

	return state == PHONE_STATE_REPEATED_MESSAGE_SHOWN_ONCE || 
		state == PHONE_STATE_ONETIME_MESSAGE_SHOWN ||
		state == PHONE_STATE_REPEATED_MESSAGE_SHOWN;
}

bool
CPhoneInfo::IsMessageBeingDisplayed(int phoneId)
{
	return pickedUpPhone == &m_aPhones[phoneId];
}

void
CPhoneInfo::Load(CPhoneInfo *source, uint8 buffer)
{
	// Buffer isn't used.

	m_nMax = source->m_nMax;
	m_nNum = source->m_nNum;
	for (int phoneId = 0; phoneId < 50; phoneId++) {
		CPhone *phone = &source->m_aPhones[phoneId];

		m_aPhones[phoneId].m_vecPos = phone->m_vecPos;
		memcpy(m_aPhones[phoneId].m_apMessages, phone->m_apMessages, sizeof(uint16*) * 6);
		m_aPhones[phoneId].m_pEntity = phone->m_pEntity;
		m_aPhones[phoneId].m_nState = phone->m_nState;
		m_aPhones[phoneId].field_30 = phone->field_30;

		if (phone->m_pEntity) {
			// It's saved as building pool index in save file, convert it to true entity
			CBuilding *actualEntity = CPools::GetBuildingPool()->GetSlot((int)phone->m_pEntity - 1);
			m_aPhones[phoneId].m_pEntity = actualEntity;
		}
	}
}

void
CPhoneInfo::SetPhoneMessage_JustOnce(int phoneId, uint16 *msg1, uint16 *msg2, uint16 *msg3, uint16 *msg4, uint16 *msg5, uint16 *msg6)
{
	// If there is at least one message, it should be msg1.
	if (msg1) {
		m_aPhones[phoneId].m_apMessages[0] = msg1;
		m_aPhones[phoneId].m_apMessages[1] = msg2;
		m_aPhones[phoneId].m_apMessages[2] = msg3;
		m_aPhones[phoneId].m_apMessages[3] = msg4;
		m_aPhones[phoneId].m_apMessages[4] = msg5;
		m_aPhones[phoneId].m_apMessages[5] = msg6;
		m_aPhones[phoneId].m_nState = PHONE_STATE_ONETIME_MESSAGE_SET;
	} else {
		m_aPhones[phoneId].m_nState = PHONE_STATE_MESSAGE_REMOVED;
	}
}

void
CPhoneInfo::SetPhoneMessage_Repeatedly(int phoneId, uint16 *msg1, uint16 *msg2, uint16 *msg3, uint16 *msg4, uint16 *msg5, uint16 *msg6)
{
	// If there is at least one message, it should be msg1.
	if (msg1) {
		m_aPhones[phoneId].m_apMessages[0] = msg1;
		m_aPhones[phoneId].m_apMessages[1] = msg2;
		m_aPhones[phoneId].m_apMessages[2] = msg3;
		m_aPhones[phoneId].m_apMessages[3] = msg4;
		m_aPhones[phoneId].m_apMessages[4] = msg5;
		m_aPhones[phoneId].m_apMessages[5] = msg6;
		m_aPhones[phoneId].m_nState = PHONE_STATE_REPEATED_MESSAGE_SET;
	} else {
		m_aPhones[phoneId].m_nState = PHONE_STATE_MESSAGE_REMOVED;
	}
}

STARTPATCHES
	InjectHook(0x42F720, &CPhoneInfo::FindNearestFreePhone, PATCH_JUMP);
	InjectHook(0x42FD50, &CPhoneInfo::PhoneAtThisPosition, PATCH_JUMP);
	InjectHook(0x42FFF0, &CPhoneInfo::HasMessageBeenDisplayed, PATCH_JUMP);
	InjectHook(0x430030, &CPhoneInfo::IsMessageBeingDisplayed, PATCH_JUMP);
	InjectHook(0x430120, &CPhoneInfo::Load, PATCH_JUMP);
	InjectHook(0x42FF90, &CPhoneInfo::SetPhoneMessage_JustOnce, PATCH_JUMP);
	InjectHook(0x42FF30, &CPhoneInfo::SetPhoneMessage_Repeatedly, PATCH_JUMP);
ENDPATCHES

WRAPPER void PhonePutDownCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x42F570); }
WRAPPER void PhonePickUpCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x42F470); }
