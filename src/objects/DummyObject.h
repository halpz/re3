#pragma once

#include "Dummy.h"

class CObject;

class CDummyObject : public CDummy
{
public:
	CDummyObject(void) {}
	CDummyObject(CObject *obj);
	void dtor(void) { this->CDummyObject::~CDummyObject(); }
};
static_assert(sizeof(CDummyObject) == 0x68, "CDummyObject: error");
