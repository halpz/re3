#pragma once

#include "Dummy.h"

class CObject;

class CDummyObject : public CDummy
{
public:
	CDummyObject(void) {}
	CDummyObject(CObject *obj);
};
static_assert(sizeof(CDummyObject) == 0x68, "CDummyObject: error");
