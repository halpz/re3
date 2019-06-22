#pragma once

#include "common.h"

struct CBulletTrace
{
    CVector m_vecInf;
    CVector m_vecSup;
    char m_bInUse;
    char m_bFramesInUse;
    char m_bLifeTime;
};