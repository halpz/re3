/*
 *
 * Data structures for the charse toolkit
 */

/***************************************************************************
 *                                                                         *
 * Module  : rtcharse.h                                                    *
 *                                                                         *
 * Purpose : Charset handling                                              *
 *                                                                         *
 **************************************************************************/

#ifndef RTCHARSE_H
#define RTCHARSE_H

/**
 * \defgroup rtcharset RtCharset
 * \ingroup 2dtools
 *
 * Character Set/Foot Toolkit for RenderWare.
 */

/****************************************************************************
 Includes
 */

#include <rwcore.h>

/****************************************************************************
 Global Types
 */

/* RWPUBLIC */

typedef struct RtCharsetDesc RtCharsetDesc;

/**
 * \ingroup rtcharset
 * \struct RtCharsetDesc
 * Holds information about a character set.
 */
struct RtCharsetDesc
{
    RwInt32             width;
                        /**< Pixel-width of each character.   */
    RwInt32             height;
                        /**< Pixel-height of each character.  */
    RwInt32             width_internal;
                        /**< Pixel-width used internally, this is usually width+1 to add a border */
    RwInt32             height_internal;
                        /**< Pixel-height used internally, this is usually height+1 to add a border */
    RwInt32             count;
                        /**< Number of characters in the set. */
    RwInt32             tilewidth;
                        /**< Width of raster in characters.   */
    RwInt32             tileheight;
                        /**< Height of raster in characters.  */

};

/**
 * \ingroup rtcharset
 * \ref RtCharset
 * typedef for a structure defining a character set (opaque).
 * \see RtCharsetCreate
 */
typedef RwRaster    RtCharset;

/* RWPUBLICEND */

/****************************************************************************
 Function prototypes
 */

/* RWPUBLIC */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

extern RwBool       RtCharsetOpen(void);
extern void         RtCharsetClose(void);

extern RtCharset   *RtCharsetPrint(RtCharset * charSet,
                                   const RwChar * string,
                                   RwInt32 x, RwInt32 y);
extern RtCharset   *RtCharsetPrintBuffered(RtCharset * charSet,
                                           const RwChar * string,
                                           RwInt32 x, RwInt32 y,
                                           RwBool hideSpaces);
extern RwBool       RtCharsetBufferFlush(void);

extern RtCharset   *RtCharsetSetColors(RtCharset * charSet,
                                       const RwRGBA * foreGround,
                                       const RwRGBA * backGround);
extern RtCharset   *RtCharsetGetDesc(RtCharset * charset,
                                     RtCharsetDesc * desc);

extern RtCharset   *RtCharsetCreate(const RwRGBA * foreGround,
                                    const RwRGBA * backGround);
extern RwBool       RtCharsetDestroy(RtCharset * charSet);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

/* RWPUBLICEND */

#endif                          /* RTCHARSE_H */
