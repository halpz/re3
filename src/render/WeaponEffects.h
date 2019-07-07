#pragma once

class CWeaponEffects
{
public:
	bool m_bCrosshair;
	int8 gap_1[3];
	CVector m_vecPos;
	int8 field_16;
	int8 field_17;
	int8 field_18;
	int8 field_19;
	float field_20;
	int32 field_24;
	RwTexture *m_pTexture;
	RwRaster *m_pRaster;

public:
	static void Render(void);
	static void ClearCrosshair();
};
