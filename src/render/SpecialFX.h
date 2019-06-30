#pragma once

class CSpecialFX
{
public:
	static void Render(void);
};

class CMotionBlurStreaks
{
public:
	static void RegisterStreak(int32 id, uint8 r, uint8 g, uint8 b, CVector p1, CVector p2);
};
