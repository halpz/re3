#pragma once

#include "Vehicle.h"
#include "DamageManager.h"
#include "Door.h"

class CObject;

class CAutomobile : public CVehicle
{
public:
	// 0x288
	CDamageManager Damage;
	CDoor Doors[6];
	RwFrame *m_aCarNodes[NUM_CAR_NODES];
	CColPoint m_aWheelColPoints[4];
	float m_aSuspensionSpringRatio[4];
	float m_aSuspensionSpringRatioPrev[4];
	float m_aWheelSkidThing[4];
	float field_49C;
	bool m_aWheelSkidmarkMuddy[4];
	bool m_aWheelSkidmarkBloody[4];
	float m_aWheelRotation[4];
	float m_aWheelPosition[4];
	float m_aWheelSpeed[4];
	uint8 field_4D8;
	uint8 m_auto_flagA1 : 1;
	uint8 m_auto_flagA2 : 1;
	uint8 m_auto_flagA4 : 1;
	uint8 bTaxiLight : 1;
	uint8 m_auto_flagA10 : 1;
	uint8 m_auto_flagA20 : 1;
	uint8 m_auto_flagA40 : 1;
	uint8 m_auto_flagA80 : 1;
	uint8 field_4DA[10];
	uint32 m_nBusDoorTimerEnd;
	uint32 m_nBusDoorTimerStart;
	float m_aSuspensionSpringLength[4];
	float m_aSuspensionLineLength[4];
	float m_fHeightAboveRoad;
	float m_fImprovedHandling;
	uint8 stuff6[32];
	CPhysical *m_aGroundPhysical[4];	// physicals touching wheels
	CVector m_aGroundOffset[4];		// from ground object to colpoint
	CEntity *m_pBlowUpEntity;
	float m_weaponThingA;	// TODO
	float m_weaponThingB;	// TODO
	float m_fCarGunLR;
	float m_fCarGunUD;
	float m_fWindScreenRotation;
	uint8 stuff4[4];
	uint8 m_nWheelsOnGround_2;
	uint8 m_nWheelsOnGround;
	uint8 m_nWheelsOnGroundPrev;
	uint8 stuff5[5];
	int32 m_aWheelState[4];

	static bool &m_sAllTaxiLights;

	CAutomobile(int, uint8);

	// from CEntity
	void SetModelIndex(uint32 id);
	void ProcessControl(void);
	void Teleport(CVector v);
	void PreRender(void);
	void Render(void);

	// from CVehicle
	void ProcessControlInputs(uint8);
	void GetComponentWorldPosition(int32 component, CVector &pos);
	bool IsComponentPresent(int32 component);
	void SetComponentRotation(int32 component, CVector rotation);
	void OpenDoor(int32 component, eDoors door, float openRatio);
	void ProcessOpenDoor(uint32, uint32, float);
	bool IsDoorReady(eDoors door);
	bool IsDoorFullyOpen(eDoors door);
	bool IsDoorClosed(eDoors door);
	bool IsDoorMissing(eDoors door);
	void RemoveRefsToVehicle(CEntity *ent);
	void BlowUpCar(CEntity *ent);
	bool SetUpWheelColModel(CColModel *colModel);
	void BurstTyre(uint8 tyre);
	bool IsRoomForPedToLeaveCar(uint32, CVector *);
	float GetHeightAboveRoad(void);
	void PlayCarHorn(void);

	void ProcessSwingingDoor(int32 component, eDoors door);
	void ResetSuspension(void);
	void SetupDamageAfterLoad(void);
	CObject *SpawnFlyingComponent(int32 component, uint32 type);
	CObject *RemoveBonnetInPedCollision(void);
	void SetPanelDamage(int32 component, ePanels panel, bool noFlyingComponents = false);
	void SetBumperDamage(int32 component, ePanels panel, bool noFlyingComponents = false);
	void SetDoorDamage(int32 component, eDoors door, bool noFlyingComponents = false);

	void Fix(void);
	void SetComponentVisibility(RwFrame *frame, uint32 flags);
	void SetupModelNodes(void);
	void SetTaxiLight(bool light);
	bool GetAllWheelsOffGround(void);
	void HideAllComps(void);
	void ShowAllComps(void);
	void ReduceHornCounter(void);

	static void SetAllTaxiLights(bool set);

	CAutomobile* ctor(int, uint8);
};
static_assert(sizeof(CAutomobile) == 0x5A8, "CAutomobile: error");
