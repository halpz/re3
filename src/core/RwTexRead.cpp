#pragma warning( push )
#pragma warning( disable : 4005)
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma warning( pop )
#include "common.h"
#include "win.h"
#include "patcher.h"
#include "Timer.h"

float &texLoadTime = *(float*)0x8F1B50;
int32 &texNumLoaded = *(int32*)0x8F252C;

RwTexture*
RwTextureGtaStreamRead(RwStream *stream)
{
	RwUInt32 size, version;
	RwTexture *tex;

	if(!RwStreamFindChunk(stream, rwID_TEXTURENATIVE, &size, &version))
		return nil;

	float preloadTime = (float)CTimer::GetCurrentTimeInCycles() / (float)CTimer::GetCyclesPerMillisecond();

	if(!RWSRCGLOBAL(stdFunc[rwSTANDARDNATIVETEXTUREREAD](stream, &tex, size)))
		return nil;

	if (gGameState == GS_INIT_PLAYING_GAME) {
		texLoadTime = (texNumLoaded * texLoadTime + (float)CTimer::GetCurrentTimeInCycles() / (float)CTimer::GetCyclesPerMillisecond() - preloadTime) / (float)(texNumLoaded+1);
		texNumLoaded++;
	}
	return tex;
}

RwTexture*
destroyTexture(RwTexture *texture, void *data)
{
	RwTextureDestroy(texture);
	return texture;
}

RwTexDictionary*
RwTexDictionaryGtaStreamRead(RwStream *stream)
{
	RwUInt32 size, version;
	RwInt32 numTextures;
	RwTexDictionary *texDict;
	RwTexture *tex;

	if(!RwStreamFindChunk(stream, rwID_STRUCT, &size, &version))
		return nil;
	assert(size == 4);
	if(RwStreamRead(stream, &numTextures, size) != size)
		return nil;

	texDict = RwTexDictionaryCreate();
	if(texDict == nil)
		return nil;

	while(numTextures--){
		tex = RwTextureGtaStreamRead(stream);
		if(tex == nil){
			RwTexDictionaryForAllTextures(texDict, destroyTexture, nil);
			RwTexDictionaryDestroy(texDict);
			return nil;
		}
		RwTexDictionaryAddTexture(texDict, tex);
	}

	return texDict;
}

static int32 numberTextures = -1;
static int32 streamPosition;

RwTexDictionary*
RwTexDictionaryGtaStreamRead1(RwStream *stream)
{
	RwUInt32 size, version;
	RwInt32 numTextures;
	RwTexDictionary *texDict;
	RwTexture *tex;

	numberTextures = 0;
	if(!RwStreamFindChunk(stream, rwID_STRUCT, &size, &version))
		return nil;
	assert(size == 4);
	if(RwStreamRead(stream, &numTextures, size) != size)
		return nil;

	texDict = RwTexDictionaryCreate();
	if(texDict == nil)
		return nil;

	numberTextures = numTextures/2;

	while(numTextures > numberTextures){
		numTextures--;

		tex = RwTextureGtaStreamRead(stream);
		if(tex == nil){
			RwTexDictionaryForAllTextures(texDict, destroyTexture, nil);
			RwTexDictionaryDestroy(texDict);
			return nil;
		}
		RwTexDictionaryAddTexture(texDict, tex);
	}

	numberTextures = numTextures;
	streamPosition = stream->Type.memory.position;

	return texDict;
}

RwTexDictionary*
RwTexDictionaryGtaStreamRead2(RwStream *stream, RwTexDictionary *texDict)
{
	RwTexture *tex;

	RwStreamSkip(stream, streamPosition - stream->Type.memory.position);

	while(numberTextures--){
		tex = RwTextureGtaStreamRead(stream);
		if(tex == nil){
			RwTexDictionaryForAllTextures(texDict, destroyTexture, nil);
			RwTexDictionaryDestroy(texDict);
			return nil;
		}
		RwTexDictionaryAddTexture(texDict, tex);
	}

	return texDict;
}

STARTPATCHES
	InjectHook(0x592380, RwTextureGtaStreamRead, PATCH_JUMP);
	InjectHook(0x5924A0, RwTexDictionaryGtaStreamRead, PATCH_JUMP);
	InjectHook(0x592550, RwTexDictionaryGtaStreamRead1, PATCH_JUMP);
	InjectHook(0x592650, RwTexDictionaryGtaStreamRead2, PATCH_JUMP);
ENDPATCHES
