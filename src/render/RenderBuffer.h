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
