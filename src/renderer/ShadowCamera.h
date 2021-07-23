#pragma once


class CShadowCamera
{
public:
	RwCamera *m_pCamera;
	RwTexture *m_pTexture;
	
	CShadowCamera();
	~CShadowCamera();

	RwCamera *Create(int32 rasterSize);
	void Destroy();
	
	RwCamera *SetFrustum(float objectRadius);
	RwCamera *SetLight(RpLight *light);
	RwCamera *SetCenter(RwV3d *center);
	
	RwCamera *Update(RpClump *clump);
	RwCamera *Update(RpAtomic *atomic);
	
	void InvertRaster();
	
	RwRaster* GetRwRenderRaster()
	{
		return RwCameraGetRaster(m_pCamera);
	}
	
	// ShadowRasterRender(RwV2d *)
	// ApplyAlphaMapToRaster(void)
	
	RwRaster *MakeGradientRaster();
	
	RwTexture *GetRwRenderTexture()
	{
		return m_pTexture;
	}
	
	RwRaster* GetRwZRaster()
	{
		return RwCameraGetZRaster(m_pCamera);
	}
	
	RwRaster *RasterResample(RwRaster *dstRaster);
	RwRaster *RasterBlur(RwRaster *dstRaster, int32 numPasses);
	RwRaster *RasterGradient(RwRaster *dstRaster);
	RwRaster *DrawOutlineBorder(RwRGBA const& color);

	RwCamera *GetRwCamera()
	{
		return m_pCamera;
	}
};