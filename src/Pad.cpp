#include "common.h"
#include "Pad.h"

CPad *CPad::Pads = (CPad*)0x6F0360;

uint16 *CPad::OldKeyState = (uint16*)0x6F1E70;
uint16 *CPad::NewKeyState = (uint16*)0x6E60D0;
uint16 *CPad::TempKeyState = (uint16*)0x774DE8;

CMouseControllerState &CPad::OldMouseControllerState = *(CMouseControllerState*)0x8472A0;
CMouseControllerState &CPad::NewMouseControllerState = *(CMouseControllerState*)0x8809F0;
CMouseControllerState &CPad::PCTempMouseControllerState = *(CMouseControllerState*)0x6F1E60;

void
CControllerState::Clear(void)
{
	leftX = 0;
	leftY = 0;
	rightX = 0;
	rightY = 0;
	l1 = 0;
	l2 = 0;
	r1 = 0;
	r2 = 0;
	up = 0;
	down = 0;
	left = 0;
	right = 0;
	start = 0;
	select = 0;
	square = 0;
	triangle = 0;
	cross = 0;
	circle = 0;
	leftshock = 0;
	rightshock = 0;
}
