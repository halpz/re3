#pragma once

class CRestart
{
public:
	static void AddPoliceRestartPoint(const CVector&, float);
	static void AddHospitalRestartPoint(const CVector&, float);
	static void OverrideNextRestart(const CVector&, float);
};
