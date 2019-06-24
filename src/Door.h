#pragma once

#include "common.h"

struct CDoor
{
	float m_fAngleWhenOpened;
	float m_fAngleWhenClosed;
	char field_8;
	char field_9;
	char field_10;
	char field_11;
	float m_fAngle;
	float m_fPreviousAngle;
	float m_fAngularVelocity;
	CVector m_vecVelocity;
};