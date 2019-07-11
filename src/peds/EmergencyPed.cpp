#include "common.h"
#include "patcher.h"
#include "EmergencyPed.h"

class CEmergencyPed_ : public CEmergencyPed
{
public:
	void dtor(void) { CEmergencyPed::~CEmergencyPed(); }
};

STARTPATCHES
	InjectHook(0x4C2EF0, &CEmergencyPed_::dtor, PATCH_JUMP);
ENDPATCHES
