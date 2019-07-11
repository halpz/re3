#include "common.h"
#include "patcher.h"
#include "Heli.h"

CHeli::CHeli(int mi, uint8 owner)
{
	ctor(mi, owner);
}

WRAPPER CHeli* CHeli::ctor(int, uint8) { EAXJMP(0x547220); }
WRAPPER void CHeli::SpecialHeliPreRender(void) { EAXJMP(0x54AE10); }

class CHeli_ : public CHeli
{
public:
	void dtor(void) { CHeli::~CHeli(); }
};

STARTPATCHES
	InjectHook(0x5474A0, &CHeli_::dtor, PATCH_JUMP);
ENDPATCHES
