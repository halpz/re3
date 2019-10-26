#pragma once

#include "audio.h"

class tMP3Sample
{
public:
	uint32 m_nLength;
	uint32 m_nPosition;
	uint32 m_nLastPosCheckTimer;
};

class cMusicManager
{
public:
	bool m_bIsInitialised;
	uint8 field_1;
	uint8 m_nMusicMode;
	uint8 m_nCurrentStreamedSound;
	uint8 m_nPreviousStreamedSound;
	uint8 field_5;
	uint8 field_6;
	uint8 field_7;
	bool m_bAnnouncement;
	bool m_bPreviousPlayerInCar;
	bool m_bPlayerInCar;
	bool m_bAnnouncementInProgress;
	tMP3Sample m_asMP3Samples[TOTAL_STREAMED_SOUNDS];
	uint8 field_2364;
	uint8 field_2365;
	uint8 field_2366;
	uint8 field_2367;
	uint32 field_2368;
	uint32 field_2372;
	uint32 field_2376;
	uint8 field_2380;
	uint8 field_2381;
	uint8 field_2382;
	bool m_bRadioSetByScript;
	uint8 m_nRadioStation;
	uint8 field_2385;
	uint8 field_2386;
	uint8 field_2387;
	uint32 m_nRadioPosition;
	bool m_bRadioInCar;
	uint8 field_2393;
	uint8 field_2394;
	uint8 field_2395;

public:
	bool IsInitialised() { return m_bIsInitialised; }
	uint32 GetMusicMode() { return m_nMusicMode; }
	uint8 GetCurrentTrack() { return m_nCurrentStreamedSound; }

	void Initialise();
	void Terminate();

	void ChangeMusicMode(int32 mode);
	void StopFrontEndTrack();

	bool PlayerInCar();
	void DisplayRadioStationName();

	void PlayAnnouncement(uint8);
	void PlayFrontEndTrack(uint8, uint8);
	void PreloadCutSceneMusic(uint8);
	void PlayPreloadedCutSceneMusic(void);
	void StopCutSceneMusic(void);
	int32 GetRadioInCar(void);
	void SetRadioInCar(uint32);
	void SetRadioChannelByScript(uint8, int32);

	void ResetMusicAfterReload();

	void ResetTimers(int32);
	void Service();
};

static_assert(sizeof(cMusicManager) == 0x95C, "cMusicManager: error");

extern cMusicManager &MusicManager;
