#pragma once

enum {
	STREAM_OFFSET_MODEL = 0,
	STREAM_OFFSET_TXD = STREAM_OFFSET_MODEL+MODELINFOSIZE,
	NUMSTREAMINFO = STREAM_OFFSET_TXD+TXDSTORESIZE
};

enum StreamFlags
{
	STREAM_DONT_REMOVE = 0x01,
	STREAM_SCRIPTOWNED = 0x02,
	STREAM_DEPENDENCY  = 0x04,
	STREAM_PRIORITY    = 0x08,
	STREAM_NOFADE      = 0x10,
};

enum StreamLoadState
{
	STREAM_NOTLOADED = 0,
	STREAM_LOADED    = 1,
	STREAM_INQUEUE   = 2,
	STREAM_READING   = 3,	// what is this?
	STREAM_BIGFILE   = 4,
};

class CStreamingInfo
{
public:
	CStreamingInfo *m_next;
	CStreamingInfo *m_prev;
	uint8 m_loadState;
	uint8 m_flags;

	int16  m_nextID;
	uint32 m_position;
	uint32 m_size;

//	bool GetCdPosnAndSize(uint32 *pos, uint32 *size);
//	void SetCdPosnAndSize(uint32 pos, uint32 size);
//	void AddToList(CStreamingInfo *link);
//	void RemoveFromList(void);
};

class CStreaming
{
public:
	static bool &ms_disableStreaming;
	static int32 &ms_numModelsRequested;
	static CStreamingInfo *ms_aInfoForModel;	//[NUMSTREAMINFO]

	static void RemoveModel(int32 id);
	static void RequestModel(int32 model, int32 flags);
	static void MakeSpaceFor(int32 size);
	static void ImGonnaUseStreamingMemory(void);
	static void IHaveUsedStreamingMemory(void);
	static void UpdateMemoryUsed(void);
};
