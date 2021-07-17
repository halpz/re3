class RenderBuffer
{
public:
	static int VerticesToBeStored;
	static int IndicesToBeStored;
	static void ClearRenderBuffer(void);
	static void StartStoring(int numIndices, int numVertices, RwImVertexIndex **indexStart, RwIm3DVertex **vertexStart);
	static void StopStoring(void);
	static void RenderStuffInBuffer(void);
};

#define TEMPBUFFERVERTSIZE 512
#define TEMPBUFFERINDEXSIZE 1024

struct VertexBufferUnion
{
	RwIm2DVertex im2d[TEMPBUFFERVERTSIZE];
	RwIm3DVertex im3d[TEMPBUFFERVERTSIZE];
};

extern int32 TempBufferVerticesStored;
extern int32 TempBufferIndicesStored;
extern VertexBufferUnion TempVertexBuffer;
#define TempBufferRenderVertices (TempVertexBuffer.im3d)
extern RwImVertexIndex TempBufferRenderIndexList[TEMPBUFFERINDEXSIZE];