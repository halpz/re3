#pragma once
#include "ShadowCamera.h"

class CCutsceneShadow
{
public:
	enum
	{
		RASTER = 0,
		RESAMPLE,
		BLUR,
		GRADIENT,
	};

	CShadowCamera m_Camera;
	bool          m_bResample;
	CShadowCamera m_ResampleCamera;
	int32         m_nBlurPasses;
	CShadowCamera m_BlurCamera;
	bool          m_bGradient;
	CShadowCamera m_GradientCamera;
	
	union
	{
		RwObject *m_pObject;
		RpAtomic *m_pAtomic;
		RpClump  *m_pClump;
	};
	
	int32    m_nRwObjectType;
	RpLight *m_pLight;
	RwSphere m_BoundingSphere;
	RwSphere m_BaseSphere;
	
	CCutsceneShadow();
	~CCutsceneShadow();
	
	RwSphere GetBaseSphere()
	{
		return m_BaseSphere;
	}

	bool Create(RwObject *object, int32 rasterSize, bool resample, int32 blurPasses, bool gradient);
	RwFrame *SetLightProperties(float angleY, float angleX, bool setLight);
	bool IsInitialized();
	void Destroy();
	RwRaster *Update();
	RwTexture *UpdateForCutscene();
	CShadowCamera *GetShadowCamera(int32 camType = RASTER);
	RwTexture *GetShadowRwTexture();
	void DrawBorderAroundTexture(RwRGBA  const& color);
};
