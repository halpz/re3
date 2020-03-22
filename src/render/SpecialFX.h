#pragma once

class CSpecialFX
{
public:
	static void Render(void);
	static void Update(void);
};

class CMotionBlurStreaks
{
public:
	static void RegisterStreak(int32 id, uint8 r, uint8 g, uint8 b, CVector p1, CVector p2);
};

struct CBulletTrace
{
	CVector m_vecCurrentPos;
	CVector m_vecTargetPos;
	bool m_bInUse;
	uint8 m_framesInUse;
	uint8 m_lifeTime;

	void Update(void);
};

class CBulletTraces
{
public:
	static CBulletTrace (&aTraces)[NUMBULLETTRACES];

	static void Init(void);
	static void AddTrace(CVector*, CVector*);
	static void Render(void);
	static void Update(void);
};

class CBrightLights
{
public:
	static void RegisterOne(CVector pos, CVector up, CVector right, CVector fwd, uint8 type, uint8 unk1 = 0, uint8 unk2 = 0, uint8 unk3 = 0);
};

enum
{
	MARKERTYPE_0 = 0,
	MARKERTYPE_ARROW,
	MARKERTYPE_2,
	MARKERTYPE_3,
	MARKERTYPE_CYLINDER,
	NUMMARKERTYPES,

	MARKERTYPE_INVALID = 0x101
};


class C3dMarker
{
public:
	CMatrix m_Matrix;
	RpAtomic *m_pAtomic;
	RpMaterial *m_pMaterial;
	uint16 m_nType;
	bool m_bIsUsed;
	uint32 m_nIdentifier;
	RwRGBA m_Color;
	uint16 m_nPulsePeriod;
	int16 m_nRotateRate;
	uint32 m_nStartTime;
	float m_fPulseFraction;
	float m_fStdSize;
	float m_fSize;
	float m_fBrightness;
	float m_fCameraRange;

	bool AddMarker(uint32 identifier, uint16 type, float fSize, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);
	void DeleteMarkerObject();
	void Render();
};

class C3dMarkers
{
public:
	static void Init();
	static void Shutdown();
	static C3dMarker *PlaceMarker(uint32 id, uint16 type, CVector &pos, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);
	static void PlaceMarkerSet(uint32 id, uint16 type, CVector &pos, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate);
	static void Render();
	static void Update();

	static C3dMarker(&m_aMarkerArray)[NUM3DMARKERS];
	static int32 &NumActiveMarkers;
	static RpClump* (&m_pRpClumpArray)[NUMMARKERTYPES];
};

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

class CSpecialParticleStuff
{
	static uint32 BoatFromStart;
public:
	static void CreateFoamAroundObject(CMatrix*, float, float, float, int32);
	static void StartBoatFoamAnimation();
	static void UpdateBoatFoamAnimation(CMatrix*);
};
