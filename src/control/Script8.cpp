#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "DMAudio.h"
#if ((defined GTAVC_JP_PATCH || defined SUPPORT_JAPANESE_SCRIPT) && defined MORE_LANGUAGES)
#include "Frontend.h"
#endif
#include "GameLogic.h"
#include "Garages.h"
#ifdef MISSION_REPLAY
#include "GenericGameStorage.h"
#endif
#if (defined GTA_PC && !defined GTAVC_JP_PATCH || defined GTA_XBOX || defined SUPPORT_XBOX_SCRIPT || defined GTA_MOBILE || defined SUPPORT_MOBILE_SCRIPT)
#include "General.h"
#include "maths.h"
#endif
#include "Hud.h"
#include "Pad.h"
#include "PedAttractor.h"
#include "Population.h"
#include "Pools.h"
#include "RpAnimBlend.h"
#include "Stats.h"
#include "VisibilityPlugins.h"
#include "Wanted.h"
#include "WaterLevel.h"
#include "World.h"
#include "Zones.h"

int8 CRunningScript::ProcessCommands1400To1499(int32 command)
{
	switch (command) {
	case COMMAND_REGISTER_VIGILANTE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelVigilanteMission(ScriptParams[0]);
		return 0;
	case COMMAND_CLEAR_ALL_CHAR_ANIMS:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		if (!pPed->bInVehicle) {
			pPed->m_pVehicleAnim = nil;
			pPed->RestartNonPartialAnims();
			RpAnimBlendClumpRemoveAllAssociations(pPed->GetClump());
			pPed->SetPedState(PED_IDLE);
			pPed->SetMoveState(PEDMOVE_STILL);
			pPed->m_nLastPedState = PED_NONE;
			pPed->ClearAimFlag();
			pPed->ClearLookFlag();
			pPed->bIsPointingGunAt = false;
			if (pPed->IsPlayer())
				((CPlayerPed*)pPed)->m_fMoveSpeed = 0.0f;
			else
				pPed->m_nStoredMoveState = PEDMOVE_STILL;
			CAnimManager::AddAnimation(pPed->GetClump(), pPed->m_animGroup, ANIM_STD_IDLE);
			pPed->bIsPedDieAnimPlaying = false;
		}
		return 0;
	}
	case COMMAND_SET_MAXIMUM_NUMBER_OF_CARS_IN_GARAGE:
		CollectParameters(&m_nIp, 2);
		CGarages::SetMaxNumStoredCarsForGarage(ScriptParams[0], ScriptParams[1]);
		return 0;
	case COMMAND_WANTED_STARS_ARE_FLASHING:
	{
		CWanted* pWanted = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pWanted;
		UpdateCompareFlag(pWanted->m_nMinWantedLevel - pWanted->GetWantedLevel() > 0);
		return 0;
	}
	case COMMAND_SET_ALLOW_HURRICANES:
		CollectParameters(&m_nIp, 1);
		CStats::NoMoreHurricanes = ScriptParams[0];
		return 0;
	case COMMAND_PLAY_ANNOUNCEMENT:
	{
		CollectParameters(&m_nIp, 1);
		DMAudio.PlayRadioAnnouncement(ScriptParams[0] + STREAMED_SOUND_ANNOUNCE_BRIDGE_CLOSED);
		return 0;
	}
	case COMMAND_SET_PLAYER_IS_IN_STADIUM:
	{
		CollectParameters(&m_nIp, 1);
		CTheScripts::bPlayerIsInTheStatium = ScriptParams[0];
		return 0;
	}
	case COMMAND_GET_BUS_FARES_COLLECTED_BY_PLAYER:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[ScriptParams[0]];
		ScriptParams[0] = pPlayerInfo->m_pPed->m_nLastBusFareCollected;
		pPlayerInfo->m_pPed->m_nLastBusFareCollected = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_SET_CHAR_OBJ_BUY_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[1]);
		script_assert(pVehicle);
		ScriptParams[0] = 0;
		if (pPed->m_objective == OBJECTIVE_NONE && !pPed->bHasAlreadyUsedAttractor) {
			C2dEffect* pEffect = (C2dEffect*)GetPedAttractorManager()->GetEffectForIceCreamVan(pVehicle, pPed->GetPosition()); // has to be casted, because inner methods are const
			if (pEffect) {
				CVector pos;
				CPedAttractorManager::ComputeEffectPos(pEffect, pVehicle->GetMatrix(), pos);
				if ((pPed->GetPosition() - pos).MagnitudeSqr() < SQR(20.0f)) {
					if (GetPedAttractorManager()->HasEmptySlot(pEffect) && GetPedAttractorManager()->IsApproachable(pEffect, pVehicle->GetMatrix(), 0, pPed)) {
						if (GetPedAttractorManager()->RegisterPedWithAttractor(pPed, pEffect, pVehicle->GetMatrix()))
							ScriptParams[0] = 1;
					}
				}
			}
		}
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_DISPLAY_RADAR:
		CollectParameters(&m_nIp, 1);
		CHud::m_HideRadar = ScriptParams[0] == 0;
		return 0;
	case COMMAND_REGISTER_BEST_POSITION:
		CollectParameters(&m_nIp, 2);
		CStats::RegisterBestPosition(ScriptParams[0], ScriptParams[1]);
		return 0;
	case COMMAND_IS_PLAYER_IN_INFO_ZONE:
	{
		CollectParameters(&m_nIp, 1);
		CPlayerInfo* pPlayerInfo = &CWorld::Players[ScriptParams[0]];
		char key[KEY_LENGTH_IN_SCRIPT];
		memset(key, 0, KEY_LENGTH_IN_SCRIPT);
		CTheScripts::ReadTextLabelFromScript(&m_nIp, key);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		CVector pos = pPlayerInfo->GetPos();
		CZone* infoZone = CTheZones::FindInformationZoneForPosition(&pos);
		UpdateCompareFlag(strncmp(key, infoZone->name, 8) == 0); // original code doesn't seem to be using strncmp in here and compare 2 ints instead
		return 0;
	}
	case COMMAND_CLEAR_CHAR_ICE_CREAM_PURCHASE:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		if (pPed->m_attractor)
			GetPedAttractorManager()->DeRegisterPed(pPed, pPed->m_attractor);
		return 0;
	}
	case COMMAND_IS_IN_CAR_FIRE_BUTTON_PRESSED:
		UpdateCompareFlag(CPad::GetPad(0)->GetCarGunFired());
		return 0;
	case COMMAND_HAS_CHAR_ATTEMPTED_ATTRACTOR:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		UpdateCompareFlag(pPed->bHasAlreadyUsedAttractor);
		return 0;
	}
	case COMMAND_SET_LOAD_COLLISION_FOR_CAR_FLAG:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[0]);
		script_assert(pVehicle);
		if (ScriptParams[1]) {
			pVehicle->bDontLoadCollision = false;
			if (m_bMissionFlag) {
				CWorld::Remove(pVehicle);
				pVehicle->bIsStaticWaitingForCollision = true;
				CWorld::Add(pVehicle);
			}
		}
		else {
			pVehicle->bDontLoadCollision = true;
			if (pVehicle->bIsStaticWaitingForCollision) {
				pVehicle->bIsStaticWaitingForCollision = false;
				if (!pVehicle->GetIsStatic())
					pVehicle->AddToMovingList();
			}
		}
		return 0;
	}
	case COMMAND_SET_LOAD_COLLISION_FOR_CHAR_FLAG:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		if (ScriptParams[1]) {
			pPed->bDontLoadCollision = false;
			if (m_bMissionFlag) {
				CWorld::Remove(pPed);
				pPed->bIsStaticWaitingForCollision = true;
				CWorld::Add(pPed);
			}
		}
		else {
			pPed->bDontLoadCollision = true;
			if (pPed->bIsStaticWaitingForCollision) {
				pPed->bIsStaticWaitingForCollision = false;
				if (!pPed->GetIsStatic())
					pPed->AddToMovingList();
			}
		}
		return 0;
	}
	//case COMMAND_SET_LOAD_COLLISION_FOR_OBJECT_FLAG:
	case COMMAND_ADD_BIG_GUN_FLASH:
	{
		CollectParameters(&m_nIp, 6);
		CWeapon::AddGunFlashBigGuns(*(CVector*)&ScriptParams[0], *(CVector*)&ScriptParams[3]);
		return 0;
	}
	case COMMAND_HAS_CHAR_BOUGHT_ICE_CREAM:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		UpdateCompareFlag(pPed->bBoughtIceCream);
		return 0;
	}
	case COMMAND_GET_PROGRESS_PERCENTAGE:
		*(float*)&ScriptParams[0] = CStats::GetPercentageProgress();
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_SHORTCUT_PICKUP_POINT:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutPointAfterDeath(*(CVector*)&ScriptParams[0], *(float*)&ScriptParams[3]);
		return 0;
	}
	case COMMAND_SET_SHORTCUT_DROPOFF_POINT_FOR_MISSION:
	{
		CollectParameters(&m_nIp, 4);
		CGameLogic::AddShortCutDropOffPointForMission(*(CVector*)&ScriptParams[0], *(float*)&ScriptParams[3]);
		return 0;
	}
	case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_AREA:
	{
		CollectParameters(&m_nIp, 7);
		int ped_handle = -1;
		CVector pos = FindPlayerCoors();
		float x1 = *(float*)&ScriptParams[0];
		float y1 = *(float*)&ScriptParams[1];
		float x2 = *(float*)&ScriptParams[2];
		float y2 = *(float*)&ScriptParams[3];
		int i = CPools::GetPedPool()->GetSize();
		while (--i && ped_handle == -1) {
			CPed* pPed = CPools::GetPedPool()->GetSlot(i);
			if (!pPed)
				continue;
			if (CTheScripts::LastRandomPedId == CPools::GetPedPool()->GetIndex(pPed))
				continue;
			if (pPed->CharCreatedBy != RANDOM_CHAR)
				continue;
			if (!pPed->IsPedInControl())
				continue;
			if (pPed->bRemoveFromWorld)
				continue;
			if (pPed->bFadeOut)
				continue;
			if (pPed->m_nWaitState != WAITSTATE_FALSE)
				continue;
			if (pPed->bHasAlreadyUsedAttractor)
				continue;
			if (pPed->m_attractor)
				continue;
			if (!ThisIsAValidRandomPed(pPed->m_nPedType, ScriptParams[4], ScriptParams[5], ScriptParams[6]))
				continue;
			if (pPed->bIsLeader || pPed->m_leader)
				continue;
			if (!pPed->IsWithinArea(x1, y1, x2, y2))
				continue;
			if (pos.z - PED_FIND_Z_OFFSET > pPed->GetPosition().z)
				continue;
			if (pos.z + PED_FIND_Z_OFFSET < pPed->GetPosition().z)
				continue;
			ped_handle = CPools::GetPedPool()->GetIndex(pPed);
			CTheScripts::LastRandomPedId = ped_handle;
			pPed->CharCreatedBy = MISSION_CHAR;
			pPed->bRespondsToThreats = false;
			++CPopulation::ms_nTotalMissionPeds;
			if (m_bIsMissionScript)
				CTheScripts::MissionCleanUp.AddEntityToList(ped_handle, CLEANUP_CHAR);
		}
		ScriptParams[0] = ped_handle;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	//case COMMAND_GET_RANDOM_ICE_CREAM_CUSTOMER_IN_ZONE:
	case COMMAND_UNLOCK_ALL_CAR_DOORS_IN_AREA:
	{
		CollectParameters(&m_nIp, 4);
		uint32 i = CPools::GetVehiclePool()->GetSize();
		float infX = *(float*)&ScriptParams[0];
		float infY = *(float*)&ScriptParams[1];
		float supX = *(float*)&ScriptParams[2];
		float supY = *(float*)&ScriptParams[3];
		while (i--) {
			CVehicle* pVehicle = CPools::GetVehiclePool()->GetSlot(i);
			if (!pVehicle)
				continue;
			if (pVehicle->IsWithinArea(infX, infY, supX, supY))
				pVehicle->m_nDoorLock = CARLOCK_UNLOCKED;
		}
		return 0;
	}
	case COMMAND_SET_GANG_ATTACK_PLAYER_WITH_COPS:
		CollectParameters(&m_nIp, 2);
		CGangs::SetWillAttackPlayerWithCops((ePedType)((int)PEDTYPE_GANG1 + ScriptParams[0]), !!ScriptParams[1]);
		return 0;
	case COMMAND_SET_CHAR_FRIGHTENED_IN_JACKED_CAR:
	{
		CollectParameters(&m_nIp, 2);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		pPed->bHeldHostageInCar = ScriptParams[1];
		return 0;
	}
	case COMMAND_SET_VEHICLE_TO_FADE_IN:
	{
		CollectParameters(&m_nIp, 2);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[0]);
		script_assert(pVehicle);
		CVisibilityPlugins::SetClumpAlpha(pVehicle->GetClump(), ScriptParams[1]);
		return 0;
	}
	case COMMAND_REGISTER_ODDJOB_MISSION_PASSED:
		++CStats::MissionsPassed;
		CStats::CheckPointReachedSuccessfully();
		CTheScripts::LastMissionPassedTime = CTimer::GetTimeInMilliseconds();
		CGameLogic::RemoveShortCutDropOffPointForMission();
		return 0;
	case COMMAND_IS_PLAYER_IN_SHORTCUT_TAXI:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CWorld::Players[ScriptParams[0]].m_pPed;
		script_assert(pPed);
		UpdateCompareFlag(pPed->bInVehicle && pPed->m_pMyVehicle && pPed->m_pMyVehicle == CGameLogic::pShortCutTaxi);
		return 0;
	}
	case COMMAND_IS_CHAR_DUCKING:
	{
		CollectParameters(&m_nIp, 1);
		CPed* pPed = CPools::GetPedPool()->GetAt(ScriptParams[0]);
		script_assert(pPed);
		UpdateCompareFlag(RpAnimBlendClumpGetAssociation(pPed->GetClump(), ANIM_STD_DUCK_DOWN) != nil);
		return 0;
	}
	case COMMAND_CREATE_DUST_EFFECT_FOR_CUTSCENE_HELI:
	{
		CollectParameters(&m_nIp, 3);
		CObject* pHeli = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		bool found = false;
		float waterLevel = -1000.0f;
		CVector pos = pHeli->GetPosition();
		float radius = *(float*)&ScriptParams[1];
		float ground = CWorld::FindGroundZFor3DCoord(pos.x, pos.y, pos.z, &found);
		if (!CWaterLevel::GetWaterLevel(pos.x, pos.y, pos.z, &waterLevel, false))
			waterLevel = 0.0f;
		if (waterLevel > ground)
			ground = waterLevel;
		if (ScriptParams[2] > 8)
			ScriptParams[2] = 8;
		CVehicle::HeliDustGenerate(pHeli, (pos.z - ground - 1.0f - radius) * 0.3 + radius, ground, ScriptParams[2]);
		return 0;
	}
	case COMMAND_REGISTER_FIRE_LEVEL:
		CollectParameters(&m_nIp, 1);
		CStats::RegisterLevelFireMission(ScriptParams[0]);
		return 0;
	case COMMAND_IS_AUSTRALIAN_GAME:
		UpdateCompareFlag(false); // should we make some check?
		return 0;
	case COMMAND_DISARM_CAR_BOMB:
	{
		CollectParameters(&m_nIp, 1);
		CVehicle* pVehicle = CPools::GetVehiclePool()->GetAt(ScriptParams[0]);
		if (pVehicle->m_bombType != CARBOMB_NONE) {
			pVehicle->m_bombType = CARBOMB_NONE;
			pVehicle->m_pBombRigger = nil;
		}
		return 0;
	}
#if (defined GTAVC_JP_PATCH || defined SUPPORT_JAPANESE_SCRIPT)
	case COMMAND_IS_JAPANESE_GAME:
#ifdef MORE_LANGUAGES
		UpdateCompareFlag(FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_JAPANESE);
#elif (defined GTAVC_JP_PATCH)
		UpdateCompareFlag(true);
#else
		UpdateCompareFlag(false);
#endif
		return 0;
#elif (!defined GTA_PS2)
	case COMMAND_SET_ONSCREEN_COUNTER_FLASH_WHEN_FIRST_DISPLAYED:
	{
		script_assert(CTheScripts::ScriptSpace[m_nIp++] == ARGUMENT_GLOBALVAR);
		uint16 var = CTheScripts::Read2BytesFromScript(&m_nIp);
		CollectParameters(&m_nIp, 1);
		//CUserDisplay::OnscnTimer.SetCounterFlashWhenFirstDisplayed(var, ScriptParams[0]);
		return 0;
	}
#endif
#if (defined GTA_PC && !defined GTAVC_JP_PATCH || defined GTA_XBOX || defined SUPPORT_XBOX_SCRIPT || defined GTA_MOBILE || defined SUPPORT_MOBILE_SCRIPT)
	case COMMAND_SHUFFLE_CARD_DECKS:
	{
		CollectParameters(&m_nIp, 1);
		script_assert(ScriptParams[0] >= 0 && ScriptParams[0] <= 6);
		for (int i = 0; i < CARDS_IN_STACK; i++)
			CTheScripts::CardStack[i] = 0;
		int16 seq[CARDS_IN_STACK];
		for (int i = 0; i < MAX_DECKS * CARDS_IN_DECK; i++)
			seq[i] = i;
		int cards_left = CARDS_IN_DECK * ScriptParams[0];
		for (int k = 1; k < CARDS_IN_DECK + 1; k++) {
			for (int deck = 0; deck < ScriptParams[0]; deck++) {
				int index = CGeneral::GetRandomNumberInRange(0, cards_left);
				CTheScripts::CardStack[seq[index]] = k;
				for (int l = index; l < cards_left; l++) {
					if (l + 1 < CARDS_IN_STACK)
						seq[l] = seq[l + 1];
					else
						seq[l] = 0;
				}
				--cards_left;
			}
		}
		CTheScripts::CardStackPosition = 0;
		return 0;
	}
	case COMMAND_FETCH_NEXT_CARD:
	{
		if (CTheScripts::CardStack[CTheScripts::CardStackPosition] == 0)
			CTheScripts::CardStackPosition = 0;
		ScriptParams[0] = CTheScripts::CardStack[CTheScripts::CardStackPosition++];
		if (CTheScripts::CardStackPosition == CARDS_IN_DECK * MAX_DECKS)
			CTheScripts::CardStackPosition = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_GET_OBJECT_VELOCITY:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		*(CVector*)&ScriptParams[0] = GAME_SPEED_TO_METERS_PER_SECOND * pObject->GetMoveSpeed();
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_IS_DEBUG_CAMERA_ON:
		UpdateCompareFlag(TheCamera.WorldViewerBeingUsed);
		return 0;
	case COMMAND_ADD_TO_OBJECT_ROTATION_VELOCITY:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		CVector newSpeed = pObject->GetTurnSpeed() + *(CVector*)&ScriptParams[1] / GAME_SPEED_TO_METERS_PER_SECOND;
		if (pObject->bIsStatic) {
			pObject->SetIsStatic(false);
			pObject->AddToMovingList();
		}
		pObject->SetTurnSpeed(newSpeed.x, newSpeed.y, newSpeed.z);
		return 0;
	}
	case COMMAND_SET_OBJECT_ROTATION_VELOCITY:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		CVector newSpeed = *(CVector*)&ScriptParams[1] / GAME_SPEED_TO_METERS_PER_SECOND;
		if (pObject->bIsStatic) {
			pObject->SetIsStatic(false);
			pObject->AddToMovingList();
		}
		pObject->SetTurnSpeed(newSpeed.x, newSpeed.y, newSpeed.z);
		return 0;
	}
	case COMMAND_IS_OBJECT_STATIC:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		UpdateCompareFlag(pObject->GetIsStatic());
		return 0;
	}
	case COMMAND_GET_ANGLE_BETWEEN_2D_VECTORS:
	{
		CollectParameters(&m_nIp, 4);
		CVector2D v1 = *(CVector2D*)&ScriptParams[0];
		CVector2D v2 = *(CVector2D*)&ScriptParams[2];
		float c = DotProduct2D(v1, v2) / (v1.Magnitude() * v2.Magnitude());
#ifdef FIX_BUGS // command is a SA leftover where it was fixed to this
		*(float*)&ScriptParams[0] = RADTODEG(Acos(c));
#else
		*(float*)&ScriptParams[0] = Acos(c);
#endif
		return 0;
	}
	case COMMAND_DO_2D_RECTANGLES_COLLIDE:
	{
		CollectParameters(&m_nIp, 8);
		float infX1 = *(float*)&ScriptParams[0] - *(float*)&ScriptParams[2] * 0.5; // NB: not float
		float supX1 = *(float*)&ScriptParams[0] + *(float*)&ScriptParams[2] * 0.5;
		float infX2 = *(float*)&ScriptParams[4] - *(float*)&ScriptParams[6] * 0.5;
		float supX2 = *(float*)&ScriptParams[4] + *(float*)&ScriptParams[6] * 0.5;
		float infY1 = *(float*)&ScriptParams[1] - *(float*)&ScriptParams[3] * 0.5;
		float supY1 = *(float*)&ScriptParams[1] + *(float*)&ScriptParams[3] * 0.5;
		float infY2 = *(float*)&ScriptParams[5] - *(float*)&ScriptParams[7] * 0.5;
		float supY2 = *(float*)&ScriptParams[5] + *(float*)&ScriptParams[7] * 0.5;
		bool collide = true;
		if (infY2 > supY1)
			collide = false;
		if (infY1 > supY2)
			collide = false;
		if (infX2 > supX1)
			collide = false;
		if (infX1 > supX2)
			collide = false;
		UpdateCompareFlag(collide);
		return 0;
	}
	case COMMAND_GET_OBJECT_ROTATION_VELOCITY:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		*(CVector*)&ScriptParams[0] = pObject->GetTurnSpeed() * GAME_SPEED_TO_METERS_PER_SECOND;
		StoreParameters(&m_nIp, 3);
		return 0;
	}
	case COMMAND_ADD_VELOCITY_RELATIVE_TO_OBJECT_VELOCITY:
	{
		CollectParameters(&m_nIp, 4);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		CVector vecAddition = *(CVector*)&ScriptParams[1] * CTimer::GetTimeStep() / GAME_SPEED_TO_METERS_PER_SECOND;
		if (!pObject->bIsStatic) {
			CVector vecCurrSpeed = pObject->GetSpeed();
			vecCurrSpeed.Normalise();
			if (vecCurrSpeed.z != 1.0) { // NB: not float!
				CVector vx = CrossProduct(vecCurrSpeed, CVector(0.0f, 0.0f, 1.0f));
				vx.Normalise();
				CVector vz = CrossProduct(vx, vecCurrSpeed);
				vz.Normalise();
				CVector vecNewSpeed = pObject->GetSpeed() + vecAddition.x * vx + vecAddition.y * vecCurrSpeed + vecAddition.z * vecCurrSpeed;
				if (pObject->bIsStatic) {
					pObject->SetIsStatic(false);
					pObject->AddToMovingList();
				}
				pObject->SetMoveSpeed(vecNewSpeed);
			}
		}
		return 0;
	}
	case COMMAND_GET_OBJECT_SPEED:
	{
		CollectParameters(&m_nIp, 1);
		CObject* pObject = CPools::GetObjectPool()->GetAt(ScriptParams[0]);
		*(float*)&ScriptParams[0] = pObject->GetMoveSpeed().Magnitude() * GAME_SPEED_TO_METERS_PER_SECOND;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
#endif
#if (defined GTA_MOBILE || defined SUPPORT_MOBILE_SCRIPT)
	case COMMAND_IS_MISSION_SKIP:
#ifdef MISSION_REPLAY
		ScriptParams[0] = MissionSkipLevel;
#else
		ScriptParams[0] = 0;
#endif
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_SET_IN_AMMUNATION:
		CollectParameters(&m_nIp, 1);
#ifdef MISSION_REPLAY
		IsInAmmunation = ScriptParams[0];
#endif
		return 0;
	case COMMAND_DO_SAVE_GAME:
		CollectParameters(&m_nIp, 1);
#ifdef USE_MISSION_REPLAY_OVERRIDE_FOR_NON_MOBILE_SCRIPT
		UsingMobileScript = true;
#endif
#ifdef MISSION_REPLAY
		SaveGameForPause(ScriptParams[0]);
#endif
		return 0;
	case COMMAND_IS_RETRY:
#ifdef MISSION_REPLAY
		if (strcmp(m_abScriptName, "porno4") != 0)
			ScriptParams[0] = AllowMissionReplay;
#ifdef FIX_BUGS
		else
			ScriptParams[0] = gbTryingPorn4Again;
#else
		else if (gbTryingPorn4Again)
			ScriptParams[0] = 1;
#endif
#else
		ScriptParams[0] = 0;
#endif
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_DUMMY:
		return 0;
#endif
#if (defined GTA_XBOX || defined SUPPORT_XBOX_SCRIPT || defined GTA_MOBILE || defined SUPPORT_MOBILE_SCRIPT)
	// it is unknown what these commands do but they don't take parameters
	case COMMAND_MARK_CUTSCENE_START:
		return 0;
	case COMMAND_MARK_CUTSCENE_END:
		return 0;
	case COMMAND_CUTSCENE_SCROLL:
		return 0;
#endif
	default:
		script_assert(0);
	}
	return -1;
}
