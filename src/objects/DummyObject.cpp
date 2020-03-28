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

#include <new>

class CDummyObject_ : public CDummyObject
{
public:
	void dtor(void) { CDummyObject::~CDummyObject(); }
	CDummyObject *ctor(void) { return ::new (this) CDummyObject(); }
	CDummyObject *ctor(CObject *obj) { return ::new (this) CDummyObject(obj); }
};

STARTPATCHES
	InjectHook(0x4BAAF0, (CDummyObject* (CDummyObject::*)(void)) &CDummyObject_::ctor, PATCH_JUMP);
	InjectHook(0x4BAB10, (CDummyObject* (CDummyObject::*)(CObject*)) &CDummyObject_::ctor, PATCH_JUMP);
	InjectHook(0x4BAB70, &CDummyObject_::dtor, PATCH_JUMP);
ENDPATCHES