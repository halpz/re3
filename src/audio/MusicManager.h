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

class cMusicManager
{
public:
	bool8 m_bIsInitialised;
	bool8 m_bDisabled;
	uint8 m_nMusicMode;
	uint8 m_nNextTrack;
	uint8 m_nPlayingTrack;
	bool8 m_bFrontendTrackFinished;
	bool8 m_bPlayInFrontend;
	bool8 m_bSetNextStation;
	uint8 m_nAnnouncement;
	bool8 m_bPreviousPlayerInCar;
	bool8 m_bPlayerInCar;
	bool8 m_bAnnouncementInProgress;
	tStreamedSample m_aTracks[TOTAL_STREAMED_SOUNDS];
	bool8 m_bResetTimers;
	uint32 m_nResetTime;
	uint32 m_nLastTrackServiceTime;
	uint32 m_nTimer;
	bool8 m_bDoTrackService;
	bool8 m_bIgnoreTimeDelay;
	bool8 m_bVerifyAmbienceTrackStartedToPlay;
	bool8 m_bRadioSetByScript;
	uint8 m_nRadioStationScript;
	int32 m_nRadioPosition;
	uint8 m_nRadioInCar;

public:
	cMusicManager();
	bool8 IsInitialised() { return m_bIsInitialised; }
	uint32 GetMusicMode() { return m_nMusicMode; }
	uint8 GetNextTrack() { return m_nNextTrack; }

	bool8 Initialise();
	void Terminate();

	void ChangeMusicMode(uint8 mode);
	void StopFrontEndTrack();

	bool8 PlayerInCar();
	void DisplayRadioStationName();

	void PlayAnnouncement(uint8);
	void PlayFrontEndTrack(uint8, bool8);
	void PreloadCutSceneMusic(uint8);
	void PlayPreloadedCutSceneMusic(void);
	void StopCutSceneMusic(void);
	uint8 GetRadioInCar(void);
	void SetRadioInCar(uint32);
	void SetRadioChannelByScript(uint8, int32);

	void ResetMusicAfterReload();

	void ResetTimers(uint32);
	void Service();
	void ServiceFrontEndMode();
	void ServiceGameMode();
	void ServiceAmbience();
	void ServiceTrack();

	bool8 UsesPoliceRadio(CVehicle *veh);
	uint32 GetTrackStartPos(uint8);

	void ComputeAmbienceVol(bool8 reset, uint8& outVolume);
	bool8 ServiceAnnouncement();

	uint8 GetCarTuning();
	uint8 GetNextCarTuning();
	bool8 ChangeRadioChannel();
};

VALIDATE_SIZE(cMusicManager, 0x95C);

extern cMusicManager MusicManager;
