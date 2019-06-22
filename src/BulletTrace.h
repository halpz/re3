#pragma once

#include "common.h"

struct CBulletTrace
{
	CVector m_vecInf;
	CVector m_vecSup;
	bool m_bInUse;
	uint8 m_bFramesInUse;
	uint8 m_bLifeTime;
};
