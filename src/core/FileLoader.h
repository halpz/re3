#pragma once

class CFileLoader
{
	static char ms_line[256];
public:
	static void LoadLevel(const char *filename);
	static char *LoadLine(int fd);
	static RwTexDictionary *LoadTexDictionary(const char *filename);
	static void LoadCollisionFile(const char *filename, uint8 colSlot);
	static bool LoadCollisionFileFirstTime(uint8 *buffer, uint32 size, uint8 colSlot);
	static bool LoadCollisionFile(uint8 *buffer, uint32 size, uint8 colSlot);
	static void LoadCollisionModel(uint8 *buf, struct CColModel &model, char *name);
	static void SplitColTrianglesIntoSections(CColModel &model);
	static void LoadModelFile(const char *filename);
	static RpAtomic *FindRelatedModelInfoCB(RpAtomic *atomic, void *data);
	static void LoadClumpFile(const char *filename);
	static bool LoadClumpFile(RwStream *stream, uint32 id);
	static bool StartLoadClumpFile(RwStream *stream, uint32 id);
	static bool FinishLoadClumpFile(RwStream *stream, uint32 id);
	static bool LoadAtomicFile(RwStream *stream, uint32 id);
	static RpAtomic *SetRelatedModelInfoCB(RpAtomic *atomic, void *data);
	static RpClump *LoadAtomicFile2Return(const char *filename);
	static void AddTexDictionaries(RwTexDictionary *dst, RwTexDictionary *src);

	static void LoadObjectTypes(const char *filename);
	static int LoadObject(const char *line);
	static int LoadTimeObject(const char *line);
	static int LoadWeaponObject(const char *line);
	static void LoadClumpObject(const char *line);
	static void LoadVehicleObject(const char *line);
	static void LoadPedObject(const char *line);
	static int LoadPathHeader(const char *line, int &type);
	static void LoadPedPathNode(const char *line, int id, int node);
	static void LoadCarPathNode(const char *line, int id, int node, bool waterPath);
	static void Load2dEffect(const char *line);

	static void LoadScene(const char *filename);
	static void LoadObjectInstance(const char *line);
	static void LoadZone(const char *line);
	static void LoadCullZone(const char *line);
	static void LoadPickup(const char *line);
	static void LoadOcclusionVolume(const char *line);

	static void ReloadPaths(const char *filename);
	static void ReloadObjectTypes(const char *filename);
	static void ReloadObject(const char *line);
	static void ReLoadScene(const char *filename); // unused mobile function
};
