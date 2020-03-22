#pragma once

class CVehicle;

class CRubbish
{
public:
	static void Render(void);
	static void StirUp(CVehicle *veh);	// CAutomobile on PS2
	static void Update(void);
	static void SetVisibility(bool);
	static void Init(void);
};
