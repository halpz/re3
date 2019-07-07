#pragma once

#pragma once

#include "Object.h"

class CProjectile : public CObject
{
public:
	void dtor(void) { this->CProjectile::~CProjectile(); }
};
