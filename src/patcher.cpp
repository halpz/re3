#include "common.h"
#include "patcher.h"

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
