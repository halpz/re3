#pragma once

//done
class CSpecialFX
{
public:
	static bool bVideoCam;
	static bool bLiftCam;
	static bool bSnapShotActive;
	static int32 SnapShotFrames;

	static void Render(void); //done
	static void Update(void); //done
	static void Init(void); //done
	static void Shutdown(void); //done
	static void AddWeaponStreak(int type); //done
	static void Render2DFXs(); //done
};

//done
class CRegisteredMotionBlurStreak
{
public:
	uintptr m_id;
	uint8 m_red;
	uint8 m_green;
	uint8 m_blue;
	CVector m_pos1[3];
	CVector m_pos2[3];
	bool m_isValid[3];

	void Update(void); //done
	void Render(void); //done
};

//done
class CMotionBlurStreaks
{
	static CRegisteredMotionBlurStreak aStreaks[NUMMBLURSTREAKS];
public:
	static void Init(void); //done
	static void Update(void); //done
	static void RegisterStreak(uintptr id, uint8 r, uint8 g, uint8 b, CVector p1, CVector p2); //done
	static void Render(void); //done
};

//done
struct CBulletTrace
{
	CVector m_vecCurrentPos;
	CVector m_vecTargetPos;
	bool m_bInUse;
	uint32 m_nCreationTime;
	uint32 m_nLifeTime;
	float m_fThicknes;
	uint8 m_fVisibility;

	void Update(void); //done
};

//done
class CBulletTraces
{
public:
	static CBulletTrace aTraces[NUMBULLETTRACES];

	static void Init(void); //done
	static void Render(void); //done
	static void Update(void); //done
	static void AddTrace(CVector* start, CVector* end, float thickness, uint32 lifeTime, uint8 visibility); //done
	static void AddTrace(CVector* start, CVector* end, int32 weaponType, class CEntity* shooter); //done
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

//done
class C3dMarker
{
public:
	CMatrix m_Matrix;
	RpAtomic *m_pAtomic;
	RpMaterial *m_pMaterial;
	uint16 m_nType;
	bool m_bIsUsed;
	bool m_bFindZOnNextPlacement;
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

	bool AddMarker(uint32 identifier, uint16 type, float fSize, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate); //done
	void DeleteMarkerObject(); //done
	void Render(); //done
};

//done
class C3dMarkers
{
public:
	static void Init(); //done
	static void Shutdown(); //done
	static C3dMarker *PlaceMarker(uint32 id, uint16 type, CVector &pos, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate); //done
	static void PlaceMarkerSet(uint32 id, uint16 type, CVector &pos, float size, uint8 r, uint8 g, uint8 b, uint8 a, uint16 pulsePeriod, float pulseFraction, int16 rotateRate); //done
	static void Render(); //done
	static void Update(); //done

	static C3dMarker m_aMarkerArray[NUM3DMARKERS];
	static int32 NumActiveMarkers;
	static RpClump* m_pRpClumpArray[NUMMARKERTYPES];
};

enum
{
	BRIGHTLIGHT_INVALID,
	BRIGHTLIGHT_TRAFFIC_GREEN,
	BRIGHTLIGHT_TRAFFIC_YELLOW,
	BRIGHTLIGHT_TRAFFIC_RED,

	// white
	BRIGHTLIGHT_FRONT_LONG,
	BRIGHTLIGHT_FRONT_SMALL,
	BRIGHTLIGHT_FRONT_BIG,
	BRIGHTLIGHT_FRONT_TALL,

	// red
	BRIGHTLIGHT_REAR_LONG,
	BRIGHTLIGHT_REAR_SMALL,
	BRIGHTLIGHT_REAR_BIG,
	BRIGHTLIGHT_REAR_TALL,

	BRIGHTLIGHT_SIREN,	// unused

	BRIGHTLIGHT_FRONT = BRIGHTLIGHT_FRONT_LONG,
	BRIGHTLIGHT_REAR = BRIGHTLIGHT_REAR_LONG,
};

//done
class CBrightLight
{
public:
	CVector m_pos;
	CVector m_up;
	CVector m_side;
	CVector m_front;
	float m_camDist;
	uint8 m_type;
	uint8 m_red;
	uint8 m_green;
	uint8 m_blue;
};

//done
class CBrightLights
{
	static int NumBrightLights;
	static CBrightLight aBrightLights[NUMBRIGHTLIGHTS];
public:
	static void Init(void); //done
	static void RegisterOne(CVector pos, CVector up, CVector side, CVector front,
		uint8 type, uint8 red = 0, uint8 green = 0, uint8 blue = 0); //done
	static void Render(void); //done
	static void RenderOutGeometryBuffer(void); //done
};


enum
{
	SHINYTEXT_WALK = 1,
	SHINYTEXT_FLAT
};

//done
class CShinyText
{
public:
	CVector m_verts[4];
	CVector2D m_texCoords[4];
	float m_camDist;
	uint8 m_type;
	uint8 m_red;
	uint8 m_green;
	uint8 m_blue;
};

//done
class CShinyTexts 
{
	static int NumShinyTexts;
	static CShinyText aShinyTexts[NUMSHINYTEXTS];
public:
	static void Init(void); //done
	static void RegisterOne(CVector p0, CVector p1, CVector p2, CVector p3,
		float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3,
		uint8 type, uint8 red, uint8 green, uint8 blue, float maxDist); //done, not used
	static void Render(void); //done
	static void RenderOutGeometryBuffer(void); //done
};

//done
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
	void Render(); //done
};

//done
class CMoneyMessages
{
	static CMoneyMessage aMoneyMessages[NUMMONEYMESSAGES];
public:
	static void Init(); //done
	static void Render(); //done
	static void	RegisterOne(CVector vecPos, const char *pText, uint8 bRed, uint8 bGreen, uint8 bBlue, float fSize, float fOpacity); //done
};

//done
class CSpecialParticleStuff
{
	static uint32 BoatFromStart;
public:
	static void CreateFoamAroundObject(CMatrix*, float, float, float, int32); //done, not used
	static void StartBoatFoamAnimation(); //done, not used
	static void UpdateBoatFoamAnimation(CMatrix*); //done, not used
};
