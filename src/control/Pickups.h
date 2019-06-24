#pragma once

#include "config.h"
#include "Pickup.h"

class CPickups
{
public:
	static void RenderPickUpText(void);

	static CPickup(&aPickUps)[NUMPICKUPS];
};

class CPacManPickups
{
public:
	static void Render(void);
};
