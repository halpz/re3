#include "common.h"
#include "main.h"
#include "rwcore.h"
#include "rwplcore.h"
#include "CutsceneShadow.h"
#include "RwHelper.h"

#define DLIGHT_VALUE        0.8f /* Directional light intensity */


CCutsceneShadow::CCutsceneShadow()
{	
	m_pAtomic = nil;
	m_nRwObjectType = -1;
	m_pLight = nil;
	m_nBlurPasses = 0;
	m_bResample = false;
	m_bGradient = false;
}

CCutsceneShadow::~CCutsceneShadow()
{
	Destroy();
}

bool
CCutsceneShadow::Create(RwObject *object, int32 rasterSize, bool resample, int32 blurPasses, bool gradient)
{
	ASSERT(object != nil);
	
	RwRGBAReal color;
	RwFrame *frame;

	if (!object)
		return false;

	m_pLight = RpLightCreate(rpLIGHTDIRECTIONAL);
	ASSERT(m_pLight != nil);
	
	if (!m_pLight)
		return false;

	color.red = color.green = color.blue = DLIGHT_VALUE;
	color.alpha = 0.0f;
	
	RpLightSetColor(m_pLight, &color);
	
	frame = RwFrameCreate();
	ASSERT(frame != nil);
	
	RpLightSetFrame(m_pLight, frame);
	
	SetLightProperties(180.0f, 90.0f, false);

	m_pObject = object;
	m_nRwObjectType = RwObjectGetType(m_pObject);
	
	switch ( m_nRwObjectType )
	{
		case rpCLUMP:
		{
			RpClumpGetBoundingSphere(m_pClump, &m_BoundingSphere, 1);
			m_BaseSphere.radius = m_BoundingSphere.radius;
			RwV3dTransformPoints(&m_BaseSphere.center, &m_BoundingSphere.center, 1, RwFrameGetMatrix(RpClumpGetFrame(m_pClump)));
			break;
		}

		case rpATOMIC:
		{
			m_BoundingSphere = *RpAtomicGetBoundingSphere(m_pAtomic);
			m_BaseSphere.radius = m_BoundingSphere.radius;
			RwV3dTransformPoints(&m_BaseSphere.center, &m_BoundingSphere.center, 1, RwFrameGetMatrix(RpAtomicGetFrame(m_pAtomic)));
			break;
		}

		default:
		{
			Destroy();
			return false;
			break;
		}
	}

	if ( !m_Camera.Create(rasterSize) )
	{
		Destroy();
		return false;
	}
  
	m_nBlurPasses = blurPasses;
	m_bResample = resample;
	m_bGradient = gradient;

	if ( m_bResample && !m_ResampleCamera.Create(rasterSize - 1) )
	{
		Destroy();
		return false;
	}
  
	if ( m_nBlurPasses != 0 )
	{
		if ( !m_BlurCamera.Create(resample ? rasterSize - 1 : rasterSize) )
		{
			Destroy();
			return false;
		}
	}
  
	if ( m_bGradient )
	{
		if ( !m_GradientCamera.Create(resample ? rasterSize - 1 : rasterSize) )
		{
			Destroy();
			return false;
		}
		
		m_GradientCamera.MakeGradientRaster();
	}
  
	m_Camera.SetLight(m_pLight);
  
	switch ( m_nRwObjectType )
	{
		case rpATOMIC:
			m_Camera.SetFrustum(1.1f * m_BoundingSphere.radius);
			break;
			
		case rpCLUMP:
			m_Camera.SetFrustum(1.1f * m_BoundingSphere.radius);
			break;
	}
  
	m_Camera.SetCenter(&m_BaseSphere.center);
	return true;
}

RwFrame *
CCutsceneShadow::SetLightProperties(float angleY, float angleX, bool setLight)
{
	ASSERT(m_pLight != nil);
	
	RwFrame *frame;
	static RwV3d        Xaxis = { 1.0f, 0.0f, 0.0f };
	static RwV3d        Yaxis = { 0.0f, 1.0f, 0.0f };

	frame = RpLightGetFrame(m_pLight);
	ASSERT(frame != nil);
	
	if ( !frame )
		return nil;
	
	RwFrameRotate(frame, &Yaxis, angleY, rwCOMBINEREPLACE);
	RwFrameRotate(frame, &Xaxis, angleX, rwCOMBINEPOSTCONCAT);
	
	if ( setLight )
		m_Camera.SetLight(m_pLight);
		
	return frame;
}

bool
CCutsceneShadow::IsInitialized()
{
	return m_pObject != nil;
}

void
CCutsceneShadow::Destroy()
{
	m_Camera.Destroy();
	m_ResampleCamera.Destroy();
	m_BlurCamera.Destroy();
	m_GradientCamera.Destroy();
	
	m_pAtomic = nil;
	
	m_nRwObjectType = -1;
  
	if (m_pLight)
	{
		RwFrame *frame = RpLightGetFrame(m_pLight);
		RpLightSetFrame(m_pLight, nil);
		RwFrameDestroy(frame);
		RpLightDestroy(m_pLight);
		m_pLight = nil;
	}
}

RwRaster *
CCutsceneShadow::Update()
{
	switch ( m_nRwObjectType )
	{
		case rpCLUMP:
			ASSERT(m_pClump != nil);
			RwV3dTransformPoints(&m_BaseSphere.center, &m_BoundingSphere.center, 1, RwFrameGetMatrix(RpClumpGetFrame(m_pClump)));
			break;

		case rpATOMIC:
			ASSERT(m_pAtomic != nil);
			RwV3dTransformPoints(&m_BaseSphere.center, &m_BoundingSphere.center, 1, RwFrameGetMatrix(RpAtomicGetFrame(m_pAtomic)));
			break;
	}

	m_Camera.SetCenter(&m_BaseSphere.center);

	switch ( m_nRwObjectType )
	{
		case rpCLUMP:
			m_Camera.Update(m_pClump);
			break;

		case rpATOMIC:
			m_Camera.Update(m_pAtomic);
			break;
	}
	
	RwRaster *raster = m_Camera.GetRwRenderRaster();
	ASSERT(raster != nil);

	if ( m_bResample )
		return m_ResampleCamera.RasterResample(raster);

	if ( m_nBlurPasses )
		return m_BlurCamera.RasterBlur(raster, m_nBlurPasses);

	if ( m_bGradient )
		return m_GradientCamera.RasterGradient(raster);
	
	return raster;
}

RwTexture *
CCutsceneShadow::UpdateForCutscene()
{
	Update();
	return GetShadowRwTexture();
}

CShadowCamera *
CCutsceneShadow::GetShadowCamera(int32 camType)
{
	switch ( camType )
	{
		case RESAMPLE: return &m_ResampleCamera;
		case BLUR:     return &m_BlurCamera;    
		case GRADIENT: return &m_GradientCamera;
	}
	
	return &m_Camera;
}

RwTexture *
CCutsceneShadow::GetShadowRwTexture()
{
	if ( m_bResample )
		return m_ResampleCamera.GetRwRenderTexture();
	else
		return m_Camera.GetRwRenderTexture();
}

void
CCutsceneShadow::DrawBorderAroundTexture(RwRGBA  const& color)
{
	if ( m_bResample )
		m_ResampleCamera.DrawOutlineBorder(color);
	else
		m_Camera.DrawOutlineBorder(color);
}