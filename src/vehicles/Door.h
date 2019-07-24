#pragma once

class CVehicle;

enum eDoorState
{
	DOORST_SWINGING,
	// actually wrong though,
	// OPEN is really MAX_ANGLE and CLOSED is MIN_ANGLE
	DOORST_OPEN,
	DOORST_CLOSED
};

struct CDoor
{
	float m_fMaxAngle;
	float m_fMinAngle;
	// direction of rotation for air resistance
	int8 m_nDirn;
	// axis in which this door rotates
	int8 m_nAxis;
	int8 m_nDoorState;
	float m_fAngle;
	float m_fPrevAngle;
	float m_fAngVel;
	CVector m_vecSpeed;

	CDoor(void);
	void Init(float minAngle, float maxAngle, int8 dir, int8 axis) {
		m_fMinAngle = minAngle;
		m_fMaxAngle = maxAngle;
		m_nDirn = dir;
		m_nAxis = axis;
	}
	void Open(float ratio);
	void Process(CVehicle *veh);
	float RetAngleWhenClosed(void);
	float RetAngleWhenOpen(void);
	float GetAngleOpenRatio(void);
	bool IsFullyOpen(void);
	bool IsClosed(void);
};
