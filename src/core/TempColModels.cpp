#include "common.h"
#include "patcher.h"
#include "TempColModels.h"

CColModel &CTempColModels::ms_colModelPed1 = *(CColModel*)0x726CB0;
CColModel &CTempColModels::ms_colModelPed2 = *(CColModel*)0x726D08;
CColModel &CTempColModels::ms_colModelBBox = *(CColModel*)0x727FE0;
CColModel &CTempColModels::ms_colModelBumper1 = *(CColModel*)0x86BE88;
CColModel &CTempColModels::ms_colModelWheel1 = *(CColModel*)0x878C40;
CColModel &CTempColModels::ms_colModelPanel1 = *(CColModel*)0x87BDD8;
CColModel &CTempColModels::ms_colModelBodyPart2 = *(CColModel*)0x87BE30;
CColModel &CTempColModels::ms_colModelBodyPart1 = *(CColModel*)0x87BE88;
CColModel (&CTempColModels::ms_colModelCutObj)[5] = *(CColModel(*)[5]) *(uintptr*)0x87C960;
CColModel &CTempColModels::ms_colModelPedGroundHit = *(CColModel*)0x880480;
CColModel &CTempColModels::ms_colModelBoot1 = *(CColModel*)0x880670;
CColModel &CTempColModels::ms_colModelDoor1 = *(CColModel*)0x880850;
CColModel &CTempColModels::ms_colModelBonnet1 = *(CColModel*)0x8808A8;

WRAPPER void CTempColModels::Initialise(void) { EAXJMP(0x412160); }
