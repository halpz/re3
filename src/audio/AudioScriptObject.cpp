#include "common.h"
#include "AudioScriptObject.h"

void PlayOneShotScriptObject(uint8 id, CVector const &pos)
{
	((void (__cdecl *)(uint8, CVector const &))0x57C5F0)(id, pos);
}