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

WRAPPER void CRadar::ClearBlipForEntity(eBlipType type, int32 id) { EAXJMP(0x4A56C0); }
WRAPPER void CRadar::Draw3dMarkers() { EAXJMP(0x4A4C70); }
WRAPPER void CRadar::DrawRadarMap() { EAXJMP(0x4A6C20); }
WRAPPER float CRadar::LimitRadarPoint(CVector2D *point) { EAXJMP(0x4A4F30); }
WRAPPER void CRadar::ShowRadarTrace(float x, float y, uint32 size, uint32 red, uint32 green, uint32 blue, uint32 alpha) { EAXJMP(0x4A5870); }

float &CRadar::m_RadarRange = *(float*)0x8E281C;
CVector2D &CRadar::vec2DRadarOrigin = *(CVector2D*)0x6299B8;
CBlip *CRadar::ms_RadarTrace = (CBlip*)0x6ED5E0;
float CRadar::cachedSin;
float CRadar::cachedCos;

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

#if 0
WRAPPER void CRadar::DrawMap () { EAXJMP(0x4A4200); }
#else
void CRadar::DrawMap()
{
	if (!TheCamera.m_WideScreenOn && CHud::m_Wants_To_Draw_Hud) {
		if (FindPlayerVehicle()) {
			if (FindPlayerVehicle()->GetSpeed().Magnitude() > 0.3f) {
				if (FindPlayerVehicle()->GetSpeed().Magnitude() > 0.9f)
					CRadar::m_RadarRange = 350.0f;
				else
					CRadar::m_RadarRange = (FindPlayerVehicle()->GetSpeed().Magnitude() + 0.3f) * 200.0f;
			}
			else
				CRadar::m_RadarRange = 120.0f;
		}
		else
			CRadar::m_RadarRange = 120.0f;

		vec2DRadarOrigin.x = FindPlayerCentreOfWorld_NoSniperShift().x;
		vec2DRadarOrigin.y = FindPlayerCentreOfWorld_NoSniperShift().y;
		CRadar::DrawRadarMap();
	}
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
		CRadar::TransformRadarPointToScreenSpace(&out, &in);

		float angle;
		if (TheCamera.Cams[TheCamera.ActiveCam].Mode == CCam::CamMode::MODE_TOPDOWN1)
			angle = PI + FindPlayerHeading();
		else
			angle = FindPlayerHeading() - (PI + atan2(-TheCamera.m_matrix.m_matrix.up.x, TheCamera.m_matrix.m_matrix.up.y));

		CRadar::DrawRotatingRadarSprite(CentreSprite, out.x, out.y, angle, 255);

		CVector2D vec2d;
		vec2d.x = vec2DRadarOrigin.x;
		vec2d.y = M_SQRT2 * CRadar::m_RadarRange + vec2DRadarOrigin.y;
		CRadar::TransformRealWorldPointToRadarSpace(&in, &vec2d);
		CRadar::LimitRadarPoint(&in);
		CRadar::TransformRadarPointToScreenSpace(&out, &in);
		CRadar::DrawRadarSprite(RADAR_SPRITE_NORTH, out.x, out.y, 255);

		/*
			DrawEntityBlip
		*/
		for (int i = 0; i < 32; i++) {
			if (ms_RadarTrace[i].m_bInUse) {
				if (ms_RadarTrace[i].m_eBlipType <= BLIP_OBJECT) {
					CEntity *e = nil;
					switch (CRadar::ms_RadarTrace[i].m_eBlipType) {
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
						if (CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_MARKER_ONLY) {
							if (CTheScripts::DbgFlag) {
								CRadar::ShowRadarMarker(e->GetPosition(), CRadar::GetRadarTraceColour(CRadar::ms_RadarTrace[i].m_nColor, CRadar::ms_RadarTrace[i].m_bDim), CRadar::ms_RadarTrace->m_Radius);

								CRadar::ms_RadarTrace[i].m_Radius = CRadar::ms_RadarTrace[i].m_Radius - 0.1f;
								if (CRadar::ms_RadarTrace[i].m_Radius >= 1.0f)
									CRadar::ms_RadarTrace[i].m_Radius = 5.0;
							}
						}
						if (CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BLIP_ONLY) {
							vec2d = e->GetPosition();
							CRadar::TransformRealWorldPointToRadarSpace(&in, &vec2d);
							float dist = CRadar::LimitRadarPoint(&in);
							int a = CRadar::CalculateBlipAlpha(dist);
							CRadar::TransformRadarPointToScreenSpace(&out, &in);

							CRGBA col = CRadar::GetRadarTraceColour(CRadar::ms_RadarTrace[i].m_nColor, CRadar::ms_RadarTrace[i].m_bDim);

							if (CRadar::ms_RadarTrace[i].m_IconID)
								CRadar::DrawRadarSprite(CRadar::ms_RadarTrace[i].m_IconID, out.x, out.y, a);
							else
								CRadar::ShowRadarTrace(out.x, out.y, CRadar::ms_RadarTrace[i].m_wScale, col.r, col.g, col.b, 255);
						}
					}
				}
			}
		}

		/*
			DrawCoordBlip
		*/
		for (int i = 0; i < 32; i++) {
			if (CRadar::ms_RadarTrace[i].m_bInUse) {
				if (ms_RadarTrace[i].m_eBlipType >= BLIP_COORD) {
					if (CRadar::DisplayThisBlip(ms_RadarTrace[i].m_IconID) && CRadar::ms_RadarTrace[i].m_eBlipType != BLIP_CONTACT_POINT || !CTheScripts::IsPlayerOnAMission()) {
						if (CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_MARKER_ONLY) {
							if (CTheScripts::DbgFlag) {
								CRadar::ShowRadarMarker(CRadar::ms_RadarTrace[i].m_vecPos, CRadar::GetRadarTraceColour(CRadar::ms_RadarTrace[i].m_nColor, CRadar::ms_RadarTrace[i].m_bDim), CRadar::ms_RadarTrace->m_Radius);
								CRadar::ms_RadarTrace[i].m_Radius = CRadar::ms_RadarTrace[i].m_Radius - 0.1f;
								if (CRadar::ms_RadarTrace[i].m_Radius >= 1.0f)
									CRadar::ms_RadarTrace[i].m_Radius = 5.0f;
							}
						}

						if (CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BOTH || CRadar::ms_RadarTrace[i].m_eBlipDisplay == BLIP_DISPLAY_BLIP_ONLY) {
							CRadar::TransformRealWorldPointToRadarSpace(&in, &ms_RadarTrace[i].m_vec2DPos);
							float dist = CRadar::LimitRadarPoint(&in);
							int a = CRadar::CalculateBlipAlpha(dist);
							CRadar::TransformRadarPointToScreenSpace(&out, &in);

							CRGBA col = CRadar::GetRadarTraceColour(CRadar::ms_RadarTrace[i].m_nColor, CRadar::ms_RadarTrace[i].m_bDim);

							if (CRadar::ms_RadarTrace[i].m_IconID)
								CRadar::DrawRadarSprite(CRadar::ms_RadarTrace[i].m_IconID, out.x, out.y, a);
							else
								CRadar::ShowRadarTrace(out.x, out.y, CRadar::ms_RadarTrace[i].m_wScale, col.r, col.g, col.b, 255);
						}
					}
				}
			};
		}
	}
}
#endif

bool CRadar::DisplayThisBlip(int16 spriteid) 
{
	switch (spriteid) {
		case RADAR_SPRITE_NONE:
			return true;
			break;
		case RADAR_SPRITE_ASUKA:
		case RADAR_SPRITE_BOMB:
		case RADAR_SPRITE_CAT:
			return false;
			break;
		case RADAR_SPRITE_CENTRE:
			return true;
			break;
		case RADAR_SPRITE_COPCAR:
		case RADAR_SPRITE_DON:
		case RADAR_SPRITE_EIGHT:
		case RADAR_SPRITE_EL:
		case RADAR_SPRITE_ICE:
		case RADAR_SPRITE_JOEY:
		case RADAR_SPRITE_KENJI:
		case RADAR_SPRITE_LIZ:
		case RADAR_SPRITE_LUIGI:
			return false;
			break;
		case RADAR_SPRITE_NORTH:
			return true;
			break;
		case RADAR_SPRITE_RAY:
		case RADAR_SPRITE_SAL:
		case RADAR_SPRITE_SAVE:
		case RADAR_SPRITE_SPRAY:
		case RADAR_SPRITE_TONY:
		case RADAR_SPRITE_WEAPON:
			return false;
			break;
	};
}

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
		break;
	case 1:
		if (bright)
			return CRGBA(95, 160, 106, 255);
		else
			return CRGBA(127, 0, 255, 255);
		break;
	case 2:
		if (bright)
			return CRGBA(128, 167, 243, 255);
		else
			return CRGBA(0, 127, 255, 255);
		break;
	case 3:
		if (bright)
			return CRGBA(225, 225, 225, 255);
		else
			return CRGBA(127, 127, 127, 255);
		break;
	case 4:
		if (bright)
			return CRGBA(255, 225, 0, 255);
		else
			return CRGBA(127, 127, 0, 255);
		break;
	case 5:
		if (bright)
			return CRGBA(255, 0, 255, 255);
		else
			return CRGBA(127, 0, 127, 255);
		break;
	case 6:
		if (bright)
			return CRGBA(255, 255, 255, 255);
		else
			return CRGBA(127, 127, 255, 255);
		break;
	default:
		return CRGBA(0, 0, 0, 255);
		break;
	}
}

void CRadar::TransformRadarPointToScreenSpace(CVector2D *out, CVector2D *in)
{
	out->x = in->x * SCREEN_SCALE_X(47.0f) + SCREEN_SCALE_X(47.0f + 20.0f);
	out->y = (SCREEN_SCALE_Y(76.0f)) * 0.5f + SCREEN_HEIGHT - (SCREEN_SCALE_Y(123.0f)) - in->y * (SCREEN_SCALE_Y(76.0f)) * 0.5f;
}

#if 0
WRAPPER void CRadar::TransformRealWorldPointToRadarSpace(CVector2D *out, CVector2D *in) { EAXJMP(0x4A50D0); }
#else
void CRadar::TransformRealWorldPointToRadarSpace(CVector2D *out, CVector2D *in) 
{ 
	if (TheCamera.Cams->Mode != CCam::CamMode::MODE_TOPDOWN1 && TheCamera.Cams->Mode != CCam::CamMode::MODE_TOPDOWNPED) {
		if (TheCamera.GetLookDirection() != LOOKING_FORWARD) {
			cachedSin = sin(atan2(-TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->m_matrix.m_matrix.up.x, TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->m_matrix.m_matrix.up.y));
			cachedCos = cos(atan2(-TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->m_matrix.m_matrix.up.x, TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->m_matrix.m_matrix.up.y));
		}
		else {
			CVector vecCamera;

			if (TheCamera.Cams->Mode == CCam::CamMode::MODE_FIRSTPERSON) {
				vecCamera = TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->m_matrix.m_matrix.up;
				vecCamera.Normalise();
			}
			else
				vecCamera = TheCamera.Cams[TheCamera.ActiveCam].CamTargetEntity->m_matrix.m_matrix.pos - TheCamera.Cams[TheCamera.ActiveCam].SourceBeforeLookBehind;
		
			cachedSin = sin(atan2(-vecCamera.x, vecCamera.y));
			cachedCos = cos(atan2(-vecCamera.x, vecCamera.y));	
		}
	}
	else {
		cachedSin = 0.0f;
		cachedCos = 1.0f;
	}
	
	float x = (in->x - vec2DRadarOrigin.x) * (1.0f / m_RadarRange);
	float y = (in->y - vec2DRadarOrigin.y) * (1.0f / m_RadarRange);
	
	out->x = cachedSin * y + cachedCos * x;
	out->y = cachedCos * y - cachedSin * x;
}
#endif 

#if 0
WRAPPER void CRadar::DrawRadarSprite(int sprite, float x, float y, int alpha) { EAXJMP(0x4A5EF0); }
#else
void CRadar::DrawRadarSprite(int sprite, float x, float y, int alpha)
{ 
	float w = SCREEN_SCALE_X(8.0f);
	float h = SCREEN_SCALE_Y(8.0f);

	RadarSprites[sprite]->Draw(CRect(x - w, y - h, x + w, y + h), CRGBA(255, 255, 255, alpha));
}
#endif

#if 0
WRAPPER void CRadar::ShowRadarMarker(CVector pos, CRGBA color, float radius) { EAXJMP(0x4A59C0); }
#else
void CRadar::ShowRadarMarker(CVector pos, CRGBA color, float radius) {
	float z2 = pos.z + (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.at.z;
	float y2 = (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.at.y + pos.y;
	float x2 = (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.at.x + pos.x;
	float z1 = pos.z + (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.at.z;
	float y1 = (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.at.y + pos.y;
	float x1 = (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.at.x + pos.x;
	CTheScripts::ScriptDebugLine3D(x1, y1, z1, x2, y2, z2, color.color32, color.color32);

	z2 = pos.z - (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.at.x;
	y2 = pos.y - (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.at.x;
	x2 = pos.x - (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.at.x;
	z1 = pos.z - (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.at.x;
	y1 = pos.y - (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.at.x;
	x1 = pos.x - (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.at.x;
	CTheScripts::ScriptDebugLine3D(x1, y1, z1, x2, y2, z2, color.color32, color.color32);

	z2 = (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.right.x + pos.z;
	y2 = (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.right.x + pos.y;
	x2 = (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.right.x + pos.x;
	z1 = (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.right.x + pos.z;
	y1 = (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.right.x + pos.y;
	x1 = (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.right.x + pos.x;
	CTheScripts::ScriptDebugLine3D(x1, y1, z1, x2, y2, z2, color.color32, color.color32);

	z2 = pos.z - (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.right.x;
	y2 = pos.y - (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.right.x;
	x2 = pos.x - (0.5f * color.color32) * TheCamera.m_matrix.m_matrix.right.x;
	z1 = pos.z - (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.right.x;
	y1 = pos.y - (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.right.x;
	x1 = pos.x - (1.4f * color.color32) * TheCamera.m_matrix.m_matrix.right.x;
	CTheScripts::ScriptDebugLine3D(x1, y1, z1, x2, y2, z2, color.color32, color.color32);
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

		curPosn[i].x = x + (oldPosn[i].x - x) * cosf(angle) + (oldPosn[i].y - y) *  sinf(angle);
		curPosn[i].y = y - (oldPosn[i].x - x) *  sinf(angle) + (oldPosn[i].y - y) * cosf(angle);
	}													

	sprite->Draw(curPosn[2].x, curPosn[2].y, curPosn[3].x, curPosn[3].y, curPosn[0].x, curPosn[0].y, curPosn[1].x, curPosn[1].y, CRGBA(255, 255, 255, alpha));
}
#endif 

STARTPATCHES
	InjectHook(0x4A5040, CRadar::TransformRadarPointToScreenSpace, PATCH_JUMP);
ENDPATCHES
