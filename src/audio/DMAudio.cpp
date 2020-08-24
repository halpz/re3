#include "common.h"

#include "DMAudio.h"
#include "MusicManager.h"
#include "AudioManager.h"
#include "AudioScriptObject.h"
#include "sampman.h"
#include "Text.h"
#include "crossplatform.h"

cDMAudio DMAudio;

void
cDMAudio::Initialise(void)
{
	AudioManager.Initialise();
}

void
cDMAudio::Terminate(void)
{
	AudioManager.Terminate();
}

void
cDMAudio::Service(void)
{
	AudioManager.Service();
}

int32
cDMAudio::CreateEntity(eAudioType type, void *UID)
{
	return AudioManager.CreateEntity(type, (CPhysical *)UID);
}

void
cDMAudio::DestroyEntity(int32 audioEntity)
{
	AudioManager.DestroyEntity(audioEntity);
}

void
cDMAudio::SetEntityStatus(int32 audioEntity, uint8 status)
{
	AudioManager.SetEntityStatus(audioEntity, status);
}

void
cDMAudio::PlayOneShot(int32 audioEntity, uint16 oneShot, float volume)
{
	AudioManager.PlayOneShot(audioEntity, oneShot, volume);
}

void
cDMAudio::DestroyAllGameCreatedEntities(void)
{
	AudioManager.DestroyAllGameCreatedEntities();
}

void
cDMAudio::SetMonoMode(uint8 mono)
{
	AudioManager.SetMonoMode(mono);
}

void
cDMAudio::SetEffectsMasterVolume(uint8 volume)
{
	uint8 vol = volume;
	if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
	
	AudioManager.SetEffectsMasterVolume(vol);
}

void
cDMAudio::SetMusicMasterVolume(uint8 volume)
{
	uint8 vol = volume;
	if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
	
	AudioManager.SetMusicMasterVolume(vol);
}

void
cDMAudio::SetEffectsFadeVol(uint8 volume)
{
	uint8 vol = volume;
	if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
	
	AudioManager.SetEffectsFadeVol(vol);
}

void
cDMAudio::SetMusicFadeVol(uint8 volume)
{
	uint8 vol = volume;
	if ( vol > MAX_VOLUME ) vol = MAX_VOLUME;
	
	AudioManager.SetMusicFadeVol(vol);
}

uint8
cDMAudio::GetNum3DProvidersAvailable(void)
{
	return AudioManager.GetNum3DProvidersAvailable();
}

char *
cDMAudio::Get3DProviderName(uint8 id)
{
	return AudioManager.Get3DProviderName(id);
}

// TODO(Miami): Content of this moved to cSampleManager or cAudioManager
int8 cDMAudio::AutoDetect3DProviders(void)
{
	if (!AudioManager.IsAudioInitialised())
		return -1;

	int eax = -1, eax2 = -1, eax3 = -1, ds3dh = -1, ds3ds = -1;

	for ( int32 i = 0; i < GetNum3DProvidersAvailable(); i++ )
	{
		char *providername = Get3DProviderName(i);
		strupr(providername);

#if defined(AUDIO_OAL)
		if (!strcmp(providername, "OPENAL SOFT")) {
			SetCurrent3DProvider(i);
			if (GetCurrent3DProviderIndex() == i)
				return i;
		}
#else
		if (!strcmp(providername, "CREATIVE LABS EAX 3 (TM)")) {
			SetCurrent3DProvider(i);
			if (GetCurrent3DProviderIndex() == i) {
				eax3 = i;
			}
		}

		if (!strcmp(providername, "CREATIVE LABS EAX 2 (TM)")) {
			SetCurrent3DProvider(i);
			if (GetCurrent3DProviderIndex() == i)
				eax2 = i;
		}

		if (!strcmp(providername, "CREATIVE LABS EAX (TM)")) {
			SetCurrent3DProvider(i);
			if (GetCurrent3DProviderIndex() == i)
				eax = i;
		}

		if (!strcmp(providername, "DIRECTSOUND3D HARDWARE SUPPORT")) {
			SetCurrent3DProvider(i);
			if (GetCurrent3DProviderIndex() == i)
				ds3dh = i;
		}

		if (!strcmp(providername, "DIRECTSOUND3D SOFTWARE EMULATION")) {
			SetCurrent3DProvider(i);
			if (GetCurrent3DProviderIndex() == i)
				ds3ds = i;
		}
#endif
	}

	if (eax3 != -1)
		return eax3;
	if (eax2 != -1)
		return eax2;
	if (eax != -1)
		return eax;
	if (ds3dh != -1)
		return ds3dh;
	if (ds3ds != -1)
		return ds3ds;
	return -1;
}

int8
cDMAudio::GetCurrent3DProviderIndex(void)
{
	return AudioManager.GetCurrent3DProviderIndex();
}

int8
cDMAudio::SetCurrent3DProvider(uint8 which)
{
	return AudioManager.SetCurrent3DProvider(which);
}

void
cDMAudio::SetSpeakerConfig(int32 config)
{
	AudioManager.SetSpeakerConfig(config);
}

bool
cDMAudio::IsMP3RadioChannelAvailable(void)
{
	return AudioManager.IsMP3RadioChannelAvailable();
}

void
cDMAudio::ReleaseDigitalHandle(void)
{
	AudioManager.ReleaseDigitalHandle();
}

void
cDMAudio::ReacquireDigitalHandle(void)
{
	AudioManager.ReacquireDigitalHandle();
}

void
cDMAudio::SetDynamicAcousticModelingStatus(uint8 status)
{
	AudioManager.SetDynamicAcousticModelingStatus(status);
}

bool
cDMAudio::CheckForAnAudioFileOnCD(void)
{
	return AudioManager.CheckForAnAudioFileOnCD();
}

char
cDMAudio::GetCDAudioDriveLetter(void)
{
	return AudioManager.GetCDAudioDriveLetter();
}

bool
cDMAudio::IsAudioInitialised(void)
{
	return AudioManager.IsAudioInitialised();
}

void
cDMAudio::ReportCrime(eCrimeType crime, const CVector &pos)
{
	AudioManager.ReportCrime(crime, &pos);
}

int32
cDMAudio::CreateLoopingScriptObject(cAudioScriptObject *scriptObject)
{
	int32 audioEntity = AudioManager.CreateEntity(AUDIOTYPE_SCRIPTOBJECT, scriptObject);

	if ( AEHANDLE_IS_OK(audioEntity) )
		AudioManager.SetEntityStatus(audioEntity, true);
	
	return audioEntity;
}

void
cDMAudio::DestroyLoopingScriptObject(int32 audioEntity)
{
	AudioManager.DestroyEntity(audioEntity);
}

void
cDMAudio::CreateOneShotScriptObject(cAudioScriptObject *scriptObject)
{
	int32 audioEntity = AudioManager.CreateEntity(AUDIOTYPE_SCRIPTOBJECT, scriptObject);

	if ( AEHANDLE_IS_OK(audioEntity) )
	{
		AudioManager.SetEntityStatus(audioEntity, true);
		AudioManager.PlayOneShot(audioEntity, scriptObject->AudioId, 0.0f);
	}
}

void
cDMAudio::PlaySuspectLastSeen(float x, float y, float z)
{
	AudioManager.PlaySuspectLastSeen(x, y, z);
}

void
cDMAudio::ReportCollision(CEntity *entityA, CEntity *entityB, uint8 surfaceTypeA, uint8 surfaceTypeB, float collisionPower, float velocity)
{
	AudioManager.ReportCollision(entityA, entityB, surfaceTypeA, surfaceTypeB, collisionPower, velocity);
}

void
cDMAudio::PlayFrontEndSound(uint16 frontend, uint32 volume)
{
	AudioManager.PlayOneShot(AudioManager.m_nFrontEndEntity, frontend, (float)volume);
}

void
cDMAudio::PlayRadioAnnouncement(uint8 announcement)
{
	MusicManager.PlayAnnouncement(announcement);
}

void
cDMAudio::PlayFrontEndTrack(uint8 track, uint8 frontendFlag)
{
	MusicManager.PlayFrontEndTrack(track, frontendFlag);
}

void
cDMAudio::StopFrontEndTrack(void)
{
	MusicManager.StopFrontEndTrack();
}

void
cDMAudio::ResetTimers(uint32 time)
{
	AudioManager.ResetTimers(time);
}

void
cDMAudio::ChangeMusicMode(uint8 mode)
{
	MusicManager.ChangeMusicMode(mode);
}

void
cDMAudio::PreloadCutSceneMusic(uint8 track)
{
	MusicManager.PreloadCutSceneMusic(track);
}

void
cDMAudio::PlayPreloadedCutSceneMusic(void)
{
	MusicManager.PlayPreloadedCutSceneMusic();
}

void
cDMAudio::StopCutSceneMusic(void)
{
	MusicManager.StopCutSceneMusic();
}

void
cDMAudio::PreloadMissionAudio(uint8 slot, Const char *missionAudio)
{
	AudioManager.PreloadMissionAudio(slot, missionAudio);
}

uint8
cDMAudio::GetMissionAudioLoadingStatus(uint8 slot)
{
	return AudioManager.GetMissionAudioLoadingStatus(slot);
}

void
cDMAudio::SetMissionAudioLocation(uint8 slot, float x, float y, float z)
{
	AudioManager.SetMissionAudioLocation(slot, x, y, z);
}

void
cDMAudio::PlayLoadedMissionAudio(uint8 slot)
{
	AudioManager.PlayLoadedMissionAudio(slot);
}

bool
cDMAudio::IsMissionAudioSampleFinished(uint8 slot)
{
	return AudioManager.IsMissionAudioSampleFinished(slot);
}

void
cDMAudio::ClearMissionAudio(uint8 slot)
{
	AudioManager.ClearMissionAudio(slot);
}

uint8
cDMAudio::GetRadioInCar(void)
{
	return MusicManager.GetRadioInCar();
}

void
cDMAudio::SetRadioInCar(uint32 radio)
{
	MusicManager.SetRadioInCar(radio);
}

void
cDMAudio::SetRadioChannel(int8 radio, int32 pos)
{
	MusicManager.SetRadioChannelByScript(radio, pos);
}
