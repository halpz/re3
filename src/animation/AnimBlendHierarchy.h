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
	bool compressed;	// not really used
	bool compressed2;	// not really used
	float totalLength;
	CLink<CAnimBlendHierarchy*> *linkPtr;

	CAnimBlendHierarchy(void);
	void Shutdown(void);
	void SetName(char *name);
	void CalcTotalTime(void);
	void CalcTotalTimeCompressed(void);
	void RemoveQuaternionFlips(void);
	void RemoveAnimSequences(void);
	void Uncompress(void);
	void RemoveUncompressedData(void);
	bool IsCompressed() { return !!compressed; };
};

VALIDATE_SIZE(CAnimBlendHierarchy, 0x28);