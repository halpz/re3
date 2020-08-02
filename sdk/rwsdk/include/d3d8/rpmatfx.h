
#ifndef RPMATFX_H
#define RPMATFX_H

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/

#include "rwcore.h"
#include "rpworld.h"

/*---- start: ./matfx.h----*/

#ifndef RPMATFX_MATFX_H
#define RPMATFX_MATFX_H


/**
 * \defgroup rpmatfx RpMatFX
 * \ingroup materials
 *
 * Material Effects Plugin for RenderWare Graphics.
 */

/*===========================================================================*
 *--- Global Types ----------------------------------------------------------*
 *===========================================================================*/

/**
 * \ingroup rpmatfx
 * RpMatFXMaterialFlags, this type represents the different types of
 * material effects that can be used on a material. The effects are
 * initialized with \ref RpMatFXMaterialSetEffects:
 */
enum RpMatFXMaterialFlags
{
    rpMATFXEFFECTNULL       = 0,
    rpMATFXEFFECTBUMPMAP    = 1, /**<Bump mapping                 */
    rpMATFXEFFECTENVMAP     = 2, /**<Environment mapping          */
    rpMATFXEFFECTBUMPENVMAP = 3, /**<Bump and environment mapping */
    rpMATFXEFFECTDUAL       = 4, /**<Dual pass                    */

    rpMATFXEFFECTMAX,
    rpMATFXNUMEFFECTS       = rpMATFXEFFECTMAX - 1,

    rpMATFXFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpMatFXMaterialFlags  RpMatFXMaterialFlags;


/*===========================================================================*
 *--- Plugin API Functions --------------------------------------------------*
 *===========================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*--- Plugin functions ------------------------------------------------------*/
extern void
RpMatFXMaterialDataSetFreeListCreateParams( RwInt32 blockSize,
                                        RwInt32 numBlocksToPrealloc );

extern RwBool
RpMatFXPluginAttach( void );

/*--- Setup functions -------------------------------------------------------*/
extern RpAtomic *
RpMatFXAtomicEnableEffects( RpAtomic *atomic );

extern RwBool
RpMatFXAtomicQueryEffects( RpAtomic *atomic );

extern RpWorldSector *
RpMatFXWorldSectorEnableEffects( RpWorldSector *worldSector );

extern RwBool
RpMatFXWorldSectorQueryEffects( RpWorldSector *worldSector );

extern RpMaterial *
RpMatFXMaterialSetEffects( RpMaterial *material,
                           RpMatFXMaterialFlags flags );


/*--- Setup Effects ---------------------------------------------------------*/
extern RpMaterial *
RpMatFXMaterialSetupBumpMap( RpMaterial *material,
                             RwTexture *texture,
                             RwFrame *frame,
                             RwReal coef );

extern RpMaterial *
RpMatFXMaterialSetupEnvMap( RpMaterial *material,
                            RwTexture *texture,
                            RwFrame *frame,
                            RwBool useFrameBufferAlpha,
                            RwReal coef );

extern RpMaterial *
RpMatFXMaterialSetupDualTexture( RpMaterial *material,
                                 RwTexture *texture,
                                 RwBlendFunction srcBlendMode,
                                 RwBlendFunction dstBlendMode );

/*--- Tinker with effects ---------------------------------------------------*/
extern RpMatFXMaterialFlags
RpMatFXMaterialGetEffects( const RpMaterial *material );

/*--- Bump Map --------------------------------------------------------------*/
extern RpMaterial *
RpMatFXMaterialSetBumpMapTexture( RpMaterial *material,
                                  RwTexture *texture );

extern RpMaterial *
RpMatFXMaterialSetBumpMapFrame( RpMaterial *material,
                                RwFrame *frame );

extern RpMaterial *
RpMatFXMaterialSetBumpMapCoefficient( RpMaterial *material,
                                      RwReal coef );
extern RwTexture *
RpMatFXMaterialGetBumpMapTexture( const RpMaterial *material );

extern RwTexture *
RpMatFXMaterialGetBumpMapBumpedTexture( const RpMaterial *material );

extern RwFrame *
RpMatFXMaterialGetBumpMapFrame( const RpMaterial *material );

extern RwReal
RpMatFXMaterialGetBumpMapCoefficient( const RpMaterial *material );

/*--- Env Map ---------------------------------------------------------------*/
extern RpMaterial *
RpMatFXMaterialSetEnvMapTexture( RpMaterial *material,
                                 RwTexture *texture );

extern RpMaterial *
RpMatFXMaterialSetEnvMapFrame( RpMaterial *material,
                               RwFrame *frame );

extern RpMaterial *
RpMatFXMaterialSetEnvMapFrameBufferAlpha( RpMaterial *material,
                                          RwBool useFrameBufferAlpha );

extern RpMaterial *
RpMatFXMaterialSetEnvMapCoefficient( RpMaterial *material,
                                     RwReal coef );

extern RwTexture *
RpMatFXMaterialGetEnvMapTexture( const RpMaterial *material );

extern RwFrame *
RpMatFXMaterialGetEnvMapFrame( const RpMaterial *material );

extern RwBool
RpMatFXMaterialGetEnvMapFrameBufferAlpha( const RpMaterial *material );

extern RwReal
RpMatFXMaterialGetEnvMapCoefficient( const RpMaterial *material );

/*--- Dual Pass -------------------------------------------------------------*/
extern RpMaterial *
RpMatFXMaterialSetDualTexture( RpMaterial *material,
                               RwTexture *texture );

extern RpMaterial *
RpMatFXMaterialSetDualBlendModes( RpMaterial *material,
                                  RwBlendFunction srcBlendMode,
                                  RwBlendFunction dstBlendMode );

extern RwTexture *
RpMatFXMaterialGetDualTexture( const RpMaterial *material );

extern const RpMaterial *
RpMatFXMaterialGetDualBlendModes( const RpMaterial *material,
                                  RwBlendFunction *srcBlendMode,
                                  RwBlendFunction *dstBlendMode );
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* RPMATFX_MATFX_H */

/*---- end: ./matfx.h----*/

/*---- start: c:/daily/rwsdk/plugin/matfx/d3d8/matfxplatform.h----*/

/**
 * \defgroup rpmatfxd3d8 D3D8
 * \ingroup rpmatfx
 *
 * D3D8 specific documentation.
 */


/******************************************************************************
 *  Enum types
 */

/**
 * \ingroup rpmatfxd3d8
 * \ref RpMatFXD3D8Pipeline
 */
enum RpMatFXD3D8Pipeline
{
    rpNAMATFXD3D8PIPELINE          = 0,
    rpMATFXD3D8ATOMICPIPELINE      = 1, /**<D3D8 atomic material effect rendering pipeline. */
    rpMATFXD3D8WORLDSECTORPIPELINE = 2, /**<D3D8 world sector material effect rendering pipeline. */
    rpMATFXD3D8PIPELINEMAX,
    rpMATFXD3D8PIPELINEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};
typedef enum RpMatFXD3D8Pipeline RpMatFXD3D8Pipeline;

/******************************************************************************
 *  Global types
 */

/******************************************************************************
 *  Functions
 */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern RxPipeline *
RpMatFXGetD3D8Pipeline( RpMatFXD3D8Pipeline d3d8Pipeline );

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*---- end: c:/daily/rwsdk/plugin/matfx/d3d8/matfxplatform.h----*/

#endif /* RPMATFX_H */


