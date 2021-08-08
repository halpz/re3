#pragma once

#define DEFAULT_MAX_NUMBER_OF_PEDS 25.0f
#define DEFAULT_MAX_NUMBER_OF_PEDS_INTERIOR 40.0f
#define DEFAULT_MAX_NUMBER_OF_CARS 30.0f

class CIniFile
{
public:
	static void LoadIniFile();

	static float PedNumberMultiplier;
	static float CarNumberMultiplier;
};
