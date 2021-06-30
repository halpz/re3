#include "common.h"

#include "Automobile.h"
#include "Bridge.h"
#include "Camera.h"
#include "CarCtrl.h"
#include "Cranes.h"
#include "Darkel.h"
#include "Explosion.h"
#include "Fire.h"
#include "Frontend.h"
#include "General.h"
#include "HandlingMgr.h"
#include "Messages.h"
#include "Pad.h"
#include "PathFind.h"
#include "PlayerInfo.h"
#include "PlayerPed.h"
#include "PlayerSkin.h"
#include "ProjectileInfo.h"
#include "Remote.h"
#include "Renderer.h"
#include "Replay.h"
#include "Script.h"
#include "SpecialFX.h"
#include "Stats.h"
#include "Streaming.h"
#include "Text.h"
#include "Wanted.h"
#include "WaterLevel.h"
#include "World.h"
#include "ZoneCull.h"
#include "main.h"
#include "Bike.h"
#include "Automobile.h"
#include "GameLogic.h"

CVector lastPlayerPos;

void
CPlayerInfo::Clear(void)
{
	m_pPed = nil;
	m_pRemoteVehicle = nil;
	if (m_pVehicleEx) {
		m_pVehicleEx->bUsingSpecialColModel = false;
		m_pVehicleEx = nil;
	}
	m_nVisibleMoney = 0;
	m_nMoney = m_nVisibleMoney;
	m_WBState = WBSTATE_PLAYING;
	m_nWBTime = 0;
	m_nTrafficMultiplier = 0;
	m_fRoadDensity = 1.0f;
	m_bInRemoteMode = false;
	field_D5 = false;
	field_D6 = false;
	m_bUnusedTaxiThing = false;
	m_nUnusedTaxiTimer = 0;
	m_nCollectedPackages = 0;
	m_nTotalPackages = 3;
	m_nTimeLastHealthLoss = 0;
	m_nTimeLastArmourLoss = 0;
	m_nNextSexFrequencyUpdateTime = 0;
	m_nNextSexMoneyUpdateTime = 0;
	m_nSexFrequency = 0;
	m_pHooker = nil;
	m_nTimeTankShotGun = 0;
	field_EC = 0;
	m_nUpsideDownCounter = 0;
	m_nTimeCarSpentOnTwoWheels = 0;
	m_nDistanceCarTravelledOnTwoWheels = 0;
	m_nTimeNotFullyOnGround = 0;
	m_nTimeSpentOnWheelie = 0;
	m_nDistanceTravelledOnWheelie = 0.0f;
	m_nTimeSpentOnStoppie = 0;
	m_nDistanceTravelledOnStoppie = 0.0f;
	m_nCancelWheelStuntTimer = 0;
	m_nLastTimeCarSpentOnTwoWheels = 0;
	m_nLastDistanceCarTravelledOnTwoWheels = 0;
	m_nLastTimeSpentOnWheelie = 0;
	m_nLastDistanceTravelledOnWheelie = 0;
	m_nLastTimeSpentOnStoppie = 0;
	m_nLastDistanceTravelledOnStoppie = 0;
	m_bInfiniteSprint = false;
	m_bFastReload = false;
	m_bFireproof = false;
	m_nMaxHealth = m_nMaxArmour = 100;
	m_bGetOutOfJailFree = false;
	m_bGetOutOfHospitalFree = false;
	m_bDriveByAllowed = true;
	m_nPreviousTimeRewardedForExplosion = 0;
	m_nExplosionsSinceLastReward = 0;
	m_nHavocLevel = 0;
	m_fMediaAttention = 0.0f;
	m_nCurrentBustedAudio = 1;
	m_nBustedAudioStatus = BUSTEDAUDIO_NONE;
}

void
CPlayerInfo::Process(void)
{
#ifdef FIX_BUGS
	if (CReplay::IsPlayingBack())
		return;
#endif
	// Unused taxi feature. Gives you a dollar for every second with a passenger. Can be toggled via 0x29A opcode.
	bool startTaxiTimer = true;
	if (m_bUnusedTaxiThing && m_pPed->bInVehicle) {
		CVehicle *veh = m_pPed->m_pMyVehicle;
		if (veh->IsTaxi()
			&& veh->pDriver == m_pPed && veh->m_nNumPassengers != 0) {
			for (uint32 timePassed = CTimer::GetTimeInMilliseconds() - m_nUnusedTaxiTimer; timePassed >= 1000; m_nUnusedTaxiTimer += 1000) {
				timePassed -= 1000;
				++m_nMoney;
			}
			startTaxiTimer = false;
		}
	}
	if (startTaxiTimer)
		m_nUnusedTaxiTimer = CTimer::GetTimeInMilliseconds();

	if (!m_pPed->InVehicle()) {
		m_nTimeCarSpentOnTwoWheels = 0;
		m_nTimeNotFullyOnGround = 0;
		m_nTimeSpentOnWheelie = 0;
		m_nTimeSpentOnStoppie = 0;
		m_nCancelWheelStuntTimer = 0;
	} else if (m_pPed->m_pMyVehicle->IsCar()) {
		CAutomobile *car = (CAutomobile*)m_pPed->m_pMyVehicle;

		if (car->m_nWheelsOnGround < 3)
			m_nTimeNotFullyOnGround += CTimer::GetTimeStepInMilliseconds();
		else
			m_nTimeNotFullyOnGround = 0;

		if (car->m_aSuspensionSpringRatioPrev[2] == 1.f && car->m_aSuspensionSpringRatioPrev[3] == 1.f) {
			if (car->m_aSuspensionSpringRatioPrev[0] < 1.0f && car->m_aSuspensionSpringRatioPrev[1] < 1.0f && car->m_fDamageImpulse == 0.0f) {
				m_nTimeCarSpentOnTwoWheels += CTimer::GetTimeStepInMilliseconds();
				m_nDistanceCarTravelledOnTwoWheels += car->m_fDistanceTravelled;
				m_nCancelWheelStuntTimer = Max(0.0f, m_nCancelWheelStuntTimer - CTimer::GetTimeStepInMilliseconds() * 0.5f);

			} else {
				if (m_nTimeCarSpentOnTwoWheels != 0 && m_nCancelWheelStuntTimer < 500) {
					m_nCancelWheelStuntTimer += CTimer::GetTimeStepInMilliseconds();
				} else {
					if (m_nTimeCarSpentOnTwoWheels >= 2000) {
						m_nLastTimeCarSpentOnTwoWheels = m_nTimeCarSpentOnTwoWheels;
						m_nLastDistanceCarTravelledOnTwoWheels = m_nDistanceCarTravelledOnTwoWheels;
						if (CStats::Longest2Wheel < m_nTimeCarSpentOnTwoWheels / 1000)
							CStats::Longest2Wheel = m_nTimeCarSpentOnTwoWheels / 1000;
						if (CStats::Longest2WheelDist < m_nDistanceCarTravelledOnTwoWheels)
							CStats::Longest2WheelDist = m_nDistanceCarTravelledOnTwoWheels;
					}
					m_nTimeCarSpentOnTwoWheels = 0;
					m_nDistanceCarTravelledOnTwoWheels = 0;
					m_nCancelWheelStuntTimer = 0;
				}
			}
		} else if (car->m_aSuspensionSpringRatioPrev[0] == 1.0f && car->m_aSuspensionSpringRatioPrev[1] == 1.0f) {
#ifdef FIX_BUGS
			if (car->m_aSuspensionSpringRatioPrev[2] < 1.f
#else
			if (car->m_aSuspensionSpringRatioPrev[1] < 1.f
#endif
				&& car->m_aSuspensionSpringRatioPrev[3] < 1.f && 0.0f == car->m_fDamageImpulse) {
				m_nTimeCarSpentOnTwoWheels += CTimer::GetTimeStepInMilliseconds();
				m_nDistanceCarTravelledOnTwoWheels += car->m_fDistanceTravelled;
				m_nCancelWheelStuntTimer = Max(0.0f, m_nCancelWheelStuntTimer - CTimer::GetTimeStepInMilliseconds() * 0.2f);

			} else if (m_nTimeCarSpentOnTwoWheels != 0 && m_nCancelWheelStuntTimer < 500) {
				m_nCancelWheelStuntTimer += CTimer::GetTimeStepInMilliseconds();

			} else {
				if (m_nTimeCarSpentOnTwoWheels >= 2000) {
					m_nLastTimeCarSpentOnTwoWheels = m_nTimeCarSpentOnTwoWheels;
					m_nLastDistanceCarTravelledOnTwoWheels = m_nDistanceCarTravelledOnTwoWheels;
					if (CStats::Longest2Wheel < m_nTimeCarSpentOnTwoWheels / 1000)
						CStats::Longest2Wheel = m_nTimeCarSpentOnTwoWheels / 1000;
					if (CStats::Longest2WheelDist < m_nDistanceCarTravelledOnTwoWheels)
						CStats::Longest2WheelDist = m_nDistanceCarTravelledOnTwoWheels;
				}
				m_nTimeCarSpentOnTwoWheels = 0;
				m_nDistanceCarTravelledOnTwoWheels = 0;
				m_nCancelWheelStuntTimer = 0;
			}
		} else if (m_nTimeCarSpentOnTwoWheels != 0) {
			if (m_nTimeCarSpentOnTwoWheels >= 2000) {
				m_nLastTimeCarSpentOnTwoWheels = m_nTimeCarSpentOnTwoWheels;
				m_nLastDistanceCarTravelledOnTwoWheels = m_nDistanceCarTravelledOnTwoWheels;
				if (CStats::Longest2Wheel < m_nTimeCarSpentOnTwoWheels / 1000)
					CStats::Longest2Wheel = m_nTimeCarSpentOnTwoWheels / 1000;
				if (CStats::Longest2WheelDist < m_nDistanceCarTravelledOnTwoWheels)
					CStats::Longest2WheelDist = m_nDistanceCarTravelledOnTwoWheels;
			}
			m_nTimeCarSpentOnTwoWheels = 0;
			m_nDistanceCarTravelledOnTwoWheels = 0;
			m_nCancelWheelStuntTimer = 0;
		}
		m_nTimeSpentOnWheelie = 0;
		m_nTimeSpentOnStoppie = 0;
	} else if (m_pPed->m_pMyVehicle->IsBike()) {
		CBike *bike = (CBike*)m_pPed->m_pMyVehicle;
		if (bike->m_aSuspensionSpringRatioPrev[0] == 1.0f && bike->m_aSuspensionSpringRatioPrev[1] == 1.0f) {
			if (bike->m_aSuspensionSpringRatioPrev[2] < 1.0f
				|| (bike->m_aSuspensionSpringRatioPrev[3] < 1.0f && 0.0f == bike->m_fDamageImpulse)) {
				m_nTimeSpentOnWheelie += CTimer::GetTimeStepInMilliseconds();
				m_nDistanceTravelledOnWheelie += bike->m_fDistanceTravelled;
				m_nCancelWheelStuntTimer = Max(0.0f, m_nCancelWheelStuntTimer - CTimer::GetTimeStepInMilliseconds() * 0.2f);

			} else {
				if (m_nTimeSpentOnWheelie != 0 && m_nCancelWheelStuntTimer < 500) {
					m_nCancelWheelStuntTimer += CTimer::GetTimeStepInMilliseconds();
				} else {
					if (m_nTimeSpentOnWheelie >= 5000) {
						m_nLastTimeSpentOnWheelie = m_nTimeSpentOnWheelie;
						m_nLastDistanceTravelledOnWheelie = m_nDistanceTravelledOnWheelie;
						if (CStats::LongestWheelie < m_nTimeSpentOnWheelie / 1000)
							CStats::LongestWheelie = m_nTimeSpentOnWheelie / 1000;
						if (CStats::LongestWheelieDist < m_nDistanceTravelledOnWheelie)
							CStats::LongestWheelieDist = m_nDistanceTravelledOnWheelie;
					}
					m_nTimeSpentOnWheelie = 0;
					m_nDistanceTravelledOnWheelie = 0;
					m_nCancelWheelStuntTimer = 0;
				}
			}
		} else if (m_nTimeSpentOnWheelie != 0) {
			if (m_nTimeSpentOnWheelie >= 5000) {
				m_nLastTimeSpentOnWheelie = m_nTimeSpentOnWheelie;
				m_nLastDistanceTravelledOnWheelie = m_nDistanceTravelledOnWheelie;
				if (CStats::LongestWheelie < m_nTimeSpentOnWheelie / 1000)
					CStats::LongestWheelie = m_nTimeSpentOnWheelie / 1000;
				if (CStats::LongestWheelieDist < m_nDistanceTravelledOnWheelie)
					CStats::LongestWheelieDist = m_nDistanceTravelledOnWheelie;
			}
			m_nTimeSpentOnWheelie = 0;
			m_nDistanceTravelledOnWheelie = 0;
			m_nCancelWheelStuntTimer = 0;

		} else if (bike->m_aSuspensionSpringRatioPrev[2] == 1.0f && bike->m_aSuspensionSpringRatioPrev[3] == 1.0f
			&& 0.0f == bike->m_fDamageImpulse) {
			m_nTimeSpentOnStoppie += CTimer::GetTimeStepInMilliseconds();
			m_nDistanceTravelledOnStoppie += bike->m_fDistanceTravelled;
			m_nCancelWheelStuntTimer = Max(0.0f, m_nCancelWheelStuntTimer - CTimer::GetTimeStepInMilliseconds() * 0.2f);

		} else {
			if (m_nTimeSpentOnStoppie != 0 && m_nCancelWheelStuntTimer < 500) {
				m_nCancelWheelStuntTimer += CTimer::GetTimeStepInMilliseconds();
			} else {
				if (m_nTimeSpentOnStoppie >= 2000) {
					m_nLastTimeSpentOnStoppie = m_nTimeSpentOnStoppie;
					m_nLastDistanceTravelledOnStoppie = m_nDistanceTravelledOnStoppie;
					if (CStats::LongestStoppie < m_nTimeSpentOnStoppie / 1000)
						CStats::LongestStoppie = m_nTimeSpentOnStoppie / 1000;
					if (CStats::LongestStoppieDist < m_nDistanceTravelledOnStoppie)
						CStats::LongestStoppieDist = m_nDistanceTravelledOnStoppie;
				}
				m_nTimeSpentOnStoppie = 0;
				m_nDistanceTravelledOnStoppie = 0;
				m_nCancelWheelStuntTimer = 0;
			}
		}
		m_nTimeCarSpentOnTwoWheels = 0;
		m_nTimeNotFullyOnGround = 0;
	} else {
		m_nTimeCarSpentOnTwoWheels = 0;
		m_nTimeNotFullyOnGround = 0;
		m_nTimeSpentOnWheelie = 0;
		m_nTimeSpentOnStoppie = 0;
		m_nCancelWheelStuntTimer = 0;
	}

	// The effect that makes money counter does while earning/losing money
	if (m_nVisibleMoney != m_nMoney) {
		int diff = m_nMoney - m_nVisibleMoney;
		int diffAbs = Abs(diff);
		int changeBy;

		if (diffAbs > 100000)
			changeBy = 12345;
		else if (diffAbs > 10000)
			changeBy = 1234;
		else if (diffAbs > 1000)
			changeBy = 123;
		else if (diffAbs > 50)
			changeBy = 42;
		else
			changeBy = 1;

		if (diff < 0)
			m_nVisibleMoney -= changeBy;
		else
			m_nVisibleMoney += changeBy;
	}

	if (!(CTimer::GetFrameCounter() & 15)) {
		CVector2D playerPos = m_pPed->bInVehicle ? m_pPed->m_pMyVehicle->GetPosition() : m_pPed->GetPosition();
		m_fRoadDensity = ThePaths.CalcRoadDensity(playerPos.x, playerPos.y);
	}

	m_fRoadDensity = Clamp(m_fRoadDensity, 0.5f, 1.45f);

	// Because vehicle enter/exit use same key binding.
	bool enterOrExitVeh;
	if (m_pPed->bVehExitWillBeInstant && m_pPed->bInVehicle)
		enterOrExitVeh = CPad::GetPad(0)->ExitVehicleJustDown();
	else
		enterOrExitVeh = CPad::GetPad(0)->GetExitVehicle();

	if (enterOrExitVeh && m_pPed->m_nPedState != PED_ANSWER_MOBILE && m_pPed->m_nPedState != PED_SNIPER_MODE && m_pPed->m_nPedState != PED_ROCKET_MODE) {
		if (m_pPed->bInVehicle) {
			if (!m_pRemoteVehicle) {
				CEntity *surfaceBelowVeh = m_pPed->m_pMyVehicle->m_pCurGroundEntity;
				if (!surfaceBelowVeh || !CBridge::ThisIsABridgeObjectMovingUp(surfaceBelowVeh->GetModelIndex())) {
					CVehicle *veh = m_pPed->m_pMyVehicle;
					if (!veh->IsBoat() || veh->m_nDoorLock == CARLOCK_LOCKED_PLAYER_INSIDE) {
						if (veh->GetStatus() != STATUS_WRECKED && veh->GetStatus() != STATUS_TRAIN_MOVING && veh->m_nDoorLock != CARLOCK_LOCKED_PLAYER_INSIDE) {
							bool canJumpOff = false;
							if (veh->m_vehType == VEHICLE_TYPE_BIKE) {
								canJumpOff = veh->CanPedJumpOffBike();
							} else if (veh->pDriver == m_pPed) {
								canJumpOff = veh->CanPedJumpOutCar();
							}

							if (canJumpOff || veh->m_vecMoveSpeed.Magnitude() < 0.1f) {
								if (!veh->bIsInWater)
									m_pPed->SetObjective(OBJECTIVE_LEAVE_CAR, veh);

							} else if (veh->GetStatus() != STATUS_PLAYER && veh != CGameLogic::pShortCutTaxi) {
								veh->AutoPilot.m_nTempAction = TEMPACT_WAIT;
								veh->AutoPilot.m_nTimeTempAction = CTimer::GetTimeInMilliseconds() + 1000;
							}
						}
					} else {
						m_pPed->SetExitBoat(veh);
						m_pPed->bTryingToReachDryLand = true;
					}
				}
			}
		} else {
			// Enter vehicle
			if (CPad::GetPad(0)->ExitVehicleJustDown()) {
				bool weAreOnBoat = false;
				float lastCloseness = 0.0f;
				CVehicle *carBelow = nil;
				CEntity *surfaceBelow = m_pPed->m_pCurrentPhysSurface;
				if (surfaceBelow && surfaceBelow->IsVehicle()) {
					carBelow = (CVehicle*)surfaceBelow;
					if (carBelow->IsBoat() && carBelow->m_modelIndex != MI_SKIMMER) {
						weAreOnBoat = true;
						m_pPed->bOnBoat = true;
						if (carBelow->GetStatus() != STATUS_WRECKED && carBelow->GetUp().z > 0.3f)
							m_pPed->SetSeekBoatPosition(carBelow);
					}
				}
				// Find closest car
				if (!weAreOnBoat) {
					float minX = m_pPed->GetPosition().x - 10.0f;
					float maxX = 10.0f + m_pPed->GetPosition().x;
					float minY = m_pPed->GetPosition().y - 10.0f;
					float maxY = 10.0f + m_pPed->GetPosition().y;

					int minXSector = CWorld::GetSectorIndexX(minX);
					if (minXSector < 0) minXSector = 0;
					int minYSector = CWorld::GetSectorIndexY(minY);
					if (minYSector < 0) minYSector = 0;
					int maxXSector = CWorld::GetSectorIndexX(maxX);
					if (maxXSector > NUMSECTORS_X - 1) maxXSector = NUMSECTORS_X - 1;
					int maxYSector = CWorld::GetSectorIndexY(maxY);
					if (maxYSector > NUMSECTORS_Y - 1) maxYSector = NUMSECTORS_Y - 1;

					CWorld::AdvanceCurrentScanCode();

					for (int curY = minYSector; curY <= maxYSector; curY++) {
						for (int curX = minXSector; curX <= maxXSector; curX++) {
							CSector *sector = CWorld::GetSector(curX, curY);
							FindClosestCarSectorList(sector->m_lists[ENTITYLIST_VEHICLES], m_pPed,
								minX, minY, maxX, maxY, &lastCloseness, &carBelow);
							FindClosestCarSectorList(sector->m_lists[ENTITYLIST_VEHICLES_OVERLAP], m_pPed,
								minX, minY, maxX, maxY, &lastCloseness, &carBelow);
						}
					}
				}
				// carBelow is now closest vehicle
				if (carBelow && !weAreOnBoat) {
					if (carBelow->GetStatus() == STATUS_TRAIN_NOT_MOVING) {
						m_pPed->SetObjective(OBJECTIVE_ENTER_CAR_AS_PASSENGER, carBelow);
					} else if (carBelow->IsBoat()) {
						if (!carBelow->pDriver) {
							m_pPed->m_vehDoor = 0;
							m_pPed->SetEnterCar(carBelow, m_pPed->m_vehDoor);
						}
					} else {
						m_pPed->SetObjective(OBJECTIVE_ENTER_CAR_AS_DRIVER, carBelow);
					}
				}
			}
		}
	}

	if (m_bInRemoteMode) {
		uint32 timeWithoutRemoteCar = CTimer::GetTimeInMilliseconds() - m_nTimeLostRemoteCar;
		if (CTimer::GetPreviousTimeInMilliseconds() - m_nTimeLostRemoteCar < 1000 && timeWithoutRemoteCar >= 1000 && m_WBState == WBSTATE_PLAYING && field_D6) {
			TheCamera.SetFadeColour(0, 0, 0);
			TheCamera.Fade(1.0f, FADE_OUT);
		}
		if (timeWithoutRemoteCar > 2000) {
			if (m_WBState == WBSTATE_PLAYING && field_D6) {
				TheCamera.RestoreWithJumpCut();
				TheCamera.SetFadeColour(0, 0, 0);
				TheCamera.Fade(1.0f, FADE_IN);
				TheCamera.Process();
				CTimer::Stop();
				CCullZones::ForceCullZoneCoors(TheCamera.GetPosition());
				CRenderer::RequestObjectsInFrustum();
				CStreaming::LoadAllRequestedModels(false);
				CTimer::Update();
			}
			m_bInRemoteMode = false;
			if (CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle) {
				CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle->bRemoveFromWorld = true;
				CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle = nil;
			}
			if (FindPlayerVehicle()) {
				FindPlayerVehicle()->SetStatus(STATUS_PLAYER);
			}
		}
	}
	if (!(CTimer::GetFrameCounter() & 31)) {
		CVehicle *veh = FindPlayerVehicle();
		if (veh && m_pPed->bInVehicle && veh->GetUp().z < 0.0f
			&& veh->m_vecMoveSpeed.Magnitude() < 0.05f && (veh->IsCar() || veh->IsBoat()) && !veh->bIsInWater) {

			if (veh->GetUp().z < -0.5f) {
				m_nUpsideDownCounter += 2;
			} else {
				m_nUpsideDownCounter++;
			}
		} else {
			m_nUpsideDownCounter = 0;
		}

		if (m_nUpsideDownCounter > 6 && veh->bCanBeDamaged) {
			veh->m_fHealth = 249.0f < veh->m_fHealth ? 249.0f : veh->m_fHealth;
			if (veh->IsCar()) {
				CAutomobile* car = (CAutomobile*)veh;
				car->Damage.SetEngineStatus(225);
				car->m_pSetOnFireEntity = nil;
			}
		}
	}
	if (FindPlayerVehicle()) {
		CVehicle *veh = FindPlayerVehicle();
		veh->m_nZoneLevel = LEVEL_IGNORE;
		for (int i = 0; i < ARRAY_SIZE(veh->pPassengers); i++) {
			if (veh->pPassengers[i])
				veh->pPassengers[i]->m_nZoneLevel = LEVEL_GENERIC;
		}
		if(veh->m_modelIndex == MI_CADDY)
			CStats::DistanceTravelledByGolfCart += veh->m_fDistanceTravelled;
		else {
			if(veh->GetVehicleAppearance() == VEHICLE_APPEARANCE_HELI)
				CStats::DistanceTravelledByHelicoptor += veh->m_fDistanceTravelled;
			if (veh->GetVehicleAppearance() == VEHICLE_APPEARANCE_PLANE)
				CStats::DistanceTravelledByPlane += veh->m_fDistanceTravelled;
			if (veh->GetVehicleAppearance() == VEHICLE_APPEARANCE_CAR)
				CStats::DistanceTravelledByCar += veh->m_fDistanceTravelled;
			if (veh->GetVehicleAppearance() == VEHICLE_APPEARANCE_BIKE)
				CStats::DistanceTravelledByBike += veh->m_fDistanceTravelled;
			if (veh->GetVehicleAppearance() == VEHICLE_APPEARANCE_BOAT)
				CStats::DistanceTravelledByBoat += veh->m_fDistanceTravelled;

			if (veh->GetVehicleAppearance() == VEHICLE_APPEARANCE_PLANE) {
				if (veh->m_vecMoveSpeed.Magnitude() > 0.2f) {
					CStats::FlightTime += CTimer::GetTimeStep() * 16.f; // what a weird choice
				}
			}
		}
	} else {
		CStats::DistanceTravelledOnFoot += FindPlayerPed()->m_fDistanceTravelled;
	}

	if (m_pPed->m_pWanted->GetWantedLevel() && !CTheScripts::IsPlayerOnAMission()) {
		float maxDelta = 0.0f;
		static bool movedSignificantly = true;
		static bool thereIsACarPathNear = true;
		// there was one more guard without variable's itself???

		if (CTimer::GetTimeInMilliseconds() / 20000 != CTimer::GetPreviousTimeInMilliseconds() / 20000) {
			float posChange = (lastPlayerPos - FindPlayerCoors()).Magnitude();
			movedSignificantly = posChange >= 10.0f;
			lastPlayerPos = FindPlayerCoors();
			thereIsACarPathNear = ThePaths.FindNodeClosestToCoors(FindPlayerCoors(), PATH_CAR, 60.0f, true, false, false, false) != 0;
		}
		switch (m_pPed->m_pWanted->GetWantedLevel()) {
			case 1:
				maxDelta = 31.f;
				break;
			case 2:
				maxDelta = 62.f;
				break;
			case 3:
				maxDelta = 125.f;
				break;
			case 4:
				maxDelta = 250.f;
				break;
			case 5:
				maxDelta = 500.f;
				break;
			case 6:
				maxDelta = 1000.f;
				break;
			default:
				break;
		}
		float increaseDelta = maxDelta - m_fMediaAttention;
		float increaseAttentionBy = CTimer::GetTimeStep() * 0.0001f * increaseDelta;
		if (increaseAttentionBy < 0.0f
			|| movedSignificantly && thereIsACarPathNear && !CCullZones::NoPolice() && !CCullZones::PoliceAbandonCars() && CGame::currArea == AREA_MAIN_MAP) {
			m_fMediaAttention += increaseAttentionBy;
		}
	} else {
		m_fMediaAttention = 0.0f;
	}
	CStats::HighestChaseValue = Max(m_fMediaAttention, CStats::HighestChaseValue);
	m_nMoney = Min(999999999, m_nMoney);
	m_nVisibleMoney = Min(999999999, m_nVisibleMoney);
}

bool
CPlayerInfo::IsPlayerInRemoteMode()
{
	return m_pRemoteVehicle || m_bInRemoteMode;
}

void
CPlayerInfo::SavePlayerInfo(uint8 *buf, uint32 *size)
{
	// Interesting
	*size = sizeof(CPlayerInfo);

#define CopyToBuf(buf, data) memcpy(buf, &data, sizeof(data)); buf += sizeof(data);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nMoney);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_WBState);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nWBTime);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nTrafficMultiplier);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_fRoadDensity);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nVisibleMoney);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nCollectedPackages);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nTotalPackages);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bInfiniteSprint);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bFastReload);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bFireproof);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nMaxHealth);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nMaxArmour);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfJailFree);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfHospitalFree);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bDriveByAllowed);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_aPlayerName);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nBustedAudioStatus);
	CopyToBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nCurrentBustedAudio);
#undef CopyToBuf
}

void
CPlayerInfo::LoadPlayerInfo(uint8 *buf, uint32 size)
{
#define CopyFromBuf(buf, data) memcpy(&data, buf, sizeof(data)); buf += sizeof(data);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nMoney);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_WBState);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nWBTime);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nTrafficMultiplier);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_fRoadDensity);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nVisibleMoney);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nCollectedPackages);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nTotalPackages);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bInfiniteSprint);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bFastReload);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bFireproof);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nMaxHealth);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nMaxArmour);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfJailFree);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bGetOutOfHospitalFree);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_bDriveByAllowed);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_aPlayerName);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nBustedAudioStatus);
	CopyFromBuf(buf, CWorld::Players[CWorld::PlayerInFocus].m_nCurrentBustedAudio)
#undef CopyFromBuf
}

void
CPlayerInfo::FindClosestCarSectorList(CPtrList& carList, CPed* ped, float unk1, float unk2, float unk3, float unk4, float* lastCloseness, CVehicle** closestCarOutput)
{
	for (CPtrNode* node = carList.first; node; node = node->next) {
		CVehicle *car = (CVehicle*)node->item;
		if(car->m_scanCode != CWorld::GetCurrentScanCode()) {
			if (!car->bUsesCollision || !car->IsVehicle())
				continue;

			car->m_scanCode = CWorld::GetCurrentScanCode();
			if (car->GetStatus() != STATUS_WRECKED && car->GetStatus() != STATUS_TRAIN_MOVING
				&& (car->GetUp().z > 0.3f || (car->IsVehicle() && ((CVehicle*)car)->m_vehType == VEHICLE_TYPE_BIKE))) {
				CVector carCentre = car->GetBoundCentre();

				if (Abs(ped->GetPosition().z - carCentre.z) < 2.0f || car->IsCar() && carCentre.z < ped->GetPosition().z && ped->GetPosition().z - 4.f < carCentre.z) {
					float dist = (ped->GetPosition() - carCentre).Magnitude2D();
					if (dist <= 10.0f && !CCranes::IsThisCarBeingCarriedByAnyCrane(car)) {
						EvaluateCarPosition(car, ped, dist, lastCloseness, closestCarOutput);
					}
				}
			}
		}
	}
}

// lastCloseness is passed to other calls of this function
void
CPlayerInfo::EvaluateCarPosition(CEntity *carToTest, CPed *player, float carBoundCentrePedDist, float *lastCloseness, CVehicle **closestCarOutput)
{
	// This dist used for determining the angle to face
	CVector2D dist(carToTest->GetPosition() - player->GetPosition());
	float neededTurn = CGeneral::GetATanOfXY(player->GetForward().x, player->GetForward().y) - CGeneral::GetATanOfXY(dist.x, dist.y);
	while (neededTurn >= PI) {
		neededTurn -= 2 * PI;
	}

	while (neededTurn < -PI) {
		neededTurn += 2 * PI;
	}

	// This dist used for evaluating cars' distances, weird...
	// Accounts inverted needed turn (or needed turn in long way) and car dist.
	float closeness = (1.0f - Abs(neededTurn) / TWOPI) * (10.0f - carBoundCentrePedDist);
	if (closeness > *lastCloseness) {
		*lastCloseness = closeness;
		*closestCarOutput = (CVehicle*)carToTest;
	}
}

const CVector &
CPlayerInfo::GetPos()
{
#ifdef FIX_BUGS
	if (!m_pPed)
		return TheCamera.GetPosition();
#endif
	if (m_pPed->InVehicle())
		return m_pPed->m_pMyVehicle->GetPosition();
	return m_pPed->GetPosition();
}

CVector
FindPlayerCoors(void)
{
#ifdef FIX_BUGS
	if (CReplay::IsPlayingBack())
		return TheCamera.GetPosition();
#endif
	CPlayerPed *ped = FindPlayerPed();
	if(ped->InVehicle())
		return ped->m_pMyVehicle->GetPosition();
	else
		return ped->GetPosition();
}

const CVector &
FindPlayerSpeed(void)
{
#ifdef FIX_BUGS
	static CVector vecTmpVector(0.0f, 0.0f, 0.0f);
	if (CReplay::IsPlayingBack())
		return vecTmpVector;
#endif
	CPlayerPed *ped = FindPlayerPed();
	if(ped->InVehicle())
		return ped->m_pMyVehicle->m_vecMoveSpeed;
	else
		return ped->m_vecMoveSpeed;
}

CVehicle *
FindPlayerVehicle(void)
{
	CPlayerPed *ped = FindPlayerPed();
	if(ped && ped->InVehicle()) return ped->m_pMyVehicle;
	return nil;
}

CEntity *
FindPlayerEntity(void)
{
	CPlayerPed *ped = FindPlayerPed();
	if(ped->InVehicle())
		return ped->m_pMyVehicle;
	else
		return ped;
}

CVehicle *
FindPlayerTrain(void)
{
	if(FindPlayerVehicle() && FindPlayerVehicle()->IsTrain())
		return FindPlayerVehicle();
	else
		return nil;
}

CPlayerPed *
FindPlayerPed(void)
{
	return CWorld::Players[CWorld::PlayerInFocus].m_pPed;
}

const CVector &
FindPlayerCentreOfWorld(int32 player)
{
#ifdef FIX_BUGS
	if(CReplay::IsPlayingBack()) return TheCamera.GetPosition();
#endif
	if(CCarCtrl::bCarsGeneratedAroundCamera) return TheCamera.GetPosition();
	if(CWorld::Players[player].m_pRemoteVehicle) return CWorld::Players[player].m_pRemoteVehicle->GetPosition();
	if(FindPlayerVehicle()) return FindPlayerVehicle()->GetPosition();
	return CWorld::Players[player].m_pPed->GetPosition();
}

const CVector &
FindPlayerCentreOfWorld_NoSniperShift(void)
{
#ifdef FIX_BUGS
	if (CReplay::IsPlayingBack()) return TheCamera.GetPosition();
#endif
	if(CCarCtrl::bCarsGeneratedAroundCamera) return TheCamera.GetPosition();
	if(CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle)
		return CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle->GetPosition();
	if(FindPlayerVehicle()) return FindPlayerVehicle()->GetPosition();
	return FindPlayerPed()->GetPosition();
}

float
FindPlayerHeading(void)
{
	if(CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle)
		return CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle->GetForward().Heading();
	if(FindPlayerVehicle()) return FindPlayerVehicle()->GetForward().Heading();
	return FindPlayerPed()->GetForward().Heading();
}

bool
CPlayerInfo::IsRestartingAfterDeath()
{
	return m_WBState == WBSTATE_WASTED;
}

bool
CPlayerInfo::IsRestartingAfterArrest()
{
	return m_WBState == WBSTATE_BUSTED;
}

void
CPlayerInfo::KillPlayer()
{
	if (m_WBState != WBSTATE_PLAYING) return;

	m_WBState = WBSTATE_WASTED;
	m_nWBTime = CTimer::GetTimeInMilliseconds();
	CDarkel::ResetOnPlayerDeath();
	CMessages::AddBigMessage(TheText.Get("DEAD"), 4000, 2);
	CStats::TimesDied++;
}

void
CPlayerInfo::ArrestPlayer()
{
	if (m_WBState != WBSTATE_PLAYING) return;

	m_WBState = WBSTATE_BUSTED;
	m_nWBTime = CTimer::GetTimeInMilliseconds();
	m_nBustedAudioStatus = BUSTEDAUDIO_NONE;
	CDarkel::ResetOnPlayerDeath();
	CMessages::AddBigMessage(TheText.Get("BUSTED"), 5000, 2);
	CStats::TimesArrested++;
}

void
CPlayerInfo::PlayerFailedCriticalMission()
{
	if (m_WBState != WBSTATE_PLAYING)
		return;
	m_WBState = WBSTATE_FAILED_CRITICAL_MISSION;
	m_nWBTime = CTimer::GetTimeInMilliseconds();
	CDarkel::ResetOnPlayerDeath();
}

void
CPlayerInfo::CancelPlayerEnteringCars(CVehicle *car)
{
	if (!car || car == m_pPed->m_pMyVehicle) {
		if (m_pPed->EnteringCar())
			m_pPed->QuitEnteringCar();
	}
	if (m_pPed->m_objective == OBJECTIVE_ENTER_CAR_AS_PASSENGER || m_pPed->m_objective == OBJECTIVE_ENTER_CAR_AS_DRIVER)
		m_pPed->ClearObjective();
}

void
CPlayerInfo::MakePlayerSafe(bool toggle)
{
	if (toggle) {
		m_pPed->m_pWanted->m_bIgnoredByEveryone = true;
		CWorld::StopAllLawEnforcersInTheirTracks();
		CPad::GetPad(0)->SetDisablePlayerControls(PLAYERCONTROL_PLAYERINFO);
		CPad::StopPadsShaking();
		m_pPed->bBulletProof = true;
		m_pPed->bFireProof = true;
		m_pPed->bCollisionProof = true;
		m_pPed->bMeleeProof = true;
		m_pPed->bOnlyDamagedByPlayer = true;
		m_pPed->bExplosionProof = true;
		m_pPed->m_bCanBeDamaged = false;
		((CPlayerPed*)m_pPed)->ClearAdrenaline();
		CancelPlayerEnteringCars(nil);
		gFireManager.ExtinguishPoint(GetPos(), 4000.0f);
		CExplosion::RemoveAllExplosionsInArea(GetPos(), 4000.0f);
		CProjectileInfo::RemoveAllProjectiles();
		CWorld::SetAllCarsCanBeDamaged(false);
		CWorld::ExtinguishAllCarFiresInArea(GetPos(), 4000.0f);
		CReplay::DisableReplays();

	} else {
		m_pPed->m_pWanted->m_bIgnoredByEveryone = false;
		CPad::GetPad(0)->SetEnablePlayerControls(PLAYERCONTROL_PLAYERINFO);
		m_pPed->bBulletProof = false;
		m_pPed->bFireProof = false;
		m_pPed->bCollisionProof = false;
		m_pPed->bMeleeProof = false;
		m_pPed->bOnlyDamagedByPlayer = false;
		m_pPed->bExplosionProof = false;
		m_pPed->m_bCanBeDamaged = true;
		CWorld::SetAllCarsCanBeDamaged(true);
		CReplay::EnableReplays();
	}
}

void
CPlayerInfo::BlowUpRCBuggy(bool actually)
{
	if (!m_pRemoteVehicle || m_pRemoteVehicle->bRemoveFromWorld)
		return;

	CRemote::TakeRemoteControlledCarFromPlayer(actually);
	if (actually)
		m_pRemoteVehicle->BlowUpCar(FindPlayerPed());
}

#ifdef GTA_PC
void
CPlayerInfo::SetPlayerSkin(const char *skin)
{
	strncpy(m_aSkinName, skin, 32);
	LoadPlayerSkin();
}

void
CPlayerInfo::LoadPlayerSkin()
{
	DeletePlayerSkin();

	m_pSkinTexture = CPlayerSkin::GetSkinTexture(m_aSkinName);
}

void
CPlayerInfo::DeletePlayerSkin()
{
	if (m_pSkinTexture) {
		RwTextureDestroy(m_pSkinTexture);
		m_pSkinTexture = nil;
	}
}
#endif
