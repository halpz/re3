#pragma once

#define DEFAULT_SKIN_NAME "$$\"\""

static RpClump *gpPlayerClump;// = *(RpClump**)0x660FF8;
static float gOldFov;// = *(float*)0x660FFC;

void LoadPlayerDff(void);
void FindPlayerDff(uint32 &offset, uint32 &size);

class CPlayerSkin
{
	static int m_txdSlot;
public:
	static void Initialise();
	static void Shutdown();
	static RwTexture *GetSkinTexture(const char *texName);
	static void BeginFrontendSkinEdit();
	static void EndFrontendSkinEdit();
	static void RenderFrontendSkinEdit();
};