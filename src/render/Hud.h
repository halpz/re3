#pragma once

class CHud
{
public:
	static void Draw(void);
	static void DrawAfterFade(void);

	static bool &m_Wants_To_Draw_Hud;
};
