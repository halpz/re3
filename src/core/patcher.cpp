#define WITHWINDOWS
#include "common.h"
#include "patcher.h"

#include <algorithm>
#include <vector>

StaticPatcher *StaticPatcher::ms_head;

StaticPatcher::StaticPatcher(Patcher func)
 : m_func(func)
{
	m_next = ms_head;
	ms_head = this;
}

void
StaticPatcher::Apply()
{
	StaticPatcher *current = ms_head;
	while(current){
		current->Run();
		current = current->m_next;
	}
	ms_head = nil;
}
#ifdef _WIN32
std::vector<uint32> usedAddresses;

static DWORD protect[2];
static uint32 protect_address;
static uint32 protect_size;

void
Protect_internal(uint32 address, uint32 size)
{
	protect_address = address;
	protect_size = size;
	VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &protect[0]);
}

void
Unprotect_internal(void)
{
	VirtualProtect((void*)protect_address, protect_size, protect[0], &protect[1]);
}

void
InjectHook_internal(uint32 address, uint32 hook, int type)
{
	if(std::any_of(usedAddresses.begin(), usedAddresses.end(),
	               [address](uint32 value) { return value == address; })) {
		debug("Used address %#06x twice when injecting hook\n", address);
	}

	usedAddresses.push_back(address);


	switch(type){
	case PATCH_JUMP:
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &protect[0]);
		*(uint8*)address = 0xE9;
		break;
	case PATCH_CALL:
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &protect[0]);
		*(uint8*)address = 0xE8;
		break;
	default:
		VirtualProtect((void*)(address + 1), 4, PAGE_EXECUTE_READWRITE, &protect[0]);
		break;
	}

	*(ptrdiff_t*)(address + 1) = hook - address - 5;
	if(type == PATCH_NOTHING)
		VirtualProtect((void*)(address + 1), 4, protect[0], &protect[1]);
	else
		VirtualProtect((void*)address, 5, protect[0], &protect[1]);
}
#else
void
Protect_internal(uint32 address, uint32 size)
{
}

void
Unprotect_internal(void)
{
}

void
InjectHook_internal(uint32 address, uint32 hook, int type)
{
}
#endif
