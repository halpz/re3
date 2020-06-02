#pragma once

enum eBikeNodes {
	BIKE_NODE_NONE,
	BIKE_CHASSIS,
	BIKE_FORKS_FRONT,
	BIKE_FORKS_REAR,
	BIKE_WHEEL_FRONT,
	BIKE_WHEEL_REAR,
	BIKE_MUDGUARD,
	BIKE_HANDLEBARS,
	BIKE_NUM_NODES
};

enum eBikePositions
{
	BIKE_POS_HEADLIGHTS,
	BIKE_POS_TAILLIGHTS,
	BIKE_POS_FRONTSEAT,
	BIKE_POS_BACKSEAT,
	BIKE_POS_EXHAUST
};

class CBike : public CVehicle
{
public:
	RwFrame *m_aBikeNodes[BIKE_NUM_NODES];
	bool m_bLeanMatrixCalculated;
	CMatrix m_leanMatrix;
	CVector wheelieNormal;
	CVector wheelieRight;
	tBikeHandlingData *pBikeHandling;
	int32 m_bikeAnimType;
	uint8 m_wheelStatus[2];
	CColPoint m_aWheelColPoints[4];
	float m_aSuspensionSpringRatio[4];
	float m_aSuspensionSpringRatioPrev[4];
	float m_aWheelTimer[4];
	float m_bike_unused1;
	eSkidmarkType m_aWheelSkidmarkType[2];
	bool m_aWheelSkidmarkBloody[2];
	bool m_aWheelSkidmarkUnk[2];
	float m_aWheelRotation[2];
	float m_aWheelSpeed[2];
	float m_aWheelPosition[2];
	float m_aWheelBasePosition[2];
	float m_aSuspensionSpringLength[4];
	float m_aSuspensionLineLength[4];
	float m_fHeightAboveRoad;
	float m_fTraction;
	float m_fRearForkLength;
	float m_fFrontForkY;
	float m_fFrontForkZ;
	float m_fFrontForkSlope;
	float m_fBikeSteerAngle;
	float m_fLeanLRAngle;
	float m_fLeanLRAngle2;
	float m_fLeanInput;
	uint32 field_478;
	uint32 field_47C;
	uint8 m_bike_unused2;
	uint8 unused[3];	// looks like padding..but for what?
	uint8 m_bike_flags;
	int16 m_doingBurnout;
	float m_fTireTemperature;
	float someAngle;
	uint32 field_490;
	float m_fFireBlowUpTimer;
	CPhysical *m_aGroundPhysical[4];
	CVector m_aGroundOffset[4];
	CEntity *m_pSetOnFireEntity;
	uint8 m_nWheelsOnGround;
	uint8 m_nDriveWheelsOnGround;
	uint8 m_nDriveWheelsOnGroundPrev;
	float m_fGasPedalAudio;
	tWheelState m_aWheelState[2];
};
