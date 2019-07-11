#include "common.h"
#include "patcher.h"
#include "Plane.h"

CPlane::CPlane(int mi, uint8 owner)
{
	ctor(mi, owner);
}

WRAPPER CPlane* CPlane::ctor(int, uint8) { EAXJMP(0x54B170); }

CPlane::~CPlane()
{
	DeleteRwObject();
}

class CPlane_ : public CPlane
{
public:
	void dtor(void) { CPlane::~CPlane(); }
};

STARTPATCHES
	InjectHook(0x54B270, &CPlane_::dtor, PATCH_JUMP);
ENDPATCHES
