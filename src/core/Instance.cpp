#include "common.h"
#include "patcher.h"
#include "Instance.h"

class CInstance_ : public CInstance
{
public:
	void dtor() { CInstance::~CInstance(); }
};

STARTPATCHES
	InjectHook(0x50BE90, &CInstance_::dtor, PATCH_JUMP);
ENDPATCHES
