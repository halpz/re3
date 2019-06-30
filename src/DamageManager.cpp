#include "common.h"
#include "patcher.h"
#include "DamageManager.h"

#if 0
WRAPPER void CDamageManager::SetDoorStatus(int door, unsigned int status) { EAXJMP(0x545920); }
#else
void CDamageManager::SetDoorStatus(int door, unsigned int status)
{
	m_bDoorStatus[door] = status;
}
#endif

#if 0
WRAPPER unsigned int CDamageManager::GetDoorStatus(int door) { EAXJMP(0x545930); }
#else
unsigned int CDamageManager::GetDoorStatus(int door)
{
	return m_bDoorStatus[door];
}
#endif