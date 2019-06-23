#include "common.h"
#include "patcher.h"
#include "Radar.h"
#include "Camera.h"
#include "Hud.h"
#include "World.h"
#include "Frontend.h"
#include "General.h"
#include "Vehicle.h"
#include "Pools.h"
#include "Script.h"
#include "TxdStore.h"
#include "World.h"
#include "Streaming.h"

WRAPPER void CRadar::Draw3dMarkers() { EAXJMP(0x4A4C70); }
WRAPPER int CRadar::ClipRadarPoly(CVector2D *out, CVector2D *in) { EAXJMP(0x4A64A0); }
WRAPPER void CRadar::TransformRadarPointToRealWorldSpace(CVector2D &out, const CVector2D &in) { EAXJMP(0x4A5300); }

float &CRadar::m_RadarRange = *(float*)0x8E281C;
CBlip *CRadar::ms_RadarTrace = (CBlip*)0x6ED5E0;

CVector2D &vec2DRadarOrigin = *(CVector2D*)0x6299B8;
int *gRadarTxdIds = (int*)0x6299C0;

CSprite2d *CRadar::AsukaSprite = (CSprite2d*)0x8F1A40;
CSprite2d *CRadar::BombSprite = (CSprite2d*)0x8F5FB4;
CSprite2d *CRadar::CatSprite = (CSprite2d*)0x885B24;
CSprite2d *CRadar::CentreSprite = (CSprite2d*)0x8F6268;
CSprite2d *CRadar::CopcarSprite = (CSprite2d*)0x8F1A2C;
CSprite2d *CRadar::DonSprite = (CSprite2d*)0x8F2BE0;
CSprite2d *CRadar::EightSprite = (CSprite2d*)0x8F2BCC;
CSprite2d *CRadar::ElSprite = (CSprite2d*)0x8F1B80;
CSprite2d *CRadar::IceSprite = (CSprite2d*)0x9415FC;
CSprite2d *CRadar::JoeySprite = (CSprite2d*)0x8F2C00;
CSprite2d *CRadar::KenjiSprite = (CSprite2d*)0x8F2C68;
CSprite2d *CRadar::LizSprite = (CSprite2d*)0x8F5830;
CSprite2d *CRadar::LuigiSprite = (CSprite2d*)0x8F1A3C;
CSprite2d *CRadar::NorthSprite = (CSprite2d*)0x8F6274;
CSprite2d *CRadar::RaySprite = (CSprite2d*)0x8E2A7C;
CSprite2d *CRadar::SalSprite = (CSprite2d*)0x8F29EC;
CSprite2d *CRadar::SaveSprite = (CSprite2d*)0x8F5F74;
CSprite2d *CRadar::SpraySprite = (CSprite2d*)0x94307C;
CSprite2d *CRadar::TonySprite = (CSprite2d*)0x885B58;
CSprite2d *CRadar::WeaponSprite = (CSprite2d*)0x941534;

CSprite2d *CRadar::RadarSprites[RADAR_SPRITE_COUNT] = { 
	NULL,
	AsukaSprite,
	BombSprite,
	CatSprite,
	CentreSprite,
	CopcarSprite,
	DonSprite,
	EightSprite,
	ElSprite,
	IceSprite,
	JoeySprite,
	KenjiSprite,
	LizSprite,
	LuigiSprite,
	NorthSprite,
	RaySprite,
	SalSprite,
	SaveSprite,
	SpraySprite,
	TonySprite,
	WeaponSprite
};

#define RADAR_NUM_TILES (8)

#define RADAR_MIN_RANGE (120.0f)
#define RADAR_MAX_RANGE (350.0f)
#define RADAR_MIN_SPEED (0.3f)
#define RADAR_MAX_SPEED (0.9f)

#if 0
WRAPPER void CRadar::DrawMap () { EAXJMP(0x4A4200); }
#else
void CRadar::DrawMap()
{
	if (!TheCamera.m_WideScreenOn && CHud::m_Wants_To_Draw_Hud) {
		if (FindPlayerVehicle()) {
			float speed = FindPlayerSpeed().Magnitude();
			if (speed < RADAR_MIN_SPEED)
				m_RadarRange = RADAR_MIN_RANGE;
			else if (speed < RADAR_MAX_SPEED)
				m_RadarRange = (speed - RADAR_MIN_SPEED)/(RADAR_MAX_SPEED-RADAR_MIN_SPEED) * (RADAR_MAX_RANGE-RADAR_MIN_RANGE) + RADAR_MIN_RANGE;
			else
				m_RadarRange = RADAR_MAX_RANGE;
		}
		else
			m_RadarRange = RADAR_MIN_RANGE;

		vec2DRadarOrigin = CVector2D(FindPlayerCentreOfWorld_NoSniperShift());
		DrawRadarMap();
	}
}
#endif 

#if 0
WRAPPER void CRadar::DrawRadarMask() { EAXJMP(0x4A69C0); }
#else
void CRadar::DrawRadarMask() 
{ 
	CVector2D corners[4] = {
		CVector2D(1.0f, -1.0f),
		CVector2D(1.0f, 1.0f),
		CVector2D(-1.0f, 1.0f),
		CVector2D(-1.0, -1.0f)
	};

	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEFLAT);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwD3D8SetRenderState(rwRENDERSTATESTENCILFUNCTION, rwSTENCILFUNCTIONALWAYS);

	CVector2D out[8];
	CVector2D in;

	// Draw the shape we want to mask out from the radar in four segments
	for (int i = 0; i < 4; i++) {
		// First point is always the corner itself
		in.x = corners[i].x;
		in.y = corners[i].y;
		TransformRadarPointToScreenSpace(out[0], in);

		// Then generate a quarter of the circle
		for (int j = 0; j < 7; j++) {
			in.x = corners[i].x * cos(j * (PI / 2.0f / 6.0f));
			in.y = corners[i].y * sin(j * (PI / 2.0f / 6.0f));
			TransformRadarPointToScreenSpace(out[j + 1], in);
		};

		CSprite2d::SetMaskVertices(8, (float *)out);
		RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::GetVertices(), 8);
	};

	RwD3D8SetRenderState(rwRENDERSTATESTENCILFUNCTION, rwSTENCILFUNCTIONGREATER);
}
#endif

#if 0
WRAPPER void CRadar::SetRadarMarkerState(int counter, int flag) { EAXJMP(0x4A5C60); }
#else
void CRadar::SetRadarMarkerState(int counter, int flag)
{
	CEntity *e;
	switch (ms_RadarTrace[counter].m_eBlipType) {
	case BLIP_CAR:
		e = CPools::GetVehiclePool()->GetAt(ms_RadarTrace[counter].m_nEntityHandle);
		break;
	case BLIP_CHAR:
		e = CPools::GetPedPool()->GetAt(ms_RadarTrace[counter].m_nEntityHandle);
		break;
	case BLIP_OBJECT:
		e = CPools::GetObjectPool()->GetAt(ms_RadarTrace[counter].m_nEntityHandle);
		break;
	default:
		return;
	}

	if (e)
		e->bHasBlip = flag;

}
#endif

#if 0
WRAPPER void CRadar::ClearBlipForEntity(eBlipType type, int32 id) { EAXJMP(0x4A56C0); }
#else
void CRadar::ClearBlipForEntity(eBlipType type, int32 id)
{
	for (int i = 0; i < NUMRADARBLIPS; i++) {
		if (type == ms_RadarTrace[i].m_eBlipType && id == ms_RadarTrace[i].m_nEntityHandle) {
			SetRadarMarkerState(i, 0);
			ms_RadarTrace[i].m_bInUse = 0;
			ms_RadarTrace[i].m_eBlipType = 0;
			ms_RadarTrace[i].m_eBlipDisplay = 0;
			ms_RadarTrace[i].m_IconID = 0;
		}
	};
}
#endif

#if 1
WRAPPER void CRadar::DrawRadarSection(int x, int y) { EAXJMP(0x4A67E0); }
#else
void CRadar::DrawRadarSection(int x, int y)
{
	
}
#endif

void CRadar::RequestMapSection(int x, int y)
{
	ClipRadarTileCoords(&x, &y);
	CStreaming::RequestTxd(gRadarTxdIds[x + RADAR_NUM_TILES * y], STREAMFLAGS_DONT_REMOVE|STREAMFLAGS_DEPENDENCY);
}

void CRadar::RemoveMapSection(int x, int y) 
{
	if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
		CStreaming::RemoveTxd(gRadarTxdIds[x + RADAR_NUM_TILES * y]);
}

#if 0
WRAPPER void CRadar::StreamRadarSections(int x, int y) { EAXJMP(0x4A6100); }
#else
void CRadar::StreamRadarSections(int x, int y)
{
	for (int i = 0; i < RADAR_NUM_TILES; ++i) {
		for (int j = 0; j < RADAR_NUM_TILES; ++j) {
			if ((i >= x - 1 && i <= x + 1) && (j >= y - 1 && j <= y + 1))
				RequestMapSection(i, j);
			else
				RemoveMapSection(i, j);
		};
	};
}
#endif

#if 0
WRAPPER float CRadar::LimitRadarPoint(CVector2D &point) { EAXJMP(0x4A4F30); }
#else
float CRadar::LimitRadarPoint(CVector2D &point)
{
	float dist, invdist;

	dist = point.Magnitude();
	if (dist > 1.0f) {
		invdist = 1.0f / dist;
		point.x *= invdist;
		point.y *= invdist;
	}
	return dist;
}
#endif

#if 0
WRAPPER void CRadar::TransformRealWorldToTexCoordSpace(CVector2D &out, const CVector2D &in, int x, int y) { EAXJMP(0x4A5530); }
#else
void CRadar::TransformRealWorldToTexCoordSpace(CVector2D &out, const CVector2D &in, int x, int y)
{
	out.x = in.x - (x * 500.0f + WORLD_MIN_X);
	out.y = -(in.y - ((RADAR_NUM_TILES - y) * 500.0f + WORLD_MIN_Y));
	out.x /= 500.0f;
	out.y /= 500.0f;
}
#endif

#if 0
WRAPPER void CRadar::DrawRadarMap() { EAXJMP(0x4A6C20); }
#else
void CRadar::DrawRadarMap()
{
	DrawRadarMask();

	int x = floorf((vec2DRadarOrigin.x - WORLD_MIN_X) / 500.0f);
	int y = round(7.0f - (vec2DRadarOrigin.y - WORLD_MIN_Y) / 500.0f);
	StreamRadarSections(x, y);

	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEFLAT);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)rwTEXTUREADDRESSCLAMP);
	RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE, (void*)FALSE);

	DrawRadarSection(x - 1, y - 1);
	DrawRadarSection(x, y - 1);
	DrawRadarSection(x + 1, y - 1);
	DrawRadarSection(x - 1, y);
	DrawRadarSection(x, y);
	DrawRadarSection(x + 1, y);
	DrawRadarSection(x - 1, y + 1);
	DrawRadarSection(x, y + 1);
	DrawRadarSection(x + 1, y + 1);
}
#endif

#if 0
WRAPPER void CRadar::DrawBlips() { EAXJMP(0x4A42F0); }
#else
void CRadar::DrawBlips()
{
	if (!TheCamera.m_WideScreenOn && CHud::m_Wants_To_Draw_Hud) {
		RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
		RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
		RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
		RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);

		CVector2D out;
		CVector2D in = CVector2D(0.0f, 0.0f);
		TransformRadarPointToScreenSpace(out, in);

		float angle;
		if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_TOPDOWN1)
			angle = PI + FindPlayerHeading();
		else
			angle = FindPlayerHeading() - (PI + atan2(-TheCamera.GetForward().x, TheCamera.GetForward().y));

		DrawRotatingRadarSprite(CentreSprite, out.x, out.y, angle, 255);

		CVector2D vec2d;
		vec2d.x = vec2DRadarOrigin.x;
		vec2d.y = M_SQRT2 * m_RadarRange + vec2DRadarOrigin.y;
		TransformRealWorldPointToRadarSpace(in, vec2d);
		LimitRadarPoint(in);
		TransformRadarPointToScreenSpace(out, in);
		DrawRadarSprite(RADAR_SPRITE_NORTH, out.x, out.y, 255);

		/*
			DrawEntityBlip
		*/
		for (int i = 0; i < NUMRADARBLIPS; i++) {
			if (ms_RadarTrace[i].m_bInUse) {
				if (ms_RadarTrace[i].m_eBlipType <= BLIP_OBJECT) {
					CEntity *e = nil;
					switch (ms_RadarTrace[i].m_eBlipType) {
					case BLIP_CAR:
						e = CPools::GetVehiclePool()->GetAt(ms_RadarTrace[i].m_nEntityHandle);
						break;
					case BLIP_CHAR:
						e = CPools::GetPedPool()->GetAt(ms_RadarTrace[i].m_nEntityHandle);
						break;
					case BLIP_OBJECT:
						e = CPools::GetObjectPool()->GetAt(ms_RadarTrace[i].m_nEntityHandle);
						break;
					};

					if (e) {
						if (ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_MARKER_ONLY) {
							if (CTheScripts::DbgFlag) {
								ShowRadarMarker(e->GetPosition(), GetRadarTraceColour(ms_RadarTrace[i].m_nColor, ms_RadarTrace[i].m_bDim), ms_RadarTrace->m_Radius);

								ms_RadarTrace[i].m_Radius = ms_RadarTrace[i].m_Radius - 0.1f;
								if (ms_RadarTrace[i].m_Radius >= 1.0f)
									ms_RadarTrace[i].m_Radius = 5.0;
							}
						}
						if (ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BLIP_ONLY) {
							vec2d = e->GetPosition();
							TransformRealWorldPointToRadarSpace(in, vec2d);
							float dist = LimitRadarPoint(in);
							int a = CalculateBlipAlpha(dist);
							TransformRadarPointToScreenSpace(out, in);

							CRGBA col = GetRadarTraceColour(ms_RadarTrace[i].m_nColor, ms_RadarTrace[i].m_bDim);

							if (ms_RadarTrace[i].m_IconID)
								DrawRadarSprite(ms_RadarTrace[i].m_IconID, out.x, out.y, a);
							else
								ShowRadarTrace(out.x, out.y, ms_RadarTrace[i].m_wScale, col.r, col.g, col.b, 255);
						}
					}
				}

				/*
					DrawCoordBlip
				*/
				if (ms_RadarTrace[i].m_eBlipType >= BLIP_COORD) {
					if (ms_RadarTrace[i].m_eBlipType != BLIP_CONTACT_POINT || ms_RadarTrace[i].m_eBlipType == BLIP_CONTACT_POINT && DisplayThisBlip(i) || !CTheScripts::IsPlayerOnAMission()) {
						if (ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_MARKER_ONLY) {
							if (CTheScripts::DbgFlag) {
								ShowRadarMarker(ms_RadarTrace[i].m_vecPos, GetRadarTraceColour(ms_RadarTrace[i].m_nColor, ms_RadarTrace[i].m_bDim), ms_RadarTrace->m_Radius);
								ms_RadarTrace[i].m_Radius = ms_RadarTrace[i].m_Radius - 0.1f;
								if (ms_RadarTrace[i].m_Radius >= 1.0f)
									ms_RadarTrace[i].m_Radius = 5.0f;
							}
						}

						if (ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BLIP_ONLY) {
							TransformRealWorldPointToRadarSpace(in, ms_RadarTrace[i].m_vec2DPos);
							float dist = LimitRadarPoint(in);
							int a = CalculateBlipAlpha(dist);
							TransformRadarPointToScreenSpace(out, in);

							CRGBA col = GetRadarTraceColour(ms_RadarTrace[i].m_nColor, ms_RadarTrace[i].m_bDim);

							if (ms_RadarTrace[i].m_IconID)
								DrawRadarSprite(ms_RadarTrace[i].m_IconID, out.x, out.y, a);
							else
								ShowRadarTrace(out.x, out.y, ms_RadarTrace[i].m_wScale, col.r, col.g, col.b, 255);
						}
					}
				}
			};
		}
	}
}
#endif

int CRadar::CalculateBlipAlpha(float dist)
{
	if (dist <= 1.0f)
		return 255;

	if (dist <= 5.0f)
		return (((1.0f - ((dist * 0.25f) - 0.25f)) * 255.0f) + (((dist * 0.25f) - 0.25f) * 128.0f));

	return 128;
}

CRGBA CRadar::GetRadarTraceColour(uint32 color, bool bright)
{
	switch (color) {
	case 0:
		if (bright)
			return CRGBA(113, 43, 73, 255);
		else
			return CRGBA(127, 0, 0, 255);
	case 1:
		if (bright)
			return CRGBA(95, 160, 106, 255);
		else
			return CRGBA(127, 0, 255, 255);
	case 2:
		if (bright)
			return CRGBA(128, 167, 243, 255);
		else
			return CRGBA(0, 127, 255, 255);
	case 3:
		if (bright)
			return CRGBA(225, 225, 225, 255);
		else
			return CRGBA(127, 127, 127, 255);
	case 4:
		if (bright)
			return CRGBA(255, 225, 0, 255);
		else
			return CRGBA(127, 127, 0, 255);
	case 5:
		if (bright)
			return CRGBA(255, 0, 255, 255);
		else
			return CRGBA(127, 0, 127, 255);
	case 6:
		if (bright)
			return CRGBA(255, 255, 255, 255);
		else
			return CRGBA(127, 127, 255, 255);
	default:
		return CRGBA(0, 0, 0, 255);
	}
}

// Radar space goes from -1.0 to 1.0 in x and y, top right is (1.0, 1.0)
void CRadar::TransformRadarPointToScreenSpace(CVector2D &out, const CVector2D &in)
{
	// FIX: game doesn't scale RADAR_LEFT here
	out.x = (in.x + 1.0f)*0.5f*SCREEN_SCALE_X(RADAR_WIDTH) + SCREEN_SCALE_X(RADAR_LEFT);
	out.y = (1.0f - in.y)*0.5f*SCREEN_SCALE_Y(RADAR_HEIGHT) + SCREEN_SCALE_FROM_BOTTOM(RADAR_BOTTOM + RADAR_HEIGHT);
}

#if 0
WRAPPER void CRadar::TransformRealWorldPointToRadarSpace(CVector2D &out, const CVector2D &in) { EAXJMP(0x4A50D0); }
#else
void CRadar::TransformRealWorldPointToRadarSpace(CVector2D &out, const CVector2D &in) 
{
	float s, c;
	if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_TOPDOWN1 || TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_TOPDOWNPED) {
		s = 0.0f;
		c = 1.0f;
	} else if (TheCamera.GetLookDirection() == LOOKING_FORWARD) {
		s = sin(atan2(-TheCamera.GetForward().x, TheCamera.GetForward().y));
		c = cos(atan2(-TheCamera.GetForward().x, TheCamera.GetForward().y));
	} else {
		CVector forward;

		if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::MODE_FIRSTPERSON) {
			forward = TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->GetForward();
			forward.Normalise();	// a bit useless...
		} else
			forward = TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->GetPosition() - TheCamera.Cams[TheCamera.ActiveCam].SourceBeforeLookBehind;

		s = sin(atan2(-forward.x, forward.y));
		c = cos(atan2(-forward.x, forward.y));	
	}
	
	float x = (in.x - vec2DRadarOrigin.x) * (1.0f / m_RadarRange);
	float y = (in.y - vec2DRadarOrigin.y) * (1.0f / m_RadarRange);
	
	out.x = s * y + c * x;
	out.y = c * y - s * x;
}
#endif 

#if 0
WRAPPER void CRadar::DrawRadarSprite(int sprite, float x, float y, int alpha) { EAXJMP(0x4A5EF0); }
#else
void CRadar::DrawRadarSprite(int sprite, float x, float y, int alpha)
{
	RadarSprites[sprite]->Draw(CRect(x - SCREEN_SCALE_X(8.0f), y - SCREEN_SCALE_Y(8.0f), x + SCREEN_SCALE_X(8.0f), y + SCREEN_SCALE_Y(8.0f)), CRGBA(255, 255, 255, alpha));
}
#endif

#if 0
WRAPPER void CRadar::ShowRadarTrace(float x, float y, uint32 size, uint32 red, uint32 green, uint32 blue, uint32 alpha) { EAXJMP(0x4A5870); }
#else
void CRadar::ShowRadarTrace(float x, float y, uint32 size, uint32 red, uint32 green, uint32 blue, uint32 alpha) 
{
	CSprite2d::DrawRect(CRect(x - SCREEN_SCALE_X(size + 1.0f), y - SCREEN_SCALE_Y(size + 1.0f), SCREEN_SCALE_X(size + 1.0f) + x, SCREEN_SCALE_Y(size + 1.0f) + y), CRGBA(0, 0, 0, alpha));
	CSprite2d::DrawRect(CRect(x - SCREEN_SCALE_X(size), y - SCREEN_SCALE_Y(size), SCREEN_SCALE_X(size) + x, SCREEN_SCALE_Y(size) + y), CRGBA(red, green, blue, alpha));
}
#endif

#if 0
WRAPPER void CRadar::ShowRadarMarker(CVector pos, CRGBA color, float radius) { EAXJMP(0x4A59C0); }
#else
void CRadar::ShowRadarMarker(CVector pos, CRGBA color, float radius) {
	float f1 = radius * 0.5f;
	float f2 = radius * 1.4f;
	CVector p1, p2;

	p1 = pos + TheCamera.GetUp()*f1;
	p2 = pos + TheCamera.GetUp()*f2;
	CTheScripts::ScriptDebugLine3D(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, color.color32, color.color32);

	p1 = pos - TheCamera.GetUp()*f1;
	p2 = pos - TheCamera.GetUp()*f2;
	CTheScripts::ScriptDebugLine3D(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, color.color32, color.color32);

	p1 = pos + TheCamera.GetRight()*f1;
	p2 = pos + TheCamera.GetRight()*f2;
	CTheScripts::ScriptDebugLine3D(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, color.color32, color.color32);

	p1 = pos - TheCamera.GetRight()*f1;
	p2 = pos - TheCamera.GetRight()*f2;
	CTheScripts::ScriptDebugLine3D(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, color.color32, color.color32);
}
#endif

#if 0
WRAPPER void CRadar::DrawRotatingRadarSprite(CSprite2d* sprite, float x, float y, float angle, int alpha) { EAXJMP(0x4A5D10); }
#else
void CRadar::DrawRotatingRadarSprite(CSprite2d* sprite, float x, float y, float angle, int alpha)
{
	CVector curPosn[4];
	CVector oldPosn[4];

	curPosn[0].x = x - SCREEN_SCALE_X(5.6f);
	curPosn[0].y = y + SCREEN_SCALE_Y(5.6f);
									   
	curPosn[1].x = x + SCREEN_SCALE_X(5.6f);
	curPosn[1].y = y + SCREEN_SCALE_Y(5.6f);
									   
	curPosn[2].x = x - SCREEN_SCALE_X(5.6f);
	curPosn[2].y = y - SCREEN_SCALE_Y(5.6f);
									   
	curPosn[3].x = x + SCREEN_SCALE_X(5.6f);
	curPosn[3].y = y - SCREEN_SCALE_Y(5.6f);

	for (uint32 i = 0; i < 4; i++) {
		oldPosn[i] = curPosn[i];

		curPosn[i].x = x + (oldPosn[i].x - x) * cosf(angle) + (oldPosn[i].y - y) * sinf(angle);
		curPosn[i].y = y - (oldPosn[i].x - x) * sinf(angle) + (oldPosn[i].y - y) * cosf(angle);
	}													

	sprite->Draw(curPosn[2].x, curPosn[2].y, curPosn[3].x, curPosn[3].y, curPosn[0].x, curPosn[0].y, curPosn[1].x, curPosn[1].y, CRGBA(255, 255, 255, alpha));
}
#endif 

bool CRadar::DisplayThisBlip(int counter)
{
	switch (ms_RadarTrace[counter].m_IconID) {
	case RADAR_SPRITE_BOMB:
	case RADAR_SPRITE_SPRAY:
	case RADAR_SPRITE_WEAPON:
		return true;
	default:
		return false;
	}
}

#if 0
WRAPPER void CRadar::GetTextureCorners(int x, int y, CVector2D *out) { EAXJMP(0x4A61C0); };
#else
void CRadar::GetTextureCorners(int x, int y, CVector2D *out)
{
	out[0].x = 500.0f * (x - 4);
	out[0].y = 500.0f * (3 - y);
	out[1].x = 500.0f * (y - 4 + 1);
	out[1].y = 500.0f * (3 - y);
	out[2].x = 500.0f * (y - 4 + 1);
	out[2].y = 500.0f * (3 - y + 1);
	out[3].x = 500.0f * (x - 4);
	out[3].y = 500.0f * (3 - y + 1);
}
#endif

void CRadar::ClipRadarTileCoords(int *x, int *y)
{
	if (*x < 0)
		*x = 0;
	if (*x > 7)
		*x = 7;
	if (*y < 0)
		*y = 0;
	if (*y > 7)
		*y = 7;
}

STARTPATCHES
	InjectHook(0x4A5040, CRadar::TransformRadarPointToScreenSpace, PATCH_JUMP);
ENDPATCHES
