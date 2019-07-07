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

STARTPATCHES
	InjectHook(0x4BAB70, &CDummyObject::dtor, PATCH_JUMP);
ENDPATCHES