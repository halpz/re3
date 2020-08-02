/***********************************************************************
 *
 * Module:  rtpitexd.h
 *
 * Purpose: Platform Independent Texture Dictionaries
 *
 ***********************************************************************/

#if !defined( RTPITEXD_H )
#define RTPITEXD_H

/**
 * \defgroup rtpitexd RtPITexD
 * \ingroup texturedictionaries
 *
 * Platform Independent Texture Dictionaries
 *
 */


/* =====================================================================
 *  Includes
 * ===================================================================== */
#include <rwcore.h>
#include <rtpitexd.rpe>     /* automatically generated */


/* =====================================================================
 *  Defines
 * ===================================================================== */


/* =====================================================================
 *  Module specific type definitions
 * ===================================================================== */

/* =====================================================================
 *  Extern variables
 * ===================================================================== */


/* =====================================================================
 *  Extern function prototypes
 * ===================================================================== */

#if defined( __cplusplus )
extern "C"
{
#endif /* defined( __cplusplus ) */

/* RWPUBLIC */

extern RwUInt32
RtPITexDictionaryStreamGetSize( const RwTexDictionary *texDict );

extern RwTexDictionary *
RtPITexDictionaryStreamRead( RwStream *stream );

extern RwTexDictionary *
RtPITexDictionaryStreamWrite( RwTexDictionary *texDict,
                              RwStream *stream );

/* RWPUBLICEND */

extern void
_rwImageGammaUnCorrectArrayOfRGBA( RwRGBA * rgbaOut,
                                   RwRGBA * rgbaIn,
                                   RwInt32 numEls );

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */

#endif /* !defined( RTPITEXD_H ) */
