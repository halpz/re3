#include "common.h"
#include "patcher.h"
#include "NodeName.h"

int &gPluginOffset = *(int*)0x64C610;

#define NODENAMEEXT(o) (RWPLUGINOFFSET(char, o, gPluginOffset))

char*
GetFrameNodeName(RwFrame *frame)
{
	if(gPluginOffset < 0)
		return nil;
	return NODENAMEEXT(frame);
}
