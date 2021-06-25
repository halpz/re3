#include "common.h"
#ifndef MASTER
#include "main.h"
#include "Camera.h"
#include "Font.h"
#include "Ped.h"
#include "Sprite.h"
#include "Text.h"

static char ObjectiveText[][28] = {
	"No Obj",
	"Wait on Foot",
	"Wait on Foot for cop",
	"Flee on Foot Till Safe",
	"Guard Spot",
	"Guard Area",
	"Wait in Car",
	"Wait in Car then Getout",
	"Kill Char on Foot",
	"Kill Char Any Means",
	"Flee Char on Foot Till Safe",
	"Flee Char on Foot Always",
	"GoTo Char on Foot",
	"GoTo Char on Foot walking",
	"Hassle char",
	"Follow Char in Formation",
	"Leave Car",
	"Enter Car as Passenger",
	"Enter Car as Driver",
	"Follow Car in Car",
	"Fire at Obj from Vehicle",
	"Destroy Obj",
	"Destroy Car",
	"GoTo Area Any Means",
	"GoTo Area on Foot",
	"Run to Area",
	"GoTo Area in Car",
	"Follow Car on Foot Woffset",
	"Guard Attack",
	"Set Leader",
	"Follow Route",
	"Solicit vehicle",
	"Take Taxi",
	"Catch Train",
	"Buy IceCream",
	"Steal Any Car",
	"Steal any mission car",
	"Mug Char",
	"Lv car die",
	"Goto seat",
	"Goto atm",
	"Flee car",
	"Sunbathe",
	"Goto bus stop",
	"Goto pizza",
	"Goto shelter",
	"Aim gun at",
	"Wander",
	"Wait on foot at shltr",
	"Sprint to area",
	"Kill char on boat",
	"Solicit ped",
	"Wait at bus stop",
	"Goto ice cream van foot",
	"Wait foot icecream van"
};

static char StateText[][18] = {
	"None",
	"Idle",
	"Look Entity",
	"Look Heading",
	"Wander Range",
	"Wander Path",
	"Seek Pos",
	"Seek Entity",
	"Flee Pos",
	"Flee Entity",
	"Pursue",
	"Follow Path",
	"Sniper Mode",
	"Rocket Mode",
	"Dummy",
	"Pause",
	"Attack",
	"Fight",
	"Face Phone",
	"Make Call",
	"Chat",
	"Mug",
	"AimGun",
	"AI Control",
	"Seek Car",
	"Seek InBoat",
	"Follow Route",
	"C.P.R.",
	"Solicit",
	"Buy IceCream",
	"Investigate",
	"Step away",
	"On Fire",
	"Bathe",
	"Flash",
	"Jog",
	"Answer mobile",
	"Hang out",
	"STATES_NO_AI",
	"Abseil",
	"Sit",
	"Jump",
	"Fall",
	"GetUp",
	"Stagger",
	"Dive away",
	"STATES_NO_ST",
	"Enter Train",
	"Exit Train",
	"Arrest Plyr",
	"Driving",
	"Passenger",
	"Taxi Passngr",
	"Open Door",
	"Die",
	"Dead",
	"CarJack",
	"Drag fm Car",
	"Enter Car",
	"Steal Car",
	"Exit Car",
	"Hands Up",
	"Arrested",
	"Deply stgr"
};

static char PersonalityTypeText[][18] = {
	"Player",
	"Cop",
	"Medic",
	"Fireman",
	"Gang 1",
	"Gang 2",
	"Gang 3",
	"Gang 4",
	"Gang 5",
	"Gang 6",
	"Gang 7",
	"Street Guy",
	"Suit Guy",
	"Sensible Guy",
	"Geek Guy",
	"Old Guy",
	"Tough Guy",
	"Street Girl",
	"Suit Girl",
	"Sensible Girl",
	"Geek Girl",
	"Old Girl",
	"Tough Girl",
	"Tramp",
#ifdef FIX_BUGS // there's male and female ones
	"Tramp",
#endif
	"Tourist",
	"Prostitute",
	"Criminal",
	"Busker",
	"Taxi Driver",
	"Psycho",
	"Steward",
	"Sports Fan",
};

static char WaitStateText[][16] = {
	"No Wait",
	"Traffic Lights",
	"Pause CrossRoad",
	"Look CrossRoad",
	"Look Ped",
	"Look Shop",
	"Look Accident",
	"FaceOff Gang",
	"Double Back",
	"Hit Wall",
	"Turn 180deg",
	"Surprised",
	"Ped Stuck",
	"Look About",
	"Play Duck",
	"Play Cower",
	"Play Taxi",
	"Play HandsUp",
	"Play HandsCower",
	"Play Chat",
	"Finish Flee",
	"Sit down",
	"Sit down rvrs",
	"Sit up",
	"Sit idle",
	"Use atm",
	"Sunbth pre",
	"Sunbth down",
	"Sunbth idle",
	"Riot",
	"Fast fall",
	"Bomber",
	"Stripper",
	"Ground attack",
	"Lance sitting",
	"Handsup simple"
};

void
CPed::DebugDrawPedDestination(CPed *, int, int)
{
#ifndef FINAL
	// TODO: something was here
#endif // !FINAL
}

void
CPed::DebugDrawPedDesiredHeading(CPed *, int, int)
{
#ifndef FINAL
	// TODO: something was here
#endif // !FINAL
}

void
CPed::DebugDrawCollisionRadius(float, float, float, float, int)
{
#ifndef FINAL
	// TODO: something was here
#endif // !FINAL
}

void
CPed::DebugDrawVisionRange(CVector a1, float)
{
	for (int i = a1.x - 90; i < a1.x + 89; i += 30) {
#ifndef FINAL
		// TODO: something was here
#endif // !FINAL
	}
}

void
CPed::DebugDrawVisionSimple(CVector, float)
{
#ifndef FINAL
	// TODO: something was here
#endif // !FINAL
}

void
CPed::DebugDrawLook()
{
#ifndef FINAL
	// TODO: something was here
#endif // !FINAL
}

void
CPed::DebugDrawPedPsyche()
{
#ifndef FINAL
	// TODO: something was here
#endif // !FINAL
}

void
CPed::DebugDrawDebugLines()
{
#ifndef FINAL
	// TODO: something was here
#endif // !FINAL
}

int nDisplayDebugInfo = 0;

void
CPed::SwitchDebugDisplay(void)
{
	if (++nDisplayDebugInfo > 2)
		nDisplayDebugInfo = 0;
}

int
CPed::GetDebugDisplay(void)
{
	return nDisplayDebugInfo;
}

void
CPed::DebugDrawLookAtPoints()
{
	// TODO: mobile code
}

void
CPed::DebugRenderOnePedText(void)
{
	if ((GetPosition() - TheCamera.GetPosition()).MagnitudeSqr() < sq(30.0f)) {
		float width, height;
		RwV3d screenCoords;
		CVector bitAbove = GetPosition();
		bitAbove.z += 2.0f;
		if (CSprite::CalcScreenCoors(bitAbove, &screenCoords, &width, &height, true)) {

			float lineHeight = SCREEN_SCALE_Y(Min(height / 100.0f, 0.7f) * 22.0f);

			DefinedState();
			CFont::SetPropOn();
			CFont::SetBackgroundOn();

			// Originally both of them were being divided by 60.0f.
			float xScale = Min(width / 240.0f, 0.7f);
			float yScale = Min(height / 80.0f, 0.7f);

			CFont::SetScale(SCREEN_SCALE_X(xScale), SCREEN_SCALE_Y(yScale));
			CFont::SetCentreOn();
			CFont::SetCentreSize(SCREEN_WIDTH);
			CFont::SetJustifyOff();
			CFont::SetColor(CRGBA(255, 255, 0, 255));
			CFont::SetBackGroundOnlyTextOn();
			CFont::SetFontStyle(1);
			AsciiToUnicode(StateText[m_nPedState], gUString);
			CFont::PrintString(screenCoords.x, screenCoords.y, gUString);
			AsciiToUnicode(ObjectiveText[m_objective], gUString);
			CFont::PrintString(screenCoords.x, screenCoords.y + lineHeight, gUString);
			AsciiToUnicode(PersonalityTypeText[m_pedStats->m_type], gUString);
			CFont::PrintString(screenCoords.x, screenCoords.y + 2 * lineHeight, gUString);
			AsciiToUnicode(WaitStateText[m_nWaitState], gUString);
			CFont::PrintString(screenCoords.x, screenCoords.y + 3 * lineHeight, gUString);
			if (m_nPedState == PED_SEEK_POS || m_nPedState == PED_SEEK_ENTITY) {
				sprintf(gString, "Safe distance to target: %.2f", m_distanceToCountSeekDone);
				AsciiToUnicode(gString, gUString);
				CFont::PrintString(screenCoords.x, screenCoords.y + 4 * lineHeight, gUString);
			}
			DefinedState();
		}
	}
}

void
CPed::DebugRenderClosePedText()
{
	// TODO: mobile code
}
#endif