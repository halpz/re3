#ifndef ALDEVICELIST_H
#define ALDEVICELIST_H

#include "oal_utils.h"

#ifdef AUDIO_OAL
#pragma warning(disable: 4786)  //disable warning "identifier was truncated to '255' characters in the browser information"
#include <vector>
#include <string>

typedef struct
{
	std::string			strDeviceName;
	int				iMajorVersion;
	int				iMinorVersion;
	unsigned int	uiSourceCount;
	std::vector<std::string>	*pvstrExtensions;
	bool			bSelected;
} ALDEVICEINFO, *LPALDEVICEINFO;

class ALDeviceList
{
private:
	std::vector<ALDEVICEINFO> vDeviceInfo;
	int defaultDeviceIndex;
	int filterIndex;

public:
	ALDeviceList ();
	~ALDeviceList ();
	int GetNumDevices();
	char *GetDeviceName(int index);
	void GetDeviceVersion(int index, int *major, int *minor);
	unsigned int GetMaxNumSources(int index);
	bool IsExtensionSupported(int index, char *szExtName);
	int GetDefaultDevice();
	void FilterDevicesMinVer(int major, int minor);
	void FilterDevicesMaxVer(int major, int minor);
	void FilterDevicesExtension(char *szExtName);
	void ResetFilters();
	int GetFirstFilteredDevice();
	int GetNextFilteredDevice();

private:
	unsigned int GetMaxNumSources();
};
#endif

#endif // ALDEVICELIST_H