#include "common.h"
#include "patcher.h"
#include "Game.h"
#include "main.h"
#include "Accident.h"
#include "Antennas.h"
#include "Bridge.h"
#include "Camera.h"
#include "CarCtrl.h"
#include "CarGen.h"
#include "CdStream.h"
#include "Clock.h"
#include "Clouds.h"
#include "Collision.h"
#include "Console.h"
#include "Coronas.h"
#include "Cranes.h"
#include "Credits.h"
#include "CutsceneMgr.h"
#include "Darkel.h"
#include "Debug.h"
#include "EventList.h"
#include "FileLoader.h"
#include "FileMgr.h"
#include "Fire.h"
#include "Fluff.h"
#include "Font.h"
#include "Frontend.h"
#include "GameLogic.h"
#include "Garages.h"
#include "Glass.h"
#include "Heli.h"
#include "IniFile.h"
#include "Messages.h"
#include "Pad.h"
#include "Particle.h"
#include "Phones.h"
#include "Pickups.h"
#include "Plane.h"
#include "Population.h"
#include "Record.h"
#include "Renderer.h"
#include "Replay.h"
#include "References.h"
#include "Radar.h"
#include "Restart.h"
#include "RoadBlocks.h"
#include "PedRoutes.h"
#include "Rubbish.h"
#include "RwHelper.h"
#include "SceneEdit.h"
#include "Script.h"
#include "Shadows.h"
#include "Skidmarks.h"
#include "SpecialFX.h"
#include "Sprite2d.h"
#include "Stats.h"
#include "Streaming.h"
#include "TimeCycle.h"
#include "TrafficLights.h"
#include "Train.h"
#include "TxdStore.h"
#include "User.h"
#include "WaterCannon.h"
#include "WaterLevel.h"
#include "Weapon.h"
#include "WeaponEffects.h"
#include "Weather.h"
#include "World.h"
#include "ZoneCull.h"
#include "Zones.h"

eLevelName &CGame::currLevel = *(eLevelName*)0x941514;
bool &CGame::bDemoMode = *(bool*)0x5F4DD0;
bool &CGame::nastyGame = *(bool*)0x5F4DD4;
bool &CGame::frenchGame = *(bool*)0x95CDCB;
bool &CGame::germanGame = *(bool*)0x95CD1E;
bool &CGame::noProstitutes = *(bool*)0x95CDCF;
bool &CGame::playingIntro = *(bool*)0x95CDC2;
char *CGame::aDatFile = (char*)0x773A48;


bool
CGame::InitialiseOnceBeforeRW(void)
{
	CFileMgr::Initialise();
	CdStreamInit(MAX_CDCHANNELS);
	ValidateVersion();
	return true;
}

int &gameTxdSlot = *(int*)0x628D88;

bool CGame::Initialise(const char* datFile)
{
	ResetLoadingScreenBar();
	strcpy(aDatFile, datFile);
	CPools::Initialise();
	CIniFile::LoadIniFile();
	currLevel = LEVEL_INDUSTRIAL;
	LoadingScreen("Loading the Game", "Loading generic textures", GetRandomSplashScreen());
	gameTxdSlot = CTxdStore::AddTxdSlot("generic");
	CTxdStore::Create(gameTxdSlot);
	CTxdStore::AddRef(gameTxdSlot);
	LoadingScreen("Loading the Game", "Loading particles", nil);
	int particleTxdSlot = CTxdStore::AddTxdSlot("particle");
	CTxdStore::LoadTxd(particleTxdSlot, "MODELS/PARTICLE.TXD");
	CTxdStore::AddRef(particleTxdSlot);
	CTxdStore::SetCurrentTxd(gameTxdSlot);
	LoadingScreen("Loading the Game", "Setup game variables", nil);
	CGameLogic::InitAtStartOfGame();
	CReferences::Init();
	TheCamera.Init();
	TheCamera.SetRwCamera(Scene.camera);
	CDebug::DebugInitTextBuffer();
	ThePaths.Init();
	ThePaths.AllocatePathFindInfoMem(4500);
	CWeather::Init();
	CCullZones::Init();
	CCollision::Init();
	CTheZones::Init();
	CUserDisplay::Init();
	CMessages::Init();
	CMessages::ClearAllMessagesDisplayedByGame();
	CRecordDataForGame::Init();
	CRestart::Initialise();
	CWorld::Initialise();
	CParticle::Initialise();
	CAnimManager::Initialise();
	CCutsceneMgr::Initialise();
	CCarCtrl::Init();
	InitModelIndices();
	CModelInfo::Initialise();
	CPickups::Init();
	CTheCarGenerators::Init();
	CdStreamAddImage("MODELS\\GTA3.IMG");
	CFileLoader::LoadLevel("DATA\\DEFAULT.DAT");
	CFileLoader::LoadLevel(datFile);
	CWorld::AddParticles();
	CVehicleModelInfo::LoadVehicleColours();
	CVehicleModelInfo::LoadEnvironmentMaps();
	CTheZones::PostZoneCreation();
	LoadingScreen("Loading the Game", "Setup paths", GetRandomSplashScreen());
	ThePaths.PreparePathData();
	for (int i = 0; i < NUMPLAYERS; i++)
		CWorld::Players[i].Clear();
	CWorld::Players[0].LoadPlayerSkin();
	TestModelIndices();
	LoadingScreen("Loading the Game", "Setup water", nil);
	CWaterLevel::Initialise("DATA\\WATER.DAT");
	TheConsole.Init();
	CDraw::SetFOV(120.0f);
	CDraw::ms_fLODDistance = 500.0f;
	LoadingScreen("Loading the Game", "Setup streaming", nil);
	int txdHandle = CFileMgr::OpenFile("MODELS\\TXD.IMG", "r");
	if (txdHandle)
		CFileMgr::CloseFile(txdHandle);
	if (!CheckVideoCardCaps() && txdHandle) {
		CdStreamAddImage("MODELS\\TXD.IMG");
		CStreaming::Init();
	} else {
		CStreaming::Init();
		if (ConvertTextures()) {
			CStreaming::Shutdown();
			CdStreamAddImage("MODELS\\TXD.IMG");
			CStreaming::Init();
		}
	}
	CStreaming::LoadInitialVehicles();
	CStreaming::LoadInitialPeds();
	CStreaming::RequestBigBuildings(LEVEL_NONE);
	CStreaming::LoadAllRequestedModels(false);
	printf("Streaming uses %dK of its memory", CStreaming::ms_memoryUsed / 1024);
	LoadingScreen("Loading the Game", "Load animations", GetRandomSplashScreen());
	CAnimManager::LoadAnimFiles();
	CPed::Initialise();
	CRouteNode::Initialise();
	CEventList::Initialise();
	LoadingScreen("Loading the Game", "Find big buildings", nil);
	CRenderer::Init();
	LoadingScreen("Loading the Game", "Setup game variables", nil);
	CRadar::Initialise();
	CRadar::LoadTextures();
	CWeapon::InitialiseWeapons();
	LoadingScreen("Loading the Game", "Setup traffic lights", nil);
	CTrafficLights::ScanForLightsOnMap();
	CRoadBlocks::Init();
	LoadingScreen("Loading the Game", "Setup game variables", nil);
	CPopulation::Initialise();
	CWorld::PlayerInFocus = 0;
	CCoronas::Init();
	CShadows::Init();
	CWeaponEffects::Init();
	CSkidmarks::Init();
	CAntennas::Init();
	CGlass::Init();
	gPhoneInfo.Initialise();
	CSceneEdit::Init();
	LoadingScreen("Loading the Game", "Load scripts", nil);
	CTheScripts::Init();
	CGangs::Initialize();
	LoadingScreen("Loading the Game", "Setup game variables", nil);
	CClock::Initialise(1000);
	CHeli::InitHelis();
	CCranes::InitCranes();
	CMovingThings::Init();
	CDarkel::Init();
	CStats::Init();
	CPacManPickups::Init();
	CRubbish::Init();
	CClouds::Init();
	CSpecialFX::Init();
	CWaterCannons::Init();
	CBridge::Init();
	CGarages::Init();
	LoadingScreen("Loading the Game", "Position dynamic objects", nil);
	CWorld::RepositionCertainDynamicObjects();
	LoadingScreen("Loading the Game", "Initialise vehicle paths", nil);
	CCullZones::ResolveVisibilities();
	CTrain::InitTrains();
	CPlane::InitPlanes();
	CCredits::Init();
	CRecordDataForChase::Init();
	CReplay::Init();
	LoadingScreen("Loading the Game", "Start script", nil);
	CTheScripts::StartTestScript();
	CTheScripts::Process();
	TheCamera.Process();
	LoadingScreen("Loading the Game", "Load scene", nil);
	CModelInfo::RemoveColModelsFromOtherLevels(CGame::currLevel);
	CCollision::ms_collisionInMemory = CGame::currLevel;
	for (int i = 0; i < MAX_PADS; i++)
		CPad::GetPad(i)->Clear(true);
	return true;
}

extern void (*DebugMenuProcess)(void);
void CGame::Process(void) 
{
	CPad::UpdatePads();
	TheCamera.SetMotionBlurAlpha(0);
	if (TheCamera.m_BlurType == MBLUR_NONE || TheCamera.m_BlurType == MBLUR_SNIPER || TheCamera.m_BlurType == MBLUR_NORMAL)
		TheCamera.SetMotionBlur(0, 0, 0, 0, MBLUR_NONE);

	DebugMenuProcess();
	CCutsceneMgr::Update();
	if (!CCutsceneMgr::IsCutsceneProcessing() && !CTimer::GetIsCodePaused())
		FrontEndMenuManager.Process();
	CStreaming::Update();
	if (!CTimer::GetIsPaused())
	{
		CTheZones::Update();
		CSprite2d::SetRecipNearClip();
		CSprite2d::InitPerFrame();
		CFont::InitPerFrame();
		CRecordDataForGame::SaveOrRetrieveDataForThisFrame();
		CRecordDataForChase::SaveOrRetrieveDataForThisFrame();
		CPad::DoCheats();
		CClock::Update();
		CWeather::Update();
		CTheScripts::Process();
		CCollision::Update();
		CTrain::UpdateTrains();
		CPlane::UpdatePlanes();
		CHeli::UpdateHelis();
		CDarkel::Update();
		CSkidmarks::Update();
		CAntennas::Update();
		CGlass::Update();
		CSceneEdit::Update();
		CEventList::Update();
		CParticle::Update();
		gFireManager.Update();
		CPopulation::Update();
		CWeapon::UpdateWeapons();
		if (!CCutsceneMgr::IsRunning())
			CTheCarGenerators::Process();
		if (!CReplay::IsPlayingBack())
			CCranes::UpdateCranes();
		CClouds::Update();
		CMovingThings::Update();
		CWaterCannons::Update();
		CUserDisplay::Process();
		CReplay::Update();
		CWorld::Process();
		gAccidentManager.Update();
		CPacManPickups::Update();
		CPickups::Update();
		CGarages::Update();
		CRubbish::Update();
		CSpecialFX::Update();
		CTimeCycle::Update();
		if (CReplay::ShouldStandardCameraBeProcessed())
			TheCamera.Process();
		CCullZones::Update();
		if (!CReplay::IsPlayingBack())
			CGameLogic::Update();
		CBridge::Update();
		CCoronas::DoSunAndMoon();
		CCoronas::Update();
		CShadows::UpdateStaticShadows();
		CShadows::UpdatePermanentShadows();
		gPhoneInfo.Update();
		if (!CReplay::IsPlayingBack())
		{
			CCarCtrl::GenerateRandomCars();
			CRoadBlocks::GenerateRoadBlocks();
			CCarCtrl::RemoveDistantCars();
		}
	}
}

void CGame::ReloadIPLs(void)
{
	CTimer::Stop();
	CWorld::RemoveStaticObjects();
	ThePaths.Init();
	CCullZones::Init();
	CFileLoader::ReloadPaths("GTA3.IDE");
	CFileLoader::LoadScene("INDUST.IPL");
	CFileLoader::LoadScene("COMMER.IPL");
	CFileLoader::LoadScene("SUBURBAN.IPL");
	CFileLoader::LoadScene("CULL.IPL");
	ThePaths.PreparePathData();
	CTrafficLights::ScanForLightsOnMap();
	CRoadBlocks::Init();
	CCranes::InitCranes();
	CGarages::Init();
	CWorld::RepositionCertainDynamicObjects();
	CCullZones::ResolveVisibilities();
	CRenderer::SortBIGBuildings();
	CTimer::Update();
}

void
CGame::FinalShutdown(void)
{
	CTxdStore::Shutdown();
	CPedStats::Shutdown();
	CdStreamShutdown();
}

WRAPPER bool CGame::InitialiseRenderWare(void) { EAXJMP(0x48BBA0); }
WRAPPER void CGame::ShutdownRenderWare(void) { EAXJMP(0x48BCB0); }
WRAPPER void CGame::ShutDown(void) { EAXJMP(0x48C3A0); }
WRAPPER void CGame::ShutDownForRestart(void) { EAXJMP(0x48C6B0); }
WRAPPER void CGame::InitialiseWhenRestarting(void) { EAXJMP(0x48C740); }
WRAPPER bool CGame::InitialiseOnceAfterRW(void) { EAXJMP(0x48BD50); }

STARTPATCHES
	InjectHook(0x48C850, CGame::Process, PATCH_JUMP);
	InjectHook(0x48BEC0, CGame::FinalShutdown, PATCH_JUMP);
ENDPATCHES
