#pragma once

class COnscreenTimer
{
public:
	void ProcessForDisplay(void);
};

class CPlaceName
{
};

class CCurrentVehicle
{
};

class CPager
{
};

class CUserDisplay
{
public:
	static CPlaceName &PlaceName;
	static COnscreenTimer &OnscnTimer;
	static CPager &Pager;
	static CCurrentVehicle &CurrentVehicle;
};
