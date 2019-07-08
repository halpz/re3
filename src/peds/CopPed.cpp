#include "common.h"
#include "patcher.h"
#include "CopPed.h"

CCopPed::~CCopPed()
{
	ClearPursuit();
}

WRAPPER void CCopPed::ClearPursuit(void) { EAXJMP(0x4C28C0); }

class CCopPed_ : public CCopPed
{
public:
	void dtor(void) { CCopPed::~CCopPed(); }
};

STARTPATCHES
	InjectHook(0x4C13E0, &CCopPed_::dtor, PATCH_JUMP);
ENDPATCHES
