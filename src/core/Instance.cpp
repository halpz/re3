#include "common.h"
#include "patcher.h"
#include "Instance.h"

void
CInstance::Shutdown()
{
	GetMatrix().Detach();
}

class CInstance_ : public CInstance
{
public:
	void dtor() { CInstance::~CInstance(); }
};

STARTPATCHES
	InjectHook(0x50BE90, &CInstance_::dtor, PATCH_JUMP);
	InjectHook(0x50B850, &CInstance::Shutdown, PATCH_JUMP);
ENDPATCHES
