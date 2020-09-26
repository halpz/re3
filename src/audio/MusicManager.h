#pragma once

#include "audio_enums.h"

class tStreamedSample
{
public:
	uint32 m_nLength;
	uint32 m_nPosition;
	uint32 m_nLastPosCheckTimer;
};

class CVehicle;
class CPed;

class cMusicManager
{
public:
	bool m_bIsInitialised;
	bool m_bDisabled;
	bool field_2;
	uint8 m_nVolumeLatency;
	uint8 m_nCurrentVolume;
	uint8 m_nMaxVolume;
	uint32 m_nAnnouncement;
	bool m_bAnnouncementInProgress;
	tStreamedSample m_aTracks[TOTAL_STREAMED_SOUNDS];
	bool m_bResetTimers;
	uint32 m_nResetTime;
	bool m_bRadioSetByScript;
	uint8 m_nRadioStation;
	uint32 m_nRadioPosition;
	uint32 m_nRadioInCar;
	uint32 m_nFrontendTrack;
	uint32 m_nPlayingTrack;
	uint8 m_nUpcomingMusicMode;
	uint8 m_nMusicMode;
	bool field_398E;
	bool field_398F;
	uint32 m_nStreamedTrack;
	bool field_3994;
	bool field_3995;
	bool field_3996;
	bool field_3997;
	int8 nFramesSinceCutsceneEnded;
	bool field_3999;
	bool field_399A;
	uint8 m_nMusicModeToBeSet;
	bool field_399C;
	float aListenTimeArray[NUM_RADIOS];
	float m_nLastTrackServiceTime;

public:
	cMusicManager();
	bool IsInitialised() { return m_bIsInitialised; }
	uint8 GetMusicMode() { return m_nMusicMode; }
	uint32 GetCurrentTrack() { return m_nPlayingTrack; }

	void ResetMusicAfterReload();
	void SetStartingTrackPositions(uint8 isNewGameTimer);
	bool Initialise();
	void Terminate();

	void ChangeMusicMode(uint8 mode);
	void StopFrontEndTrack();

	bool PlayerInCar();
	void DisplayRadioStationName();

	void PlayAnnouncement(uint32);
	void PlayFrontEndTrack(uint32, uint8);
	void PreloadCutSceneMusic(uint32);
	void PlayPreloadedCutSceneMusic(void);
	void StopCutSceneMusic(void);
	uint32 GetRadioInCar(void);
	void SetRadioInCar(uint32);
	void SetRadioChannelByScript(uint32, int32);

	void ResetTimers(int32);
	void Service();
	void ServiceFrontEndMode();
	void ServiceGameMode();
	void ServiceAmbience();
	void ServiceTrack(CVehicle *veh, CPed *ped);

	bool UsesPoliceRadio(CVehicle *veh);
	bool UsesTaxiRadio(CVehicle *veh);
	uint32 GetTrackStartPos(uint32 track);

	void ComputeAmbienceVol(uint8 reset, uint8& outVolume);
	bool ServiceAnnouncement();

	uint32 GetCarTuning();
	uint32 GetNextCarTuning();
	bool ChangeRadioChannel();
	void RecordRadioStats();
	void SetUpCorrectAmbienceTrack();
	float *GetListenTimeArray();
	uint32 GetRadioPosition(uint32 station);
	uint32 GetFavouriteRadioStation();
	void SetMalibuClubTrackPos(uint8 pos);
	void SetStripClubTrackPos(uint8 pos);
	bool CheckForMusicInterruptions();

	void Enable();
	void Disable();
};

VALIDATE_SIZE(cMusicManager, 0x95C);

extern cMusicManager MusicManager;
extern bool g_bAnnouncementReadPosAlready; // we have a symbol of this so it was declared in .h
float GetHeightScale();
