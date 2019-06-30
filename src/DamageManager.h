#pragma once

#include "common.h"

class CDamageManager
{
public:

	enum {
		CAR_DOOR_BONNET = 0,
		CAR_DOOR_BUMPER,
		CAR_DOOR_LF,
		CAR_DOOR_RF,
		CAR_DOOR_LR,
		CAR_DOOR_RR
	};

	enum {
		PANEL_FL = 0,
		PANEL_FR,
		PANEL_RL,
		PANEL_RR,
		PANEL_WINDSHIELD,
		PANEL_FRONT,
		PANEL_BACK
	};

	struct PanelStatus {
		uint32 m_nPanelFrontLeftStatus : 4;
		uint32 m_nPanelFrontRightStatus : 4;
		uint32 m_nPanelBackLeftStatus : 4;
		uint32 m_nPanelBackRightStatus : 4;
		uint32 m_nWindshieldStatus : 4;
		uint32 m_nPanelFrontStatus : 4;
		uint32 m_nPanelBackStatus : 4;
	};

	float field_0;
	char m_bEngineStatus;
	char m_bWheelStatus[4];
	char m_bDoorStatus[7];
	uint32 m_abLightStatus;
	union{
		PanelStatus m_sPanelsStatus;
		uint32 m_abPanelsStatus;
	};
	char field_24;
	char field_25;
	char field_26;
	char field_27;

	void SetDoorStatus(int, unsigned int);
	unsigned int GetDoorStatus(int);
};