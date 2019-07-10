#include "common.h"
#include "patcher.h"
#include "Phones.h"

CPhoneInfo &gPhoneInfo = * (CPhoneInfo*) * (uintptr*)0x732A20;

int
CPhoneInfo::FindNearestFreePhone(CVector *pos)
{
	int nearestPhoneId = -1;
	float nearestPhoneDist = 60.0f;

	for (int phoneId = 0; phoneId < m_nMax; phoneId++) {

		if (gPhoneInfo.m_aPhones[phoneId].m_nState == 0) {
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

STARTPATCHES
	InjectHook(0x42F720, &CPhoneInfo::FindNearestFreePhone, PATCH_JUMP);
	InjectHook(0x42FD50, &CPhoneInfo::PhoneAtThisPosition, PATCH_JUMP);
ENDPATCHES

WRAPPER void PhonePutDownCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x42F570); }
WRAPPER void PhonePickUpCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x42F470); }
