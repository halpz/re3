#pragma once

class CSprite2d
{
	RwTexture *m_pTexture;

	static RwIm2DVertex *maVertices;	//[4];
public:
	static float &RecipNearClip;

	void SetRenderState(void);

	static void SetVertices(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3, uint32 far);
	static void SetVertices(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3,
		float u0, float v0, float u1, float v1, float u3, float v3, float u2, float v2);
	static void DrawRect(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3);
	static void DrawRect(const CRect &r, const CRGBA &col);
	static void DrawRectXLU(const CRect &r, const CRGBA &c0, const CRGBA &c1, const CRGBA &c2, const CRGBA &c3);
};

class CSprite
{
	static float &m_f2DNearScreenZ;
	static float &m_f2DFarScreenZ;
	static int32 &m_bFlushSpriteBufferSwitchZTest;
public:
	static float CalcHorizonCoors(void);
	static bool CalcScreenCoors(const RwV3d &in, RwV3d *out, float *outw, float *outh, bool farclip);
	static void InitSpriteBuffer(void);
	static void FlushSpriteBuffer(void);
	static void RenderOneXLUSprite(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, uint8 a);
	static void RenderBufferedOneXLUSprite(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, uint8 a);
	static void RenderBufferedOneXLUSprite_Rotate_Dimension(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, float roll, uint8 a);
	static void RenderBufferedOneXLUSprite_Rotate_Aspect(float x, float y, float z, float w, float h, uint8 r, uint8 g, uint8 b, int16 intens, float recipz, float roll, uint8 a);
	// cx/y is the direction in which the colour changes
	static void RenderBufferedOneXLUSprite_Rotate_2Colours(float x, float y, float z, float w, float h, uint8 r1, uint8 g1, uint8 b1, uint8 r2, uint8 g2, uint8 b2, float cx, float cy, float recipz, float rotation, uint8 a);
};
