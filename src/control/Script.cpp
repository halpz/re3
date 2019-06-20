#include "common.h"
#include "patcher.h"

#include "Script.h"

uint8 *CTheScripts::ScriptSpace = (uint8*)0x74B248;
CTextLine* CTheScripts::IntroTextLines = (CTextLine*)0x70EA74;
CScriptRectangle* CTheScripts::IntroRectangles = (CScriptRectangle*)0x72D109;
CSprite2d* CTheScripts::ScriptSprites = (CSprite2d*)0x72B090;
bool CTheScripts::DbgFlag = *(bool*)0x95CD87;
uint32 CTheScripts::OnAMissionFlag = *(uint32*)0x8F1B64;

WRAPPER bool CTheScripts::IsPlayerOnAMission() { EAXJMP(0x439410); }
