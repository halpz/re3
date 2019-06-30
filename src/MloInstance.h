#pragma once

#include "Placeable.h"

class CMloInstance : CPlaceable
{
public:
	void dtor() { this->CMloInstance::~CMloInstance(); }
};