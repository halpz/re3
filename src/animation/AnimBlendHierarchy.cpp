#include "common.h"

#include "AnimBlendSequence.h"
#include "AnimBlendHierarchy.h"

CAnimBlendHierarchy::CAnimBlendHierarchy(void)
{
	sequences = nil;
	numSequences = 0;
	compressed = 0;
	totalLength = 0.0f;
	linkPtr = nil;
}

void
CAnimBlendHierarchy::Shutdown(void)
{
	RemoveAnimSequences();
	compressed = 0;
	linkPtr = nil;
}

void
CAnimBlendHierarchy::SetName(char *name)
{
	strncpy(this->name, name, 24);
}

void
CAnimBlendHierarchy::CalcTotalTime(void)
{
	int i, j;
	float totalTime = 0.0f;

	for(i = 0; i < numSequences; i++){
		float seqTime = 0.0f;
		for(j = 0; j < sequences[i].numFrames; j++)
			seqTime += sequences[i].GetKeyFrame(j)->deltaTime;
		totalTime = Max(totalTime, seqTime);
	}
	totalLength = totalTime;
}

void
CAnimBlendHierarchy::RemoveQuaternionFlips(void)
{
	int i;

	for(i = 0; i < numSequences; i++)
		sequences[i].RemoveQuaternionFlips();
}

void
CAnimBlendHierarchy::RemoveAnimSequences(void)
{
	if(sequences)
		delete[] sequences;
	numSequences = 0;
}

void
CAnimBlendHierarchy::Uncompress(void)
{
	if(totalLength == 0.0f)
		CalcTotalTime();
	compressed = 0;
}

void
CAnimBlendHierarchy::RemoveUncompressedData(void)
{
	// useless
	compressed = 1;
}
