#pragma once

#include "templates.h"

class CAnimBlendSequence;

// A collection of sequences
class CAnimBlendHierarchy
{
public:
	char name[24];
	CAnimBlendSequence *sequences;
	int16 numSequences;
	int16 compressed;	// not really used
	float totalLength;
	CLink<CAnimBlendHierarchy*> *linkPtr;

	CAnimBlendHierarchy(void);
	void Shutdown(void);
	void SetName(char *name);
	void CalcTotalTime(void);
	void RemoveQuaternionFlips(void);
	void RemoveAnimSequences(void);
	void Uncompress(void);
	void RemoveUncompressedData(void);
};
static_assert(sizeof(CAnimBlendHierarchy) == 0x28, "CAnimBlendHierarchy: error");
