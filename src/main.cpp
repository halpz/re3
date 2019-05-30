#include "common.h"
#include "patcher.h"
#include "RwHelper.h"
#include "Clouds.h"
#include "Draw.h"
#include "Sprite2d.h"
#include "Renderer.h"
#include "Coronas.h"
#include "WaterLevel.h"
#include "Weather.h"
#include "Glass.h"
#include "WaterCannon.h"
#include "SpecialFX.h"
#include "Shadows.h"
#include "Skidmarks.h"
#include "Antennas.h"
#include "Rubbish.h"
#include "Particle.h"
#include "Pickups.h"
#include "WeaponEffects.h"
#include "PointLights.h"
#include "Fluff.h"
#include "Replay.h"
#include "Camera.h"
#include "World.h"
#include "Ped.h"
#include "Font.h"
#include "Pad.h"
#include "Hud.h"
#include "User.h"
#include "Messages.h"
#include "Darkel.h"
#include "Garages.h"
#include "MusicManager.h"
#include "Frontend.h"

// This is certainly a very useful function
void
DoRWRenderHorizon(void)
{
	CClouds::RenderHorizon();
}

void
RenderScene(void)
{
	CClouds::Render();
	DoRWRenderHorizon();
	CRenderer::RenderRoads();
	CCoronas::RenderReflections();
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
	CRenderer::RenderEverythingBarRoads();
	CRenderer::RenderBoats();
	DefinedState();
	CWaterLevel::RenderWater();
	CRenderer::RenderFadingInEntities();
	CRenderer::RenderVehiclesButNotBoats();
	CWeather::RenderRainStreaks();
}

void
RenderDebugShit(void)
{
	// CTheScripts::RenderTheScriptDebugLines()
}

void
RenderEffects(void)
{
	CGlass::Render();
	CWaterCannons::Render();
	CSpecialFX::Render();
	CShadows::RenderStaticShadows();
	CShadows::RenderStoredShadows();
	CSkidmarks::Render();
	CAntennas::Render();
	CRubbish::Render();
	CCoronas::Render();
	CParticle::Render();
	CPacManPickups::Render();
	CWeaponEffects::Render();
	CPointLights::RenderFogEffect();
	CMovingThings::Render();
	CRenderer::RenderFirstPersonVehicle();
}

void
Render2dStuff(void)
{
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);

	CReplay::Display();
	CPickups::RenderPickUpText();

	if(TheCamera.m_WideScreenOn)
		TheCamera.DrawBordersForWideScreen();

	CPed *player = FindPlayerPed();
	int weaponType = 0;
	if(player)
		weaponType = player->GetWeapon()->m_eWeaponType;

	bool firstPersonWeapon = false;
	int cammode = TheCamera.Cams[TheCamera.ActiveCam].Mode;
	if(cammode == CCam::MODE_SNIPER ||
	   cammode == CCam::MODE_SNIPER_RUN_AROUND ||
	   cammode == CCam::MODE_ROCKET ||
	   cammode == CCam::MODE_ROCKET_RUN_AROUND)
		firstPersonWeapon = true;

	// Draw black border for sniper and rocket launcher
	if((weaponType == WEAPONTYPE_SNIPERRIFLE || weaponType == WEAPONTYPE_ROCKETLAUNCHER) && firstPersonWeapon){
		CRGBA black(0, 0, 0, 255);

		// top and bottom strips
		if(weaponType == WEAPONTYPE_ROCKETLAUNCHER){
			CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREENW, SCREENH/2 - SCREEN_STRETCH_Y(180)), black);
			CSprite2d::DrawRect(CRect(0.0f, SCREENH/2 + SCREEN_STRETCH_Y(170), SCREENW, SCREENH), black);
		}else{
			CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREENW, SCREENH/2 - SCREEN_STRETCH_Y(210)), black);
			CSprite2d::DrawRect(CRect(0.0f, SCREENH/2 + SCREEN_STRETCH_Y(210), SCREENW, SCREENH), black);
		}
		CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREENW/2 - SCREEN_STRETCH_X(210), SCREENH), black);
		CSprite2d::DrawRect(CRect(SCREENW/2 + SCREEN_STRETCH_X(210), 0.0f, SCREENW, SCREENH), black);
	}

	MusicManager.DisplayRadioStationName();
//	TheConsole.Display();
/*
	if(CSceneEdit::m_bEditOn)
		CSceneEdit::Draw();
	else
*/
		CHud::Draw();
	CUserDisplay::OnscnTimer.ProcessForDisplay();
	CMessages::Display();
	CDarkel::DrawMessages();
	CGarages::PrintMessages();
	CPad::PrintErrorMessage();
	CFont::DrawFonts();
}

void
RenderMenus(void)
{
	if(FrontEndMenuManager.m_bMenuActive)
		FrontEndMenuManager.DrawFrontEnd();
}

bool &JustLoadedDontFadeInYet = *(bool*)0x95CDB4;
bool &StillToFadeOut = *(bool*)0x95CD99;
int32 &TimeStartedCountingForFade = *(int32*)0x9430EC;
int32 &TimeToStayFadedBeforeFadeOut = *(int32*)0x611564;

void
DoFade(void)
{
	if(CTimer::GetIsPaused())
		return;

	if(JustLoadedDontFadeInYet){
		JustLoadedDontFadeInYet = false;
		TimeStartedCountingForFade = CTimer::GetTimeInMilliseconds();
	}

	if(StillToFadeOut){
		if(CTimer::GetTimeInMilliseconds() - TimeStartedCountingForFade > TimeToStayFadedBeforeFadeOut){
			StillToFadeOut = false;
			TheCamera.Fade(3.0f, 1);
			TheCamera.ProcessFade();
			TheCamera.ProcessMusicFade();
		}else{
			TheCamera.SetFadeColour(0, 0, 0);
			TheCamera.Fade(0.0f, 0);
			TheCamera.ProcessFade();
		}
	}

	if(CDraw::FadeValue != 0 || CMenuManager::m_PrefsBrightness < 256){
		// LoadSplash

		CRGBA fadeColor;
		CRect rect;
		int fadeValue = CDraw::FadeValue;
		float brightness = min(CMenuManager::m_PrefsBrightness, 256);
		if(brightness <= 50)
			brightness = 50;
		if(FrontEndMenuManager.m_bMenuActive)
			brightness = 256;

		if(TheCamera.m_FadeTargetIsSplashScreen)
			fadeValue = 0;

		float fade = fadeValue + 256 - brightness;
		if(fade == 0){
			fadeColor.r = 0;
			fadeColor.g = 0;
			fadeColor.b = 0;
			fadeColor.a = 0;
		}else{
			fadeColor.r = fadeValue * CDraw::FadeRed / fade;
			fadeColor.g = fadeValue * CDraw::FadeGreen / fade;
			fadeColor.b = fadeValue * CDraw::FadeBlue / fade;
			int alpha = 255 - brightness*(256 - fadeValue)/256;
			if(alpha < 0)
				alpha = 0;
			fadeColor.a = alpha;
		}

		if(TheCamera.m_WideScreenOn){
			// what's this?
			float y = SCREENH/2 * TheCamera.m_ScreenReductionPercentage/100.0f;
			rect.left = 0.0f;
			rect.right = SCREENW;
			rect.top = y - 8.0f;
			rect.bottom = SCREENH - y - 8.0f;
		}else{
			rect.left = 0.0f;
			rect.right = SCREENW;
			rect.top = 0.0f;
			rect.bottom = SCREENH;
		}
		CSprite2d::DrawRect(rect, fadeColor);

		if(CDraw::FadeValue != 0 && TheCamera.m_FadeTargetIsSplashScreen){
			fadeColor.r = 255;
			fadeColor.g = 255;
			fadeColor.b = 255;
			fadeColor.a = CDraw::FadeValue;
			CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREENW, SCREENH), fadeColor, fadeColor, fadeColor, fadeColor);
		}
	}
}

void
Render2dStuffAfterFade(void)
{
	CHud::DrawAfterFade();
	CFont::DrawFonts();
}


STARTPATCHES
	InjectHook(0x48E030, RenderScene, PATCH_JUMP);
	InjectHook(0x48E080, RenderDebugShit, PATCH_JUMP);
	InjectHook(0x48E090, RenderEffects, PATCH_JUMP);
	InjectHook(0x48E0E0, Render2dStuff, PATCH_JUMP);
	InjectHook(0x48E450, RenderMenus, PATCH_JUMP);
	InjectHook(0x48D120, DoFade, PATCH_JUMP);
	InjectHook(0x48E470, Render2dStuffAfterFade, PATCH_JUMP);
ENDPATCHES
