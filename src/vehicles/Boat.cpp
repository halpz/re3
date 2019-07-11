#include "common.h"
#include "patcher.h"
#include "Boat.h"

float &fShapeLength = *(float*)0x600E78;
float &fShapeTime   = *(float*)0x600E7C;
float &fRangeMult   = *(float*)0x600E80; //0.6f; // 0.75f gta 3
float &fTimeMult = *(float*)0xA0FCF4;

float MAX_WAKE_LENGTH = 50.0f;
float MIN_WAKE_INTERVAL = 1.0f;
float WAKE_LIFETIME = 400.0f;

CBoat * (&CBoat::apFrameWakeGeneratingBoats)[4] = *(CBoat * (*)[4])*(uintptr*)0x8620E0;

CBoat::CBoat(int mi, uint8 owner)
{
	ctor(mi, owner);
}

WRAPPER CBoat* CBoat::ctor(int, uint8) { EAXJMP(0x53E3E0); }

bool CBoat::IsSectorAffectedByWake(CVector2D sector, float fSize, CBoat **apBoats)
{
	uint8 numVerts = 0;
	
	if ( apFrameWakeGeneratingBoats[0] == NULL )
		return false;
	
	for ( int32 i = 0; i < 4; i++ )
	{
		CBoat *pBoat = apFrameWakeGeneratingBoats[i];
		if ( !pBoat )
			break;
		
		for ( int j = 0; j < pBoat->m_nNumWakePoints; j++ )
		{
			 float fDist = (WAKE_LIFETIME - pBoat->m_afWakePointLifeTime[j]) * fShapeTime + float(j) * fShapeLength + fSize;
			 
			 if ( fabs(pBoat->m_avec2dWakePoints[j].x - sector.x) < fDist
				&& fabs(pBoat->m_avec2dWakePoints[i].y - sector.y) < fDist )
			 {
				 apBoats[numVerts] = pBoat;
				 numVerts = 1; // += ?
				 break;
			 }
		}
	}
	
	return numVerts != 0;
}

float CBoat::IsVertexAffectedByWake(CVector vecVertex, CBoat *pBoat)
{
	for ( int i = 0; i < pBoat->m_nNumWakePoints; i++ )
	{
		float fMaxDist = (WAKE_LIFETIME - pBoat->m_afWakePointLifeTime[i]) * fShapeTime + float(i) * fShapeLength;
		
		float fX = pBoat->m_avec2dWakePoints[i].x - vecVertex.x;
		float fY = pBoat->m_avec2dWakePoints[i].y - vecVertex.y;
		
		float fDist = fY * fY + fX * fX;
		
		if ( fDist < SQR(fMaxDist) )
			return 1.0f - min(fRangeMult * sqrt(fDist / SQR(fMaxDist)) + (WAKE_LIFETIME - pBoat->m_afWakePointLifeTime[i]) * fTimeMult, 1.0f);
	}

	return 0.0f;
}

WRAPPER void CBoat::FillBoatList(void) { EAXJMP(0x542250); }

class CBoat_ : public CBoat
{
public:
	void dtor() { CBoat::~CBoat(); };
};

STARTPATCHES
	InjectHook(0x53E790, &CBoat_::dtor, PATCH_JUMP);
ENDPATCHES
