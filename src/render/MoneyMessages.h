#pragma once

class CMoneyMessage
{
	friend class CMoneyMessages;

	uint32	m_nTimeRegistered;
	CVector	m_vecPosition;
	wchar	m_aText[16];
	CRGBA	m_Colour;
	float	m_fSize;
	float	m_fOpacity;
public:
	void Render();
};

class CMoneyMessages
{
	static CMoneyMessage aMoneyMessages[NUMMONEYMESSAGES];
public:
	static void Init();
	static void Render();
	static void	RegisterOne(CVector vecPos, const char *pText, uint8 bRed, uint8 bGreen, uint8 bBlue, float fSize, float fOpacity);
};