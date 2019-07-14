#include "common.h"
#include "patcher.h"
#include "EmergencyPed.h"
#include "ModelIndices.h"

class CEmergencyPed_ : public CEmergencyPed
{
public:
	CEmergencyPed *ctor(int pedtype) { return ::new (this) CEmergencyPed(pedtype); };
	void dtor(void) { CEmergencyPed::~CEmergencyPed(); }
};

WRAPPER void CEmergencyPed::ProcessControl(void) { EAXJMP(0x4C2F10); }

CEmergencyPed::CEmergencyPed(uint32 type) : CPed(type)
{
	switch (type){
	case PEDTYPE_EMERGENCY:
		SetModelIndex(MI_MEDIC);
		m_pRevivedPed = nil;
		field_1360 = 0;
		break;
	case PEDTYPE_FIREMAN:
		SetModelIndex(MI_FIREMAN);
		m_pRevivedPed = nil;
		break;
	default:
		break;
	}
	m_nEmergencyPedState = 0;
	m_pAttendedAccident = nil;
	field_1356 = 0;
}

STARTPATCHES
	InjectHook(0x4C2E40, &CEmergencyPed_::ctor, PATCH_JUMP);
	InjectHook(0x4C2EF0, &CEmergencyPed_::dtor, PATCH_JUMP);
ENDPATCHES
