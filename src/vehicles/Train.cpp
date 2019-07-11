#include "common.h"
#include "patcher.h"
#include "Train.h"

CTrain::CTrain(int mi, uint8 owner)
{
	ctor(mi, owner);
}

WRAPPER CTrain* CTrain::ctor(int, uint8) { EAXJMP(0x54E2A0); }

class CTrain_ : public CTrain
{
public:
	void dtor(void) { CTrain::~CTrain(); }
};

STARTPATCHES
	InjectHook(0x54E450, &CTrain_::dtor, PATCH_JUMP);
ENDPATCHES
