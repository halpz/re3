#include "common.h"
#include "patcher.h"
#include "SceneEdit.h"

#include "Camera.h"
#include "FileMgr.h"
#include "Font.h"
#include "ModelIndices.h"
#include "ModelInfo.h"
#include "Ped.h"
#include "Population.h"
#include "Text.h"
#include "Vehicle.h"
#include "World.h"

bool CSceneEdit::m_bEditOn;
int32 CSceneEdit::m_bCameraFollowActor;
bool CSceneEdit::m_bRecording;
CVector CSceneEdit::m_vecCurrentPosition;
CVector CSceneEdit::m_vecCamHeading;
CVector CSceneEdit::m_vecGotoPosition;
int32 CSceneEdit::m_nVehicle;
int32 CSceneEdit::m_nVehicle2;
int32 CSceneEdit::m_nActor;
int32 CSceneEdit::m_nActor2;
int32 CSceneEdit::m_nVehiclemodelId;
int32 CSceneEdit::m_nPedmodelId;
int16 CSceneEdit::m_nCurrentMovieCommand;
int16 CSceneEdit::m_nNumActors;
int16 CSceneEdit::m_nNumMovieCommands;
int16 CSceneEdit::m_nCurrentCommand;
int16 CSceneEdit::m_nCurrentVehicle;
bool CSceneEdit::m_bCommandActive;
int16 CSceneEdit::m_nNumVehicles;
CPed* CSceneEdit::pActors[NUM_ACTORS_IN_MOVIE];
CVehicle* CSceneEdit::pVehicles[NUM_VEHICLES_IN_MOVIE];
bool CSceneEdit::m_bDrawGotoArrow;
CMovieCommand CSceneEdit::Movie[NUM_COMMANDS_IN_MOVIE];

#define SHADOW_OFFSET (2.0f)
#define ACTION_MESSAGE_X_RIGHT (60.0f)
#define ACTION_MESSAGE_Y (8.0f)
#define SELECTED_MESSAGE_X_RIGHT (60.0f)
#define SELECTED_MESSAGE_Y (248.0f)
#define COMMAND_NAME_X_RIGHT (60.0f)
#define COMMAND_NAME_Y (38.0f)
#define COMMAND_NAME_HEIGHT (16.0f)

#define NUM_COMMANDS_TO_DRAW (9)

static const char* pCommandStrings[] = {
	"do-nothing", "New Actor", "Move Actor", "Select Actor", "Delete Actor",
	"New Vehicle", "Move Vehicle", "Select Vehicle", "Delete Vehicle", "Give Weapon",
	"Goto", "Goto (wait)", "Get In Car", "Get Out Car", "Kill",
	"Flee", "Wait", "Position Camera", "Set Camera Target", "Select Camera Mode",
	"Save Movie", "Load Movie", "Play Movie", "END"
};

static_assert(ARRAY_SIZE(pCommandStrings) == CSceneEdit::MOVIE_TOTAL_COMMANDS, "Scene edit: not all commands have names");

static int32 NextValidModelId(int32 mi, int32 step)
{
	int32 result = -1;
	int32 i = mi;
	while (result == -1) {
		if (i < 0 || i > 5500) {
			i = -i;
			continue;
		}
		CBaseModelInfo* pInfo = CModelInfo::GetModelInfo(i);
		CVehicleModelInfo* pVehicleInfo = (CVehicleModelInfo*)pInfo;
		if (!i)
			continue;
		if (pInfo->m_type == MITYPE_PED ||
			pInfo->m_type == MITYPE_VEHICLE &&
#ifdef FIX_BUGS
			(pVehicleInfo->m_vehicleType == VEHICLE_TYPE_CAR || pVehicleInfo->m_vehicleType == VEHICLE_TYPE_BOAT))
#else // && and || priority failure it seems
			pVehicleInfo->m_vehicleType == VEHICLE_TYPE_CAR || pVehicleInfo->m_vehicleType == VEHICLE_TYPE_BOAT)
#endif
			result = i;
	}
	return result;
}

void CSceneEdit::LoadMovie(void)
{
	ReInitialise();
	CFileMgr::SetDir("DATA");
	int fid = CFileMgr::OpenFile("movie.dat", "r");
#ifdef FIX_BUGS
	if (fid > 0)
#endif
	{
		CFileMgr::Read(fid, (char*)Movie, sizeof(Movie));
		CFileMgr::Read(fid, (char*)m_nNumMovieCommands, sizeof(m_nNumMovieCommands));
		CFileMgr::CloseFile(fid);
	}
	CFileMgr::SetDir("");
	m_bCommandActive = false;
}

void CSceneEdit::SaveMovie(void)
{
	CFileMgr::SetDir("DATA");
	int fid = CFileMgr::OpenFileForWriting("movie.dat");
	if (fid >= 0) {
		CFileMgr::Write(fid, (char*)Movie, sizeof(Movie));
		CFileMgr::Write(fid, (char*)m_nNumMovieCommands, sizeof(m_nNumMovieCommands));
		CFileMgr::CloseFile(fid);
	}
	CFileMgr::SetDir("");
	m_bCommandActive = false;
}

void CSceneEdit::Initialise(void)
{
	m_nActor = -1;
	m_nActor2 = -1;
	m_nVehicle = -1;
	m_nVehicle2 = -1;
	m_nCurrentCommand = MOVIE_NEW_ACTOR;
	m_nVehiclemodelId = MI_INFERNUS;
	m_nPedmodelId = MI_MALE01;
	m_nNumVehicles = 0;
	m_nNumActors = 0;
	m_nNumMovieCommands = 0;
	m_bCommandActive = false;
	m_bRecording = true;
	m_bEditOn = false;
	for (int i = 0; i < NUM_ACTORS_IN_MOVIE; i++)
		pActors[i] = nil;
	for (int i = 0; i < NUM_VEHICLES_IN_MOVIE; i++)
		pVehicles[i] = nil;
	m_vecCamHeading = TheCamera.Cams[TheCamera.ActiveCam].Front;
	m_vecGotoPosition = CVector(0.0f, 0.0f, 0.0f);
	m_bCameraFollowActor = false;
	TheCamera.Cams[TheCamera.ActiveCam].ResetStatics = true;
	m_bDrawGotoArrow = false;
}

void CSceneEdit::InitPlayback(void)
{
	m_nVehiclemodelId = MI_INFERNUS;
	m_nPedmodelId = MI_MALE01;
	m_bCommandActive = false;
	m_nNumActors = 0;
	m_nNumVehicles = 0;
	m_nActor = -1;
	m_nActor2 = -1;
	m_nVehicle = -1;
	m_nVehicle2 = -1;
	TheCamera.Cams[TheCamera.ActiveCam].ResetStatics = true;
	m_vecCamHeading = TheCamera.Cams[TheCamera.ActiveCam].Front;
	for (int i = 0; i < NUM_ACTORS_IN_MOVIE; i++) {
		if (pActors[i]) {
			CPopulation::RemovePed(pActors[i]);
			pActors[i] = nil;
		}
	}
	for (int i = 0; i < NUM_VEHICLES_IN_MOVIE; i++) {
		if (pVehicles[i]) {
			CWorld::Remove(pVehicles[i]);
			delete pVehicles[i];
			pVehicles[i] = nil;
		}
	}
	m_vecGotoPosition = CVector(0.0f, 0.0f, 0.0f);
	m_nCurrentVehicle = 0;
	m_nCurrentMovieCommand = MOVIE_DO_NOTHING;
	m_bDrawGotoArrow = false;
}

void CSceneEdit::ReInitialise(void)
{
	m_nVehiclemodelId = MI_INFERNUS;
	m_nPedmodelId = MI_MALE01;
	m_nCurrentCommand = MOVIE_NEW_ACTOR;
	m_bEditOn = true;
	m_bRecording = true;
	m_bCommandActive = false;
	m_nActor = -1;
	m_nActor2 = -1;
	m_nVehicle = -1;
	m_nVehicle2 = -1;
	m_nNumMovieCommands = 0;
	m_nCurrentMovieCommand = MOVIE_DO_NOTHING;
	m_nNumActors = 0;
	m_nNumVehicles = 0;
	for (int i = 0; i < NUM_ACTORS_IN_MOVIE; i++) {
		if (pActors[i]) {
			CPopulation::RemovePed(pActors[i]);
			pActors[i] = nil;
		}
	}
	for (int i = 0; i < NUM_VEHICLES_IN_MOVIE; i++) {
		if (pVehicles[i]) {
			CWorld::Remove(pVehicles[i]);
			delete pVehicles[i];
			pVehicles[i] = nil;
		}
	}
	for (int i = 0; i < NUM_COMMANDS_IN_MOVIE; i++) {
		Movie[i].m_nCommandId = MOVIE_DO_NOTHING;
		Movie[i].m_vecPosition = CVector(0.0f, 0.0f, 0.0f);
		Movie[i].m_vecCamera = CVector(0.0f, 0.0f, 0.0f);
		Movie[i].m_nActorId = -1;
		Movie[i].m_nActor2Id = -1;
		Movie[i].m_nVehicleId = -1;
		Movie[i].m_nModelIndex = 0;
	}
	m_vecGotoPosition = CVector(0.0f, 0.0f, 0.0f);
	m_bDrawGotoArrow = false;
}

void CSceneEdit::Update(void)
{
	if (!m_bEditOn)
		return;
	if (m_bRecording)
		ProcessCommand();
	else {
		if (m_bCameraFollowActor && m_nActor != -1) {
			if (pActors[m_nActor]->bInVehicle)
				TheCamera.TakeControl(pActors[m_nActor]->m_pMyVehicle, CCam::MODE_BEHINDCAR, JUMP_CUT, CAMCONTROL_SCRIPT);
			else
				TheCamera.TakeControl(pActors[m_nActor], CCam::MODE_FOLLOWPED, JUMP_CUT, CAMCONTROL_SCRIPT);
		}
		PlayBack();
	}
}

void CSceneEdit::Draw(void)
{
	char str[200];
	wchar wstr[200];
	if (TheCamera.m_WideScreenOn)
		return;
	CFont::SetPropOff();
	CFont::SetBackgroundOff();
	CFont::SetScale(SCREEN_SCALE_X(0.8f), SCREEN_SCALE_Y(1.35f));
	CFont::SetCentreOn();
	CFont::SetRightJustifyOn();
	CFont::SetRightJustifyWrap(0.0f);
	CFont::SetBackGroundOnlyTextOff();
	CFont::SetFontStyle(FONT_HEADING);
	CFont::SetPropOff();
	sprintf(str, "Action");
	AsciiToUnicode(str, wstr);
	CFont::SetColor(CRGBA(0, 0, 0, 0));
	CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(ACTION_MESSAGE_X_RIGHT + SHADOW_OFFSET), SCREEN_SCALE_Y(ACTION_MESSAGE_Y + SHADOW_OFFSET), wstr);
	CFont::SetColor(CRGBA(193, 164, 120, 255));
	CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(ACTION_MESSAGE_X_RIGHT), SCREEN_SCALE_Y(ACTION_MESSAGE_Y), wstr);
	sprintf(str, "Selected");
	AsciiToUnicode(str, wstr);
	CFont::SetColor(CRGBA(0, 0, 0, 0));
	CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(SELECTED_MESSAGE_X_RIGHT + SHADOW_OFFSET), SCREEN_SCALE_Y(SELECTED_MESSAGE_Y + SHADOW_OFFSET), wstr);
	CFont::SetColor(CRGBA(193, 164, 120, 255));
	CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(SELECTED_MESSAGE_X_RIGHT), SCREEN_SCALE_Y(SELECTED_MESSAGE_Y), wstr);
	CFont::SetCentreOff();
	CFont::SetScale(SCREEN_SCALE_X(0.7f), SCREEN_SCALE_Y(0.7f));
	CFont::SetFontStyle(FONT_HEADING);
	CFont::SetColor(CRGBA(0, 0, 0, 0));
	for (int i = 0; i < NUM_COMMANDS_TO_DRAW; i++) {
		int16 nCommandDrawn = m_nCurrentCommand + i - NUM_COMMANDS_TO_DRAW / 2;
		if (nCommandDrawn >= MOVIE_TOTAL_COMMANDS)
			nCommandDrawn -= (MOVIE_TOTAL_COMMANDS - 1);
		if (nCommandDrawn <= MOVIE_DO_NOTHING)
			nCommandDrawn += (MOVIE_TOTAL_COMMANDS - 1);
		sprintf(str, pCommandStrings[nCommandDrawn]);
		AsciiToUnicode(str, wstr);
		CFont::SetColor(CRGBA(0, 0, 0, 0));
		CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(COMMAND_NAME_X_RIGHT + SHADOW_OFFSET), SCREEN_SCALE_Y(COMMAND_NAME_Y + SHADOW_OFFSET + i * COMMAND_NAME_HEIGHT), wstr);
		if (nCommandDrawn == m_nCurrentCommand)
			CFont::SetColor(CRGBA(156, 91, 40, 255));
		else
			CFont::SetColor(CRGBA(193, 164, 120, 255));
		CFont::PrintString(SCREEN_SCALE_FROM_RIGHT(COMMAND_NAME_X_RIGHT), SCREEN_SCALE_Y(COMMAND_NAME_Y + i * COMMAND_NAME_HEIGHT), wstr);
	}
}

void CSceneEdit::ProcessCommand(void)
{
	if (!m_bCommandActive)
		return;
	switch (m_nCurrentCommand) {
	case MOVIE_DO_NOTHING:
		m_bCommandActive = false;
		break;
	}
}

void CSceneEdit::PlayBack(void)
{

}

void CSceneEdit::ClearForNewCommand(void)
{

}
void CSceneEdit::SelectActor(void)
{

}

void CSceneEdit::SelectActor2(void)
{

}

void CSceneEdit::SelectVehicle(void)
{

}

void CSceneEdit::SelectWeapon(void)
{

}