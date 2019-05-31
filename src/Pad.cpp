#include "common.h"
#include "patcher.h"
#include "Pad.h"

CPad *CPad::Pads = (CPad*)0x6F0360;

uint16 *CPad::OldKeyState = (uint16*)0x6F1E70;
uint16 *CPad::NewKeyState = (uint16*)0x6E60D0;
uint16 *CPad::TempKeyState = (uint16*)0x774DE8;

CMouseControllerState &CPad::OldMouseControllerState = *(CMouseControllerState*)0x8472A0;
CMouseControllerState &CPad::NewMouseControllerState = *(CMouseControllerState*)0x8809F0;
CMouseControllerState &CPad::PCTempMouseControllerState = *(CMouseControllerState*)0x6F1E60;

WRAPPER void CPad::UpdatePads(void) { EAXJMP(0x492720); }
WRAPPER void CPad::PrintErrorMessage(void) { EAXJMP(0x4942B0); }

void
CControllerState::Clear(void)
{
	LeftStickX = 0;
	LeftStickY = 0;
	RightStickX = 0;
	RightStickY = 0;
	LeftShoulder1 = 0;
	LeftShoulder2 = 0;
	RightShoulder1 = 0;
	RightShoulder2 = 0;
	DPadUp = 0;
	DPadDown = 0;
	DPadLeft = 0;
	DPadRight = 0;
	Start = 0;
	Select = 0;
	Square = 0;
	Triangle = 0;
	Cross = 0;
	Circle = 0;
	LeftShock = 0;
	RightShock = 0;
	NetworkTalk = 0;
}

bool
CPad::ForceCameraBehindPlayer(void)
{
	if(DisablePlayerControls)
		return false;
	switch(Mode){
	case 0:
	case 1:
		return !!NewState.LeftShoulder1;
	case 2:
		return !!NewState.Triangle;
	case 3:
		return !!NewState.Circle;
	}
	return false;
}

bool
CPad::GetWeapon(void)
{
	if(DisablePlayerControls)
		return false;
	switch(Mode){
	case 0:
	case 1:
		return !!NewState.Circle;
	case 2:
		return !!NewState.Cross;
	case 3:
		return !!NewState.RightShoulder1;
	}
	return false;
}

bool
CPad::GetLookBehindForCar(void)
{
	if(DisablePlayerControls)
		return false;
	return NewState.LeftShoulder2 && NewState.RightShoulder2;
}

bool
CPad::GetLookBehindForPed(void)
{
	if(DisablePlayerControls)
		return false;
	return !!NewState.RightShock;
}

bool
CPad::GetLookLeft(void)
{
	if(DisablePlayerControls)
		return false;
	return !!NewState.LeftShoulder2;
}

bool
CPad::GetLookRight(void)
{
	if(DisablePlayerControls)
		return false;
	return !!NewState.RightShoulder2;
}
