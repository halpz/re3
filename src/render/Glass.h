#pragma once

class CEntity;

class CGlass
{
public:
	static void WindowRespondsToCollision(CEntity *ent, float amount, CVector speed, CVector point, bool foo);
	static void WindowRespondsToSoftCollision(CEntity *ent, float amount);
	static void Render(void);
};
