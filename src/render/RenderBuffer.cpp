#include "common.h"
#include "patcher.h"
#include "RenderBuffer.h"

int32 &TempBufferVerticesStored = *(int32*)0x8F5F78;
int32 &TempBufferIndicesStored = *(int32*)0x8F1A4C;

RwIm3DVertex *TempVertexBuffer = (RwIm3DVertex*)0x862330;
RwImVertexIndex *TempBufferRenderIndexList = (RwImVertexIndex*)0x846288;

int RenderBuffer::VerticesToBeStored;
int RenderBuffer::IndicesToBeStored;

void
RenderBuffer::ClearRenderBuffer(void)
{
	TempBufferVerticesStored = 0;
	TempBufferIndicesStored = 0;
}

void
RenderBuffer::StartStoring(int numIndices, int numVertices, RwImVertexIndex **indexStart, RwIm3DVertex **vertexStart)
{
	if(TempBufferIndicesStored + numIndices >= 1024)
		RenderStuffInBuffer();
	if(TempBufferVerticesStored + numVertices >= 256)
		RenderStuffInBuffer();
        *indexStart = &TempBufferRenderIndexList[TempBufferIndicesStored];
        *vertexStart = &TempVertexBuffer[TempBufferVerticesStored];
        IndicesToBeStored = numIndices;
        VerticesToBeStored = numVertices;
}

void
RenderBuffer::StopStoring(void)
{
	int i;
	for(i = TempBufferIndicesStored; i < TempBufferIndicesStored+IndicesToBeStored; i++)
		TempBufferRenderIndexList[i] += TempBufferVerticesStored;
	TempBufferIndicesStored += IndicesToBeStored;
	TempBufferVerticesStored += VerticesToBeStored;
}

void
RenderBuffer::RenderStuffInBuffer(void)
{
	if(TempBufferVerticesStored && RwIm3DTransform(TempVertexBuffer, TempBufferVerticesStored, nil, rwIM3D_VERTEXUV)){
		RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, TempBufferRenderIndexList, TempBufferIndicesStored);
		RwIm3DEnd();
	}
	ClearRenderBuffer();
}

STARTPATCHES
	InjectHook(0x517620, RenderBuffer::ClearRenderBuffer, PATCH_JUMP);
	InjectHook(0x517640, RenderBuffer::StartStoring, PATCH_JUMP);
	InjectHook(0x5176B0, RenderBuffer::StopStoring, PATCH_JUMP);
	InjectHook(0x5177C0, RenderBuffer::RenderStuffInBuffer, PATCH_JUMP);
ENDPATCHES
