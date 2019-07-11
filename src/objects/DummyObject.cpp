#include "common.h"
#include "patcher.h"
#include "DummyObject.h"
#include "Pools.h"

CDummyObject::CDummyObject(CObject *obj)
{
	SetModelIndexNoCreate(obj->GetModelIndex());
	if(obj->m_rwObject)
		AttachToRwObject(obj->m_rwObject);
	obj->DetachFromRwObject();
	m_level = obj->m_level;
}

class CDummyObject_ : public CDummyObject
{
public:
	void dtor(void) { CDummyObject::~CDummyObject(); }
};

STARTPATCHES
	InjectHook(0x4BAB70, &CDummyObject_::dtor, PATCH_JUMP);
ENDPATCHES
