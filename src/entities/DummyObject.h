#pragma once

#include "Dummy.h"

class CDummyObject : CDummy
{
};
static_assert(sizeof(CDummyObject) == 0x68, "CDummyObject: error");
