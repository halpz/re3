#pragma once

#include "ColModel.h"

class CTempColModels
{
public:
	CColModel ms_colModelPed1;
	CColModel ms_colModelBBox;
	CColModel ms_colModelWeapon;

	static CColModel ms_colModelPed2;
	static CColModel ms_colModelBumper1;
	static CColModel ms_colModelWheel1;	
	static CColModel ms_colModelPanel1;
	static CColModel ms_colModelBodyPart2;
	static CColModel ms_colModelBodyPart1;
	static CColModel ms_colModelCutObj[10];
	static CColModel ms_colModelPedGroundHit;
	static CColModel ms_colModelBoot1;
	static CColModel ms_colModelDoor1;
	static CColModel ms_colModelBonnet1;
	static CColModel ms_colModelFerryDocked;

	void Initialise(void);
	void Write(base::cRelocatableChunkWriter &writer);
};

extern CTempColModels *gpTempColModels;
