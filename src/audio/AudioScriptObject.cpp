#include "common.h"
#include "AudioScriptObject.h"

void PlayOneShotScriptObject(UInt8 id, CVector const &pos)
{
	((void (__cdecl *)(UInt8, CVector const &))0x57C5F0)(id, pos);
}