#include "common.h"
#include "patcher.h"
#include "Vehicle.h"
#include "Door.h"

CDoor::CDoor(void)
{
	memset(this, 0, sizeof(*this));
}

void
CDoor::Open(float ratio)
{
	float open;

	m_fPrevAngle = m_fAngle;
	open = RetAngleWhenOpen();
	if(ratio < 1.0f){
		m_fAngle = open*ratio;
		if(m_fAngle == 0.0f)
			m_fAngVel = 0.0f;
	}else{
		m_nDoorState = DOORST_OPEN;
		m_fAngle = open;
	}
}

void
CDoor::Process(CVehicle *vehicle)
{
	static CVector vecOffset(1.0f, 0.0f, 0.0f);
	CVector speed = vehicle->GetSpeed(vecOffset);
	CVector vecSpeedDiff = speed - m_vecSpeed;
	vecSpeedDiff = Multiply3x3(vecSpeedDiff, vehicle->GetMatrix());

	// air resistance
	float fSpeedDiff = 0.0f;	// uninitialized in game
	switch(m_nAxis){
	case 0:	// x-axis
		if(m_nDirn)
			fSpeedDiff = vecSpeedDiff.y + vecSpeedDiff.z;
		else
			fSpeedDiff = -(vecSpeedDiff.y + vecSpeedDiff.z);
		break;

	// we don't support y axis apparently?

	case 2:	// z-axis
		if(m_nDirn)
			fSpeedDiff = -(vecSpeedDiff.x + vecSpeedDiff.y);
		else
			fSpeedDiff = vecSpeedDiff.x + vecSpeedDiff.y;
		break;
	}
	fSpeedDiff = clamp(fSpeedDiff, -0.2f, 0.2f);
	if(Abs(fSpeedDiff) > 0.002f)
		m_fAngVel += fSpeedDiff;
	m_fAngVel *= 0.945f;
	m_fAngVel = clamp(m_fAngVel, -0.3f, 0.3f);

	m_fAngle += m_fAngVel;
	m_nDoorState = DOORST_SWINGING;
	if(m_fAngle > m_fMaxAngle){
		m_fAngle = m_fMaxAngle;
		m_fAngVel *= -0.8f;
		m_nDoorState = DOORST_OPEN;
	}
	if(m_fAngle < m_fMinAngle){
		m_fAngle = m_fMinAngle;
		m_fAngVel *= -0.8f;
		m_nDoorState = DOORST_CLOSED;
	}
	m_vecSpeed = speed;
}

float
CDoor::RetAngleWhenClosed(void)
{
	if(Abs(m_fMaxAngle) < Abs(m_fMinAngle))
		return m_fMaxAngle;
	else
		return m_fMinAngle;
}

float
CDoor::RetAngleWhenOpen(void)
{
	if(Abs(m_fMaxAngle) < Abs(m_fMinAngle))
		return m_fMinAngle;
	else
		return m_fMaxAngle;
}

float
CDoor::GetAngleOpenRatio(void)
{
	float open = RetAngleWhenOpen();
	if(open == 0.0f)
		return 0.0f;
	return m_fAngle/open;
}

bool
CDoor::IsFullyOpen(void)
{
	// why -0.5? that's around 28 deg less than fully open
	if(Abs(m_fAngle) < Abs(RetAngleWhenOpen()) - 0.5f)
		return false;
	return true;
}

bool
CDoor::IsClosed(void)
{
	return m_fAngle == RetAngleWhenClosed();
}

STARTPATCHES
	InjectHook(0x545EF0, &CDoor::Open, PATCH_JUMP);
	InjectHook(0x545BD0, &CDoor::Process, PATCH_JUMP);
	InjectHook(0x545FE0, &CDoor::RetAngleWhenClosed, PATCH_JUMP);
	InjectHook(0x546020, &CDoor::RetAngleWhenOpen, PATCH_JUMP);
	InjectHook(0x545F80, &CDoor::GetAngleOpenRatio, PATCH_JUMP);
	InjectHook(0x546090, &CDoor::IsFullyOpen, PATCH_JUMP);
	InjectHook(0x546060, &CDoor::IsClosed, PATCH_JUMP);
ENDPATCHES
