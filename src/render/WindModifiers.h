#pragma once

class CWindModifiers
{
	CVector m_pos;
	int32 m_type;
public:
	static int32 Number;
	static void RegisterOne(CVector pos, int32 windSourceType);
	static bool FindWindModifier(CVector pos, float *x, float *y);
};
