/*
 * Data structures for 2d toolkit
 *
 * Copyright (c) Criterion Software Limited
 */

/***************************************************************************
 *                                                                         *
 * Module  : rt2d.h                                                        *
 *                                                                         *
 * Purpose :                                                               *
 *                                                                         *
 **************************************************************************/

#ifndef RT2D_H
#define RT2D_H

/**
 * \defgroup rt2d Rt2d
 * \ingroup 2dtools
 *
 * 2D Rendering Toolkit for RenderWare.
 */

/**
 * \defgroup rt2ddatatypes Data Types
 * \ingroup rt2d
 *
 * Basic Data Types
 */

/**
 * \defgroup rt2dsub Rt2d
 * \ingroup rt2d
 *
 * Rt2d functions
 */

/**
 * \defgroup rt2dbrush Rt2dBrush
 * \ingroup rt2d
 *
 * Brush functions
 */

/**
 * \defgroup rt2dctm Rt2dCTM
 * \ingroup rt2d
 *
 * Current Transformation Matrix (CTM)
 */

/**
 * \defgroup rt2ddevice Rt2dDevice
 * \ingroup rt2d
 *
 * Camera device functions
 */

/**
 * \defgroup rt2dfont Rt2dFont
 * \ingroup rt2d
 *
 * Font functions
 */

/**
 * \defgroup rt2dobject Rt2dObject
 * \ingroup rt2d
 *
 * Objects
 */

/**
 * \defgroup rt2dobjectstring Rt2dObjectString
 * \ingroup rt2d
 *
 * String functions
 */

/**
 * \defgroup rt2dpath Rt2dPath
 * \ingroup rt2d
 *
 * Path functions
 */

/**
 * \defgroup rt2dpickregion Rt2dPickRegion
 * \ingroup rt2d
 *
 * Pick regions
 */

/**
 * \defgroup rt2dscene Rt2dScene
 * \ingroup rt2d
 *
 * Scenes
 */

/**
 * \defgroup rt2dshape Rt2dShape
 * \ingroup rt2d
 *
 * Shapes
 */

/**
 * \defgroup rt2drwv2d RwV2d
 * \ingroup rt2d
 *
 * Rt2d plugin directly extends the Core Library's RwV2d API functions.
 */

/****************************************************************************
 Includes
 */

#include "rpworld.h"
#include "rt2d.rpe"            /* automatically generated header file */

/****************************************************************************
 Defines
 */

#define Rt2dBrushSetWidthMacro(_brush, _width)                          \
     ( ( (_brush)->halfwidth = ((_width) * 0.5f) ), (_brush) )

#define Rt2dBrushGetWidthMacro(_brush)                                  \
    ( (_brush)->halfwidth * 2.0f )

#define Rt2dCTMReadMacro(_result)                                       \
    (RwMatrixCopy((_result), _rt2dCTMGet()), (_result))

#if defined (GCN_DRVMODEL_H)
    #define VERTEXCACHESIZE 64
#else
    #define VERTEXCACHESIZE 256
#endif


/****************************************************************************
 Global Types
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

/*
 * rt2dShadeParameters
 * typedef for a structure describing Shade Parameters
 */
typedef struct rt2dShadeParameters rt2dShadeParameters;

/*
 *
 * rt2dShadeParameters
 * describes Shade Parameters
 */

#if (!defined(DOXYGEN))
struct rt2dShadeParameters
{
    RwRGBAReal          col;    /* col */
    RwV2d               uv;     /* uv */
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rt2ddatatypes
 * \struct Rt2dBrush
 * Brush object.
 * This should be considered an opaque type.
 * Use Rt2dBrush API functions to access.
 */
typedef struct Rt2dBrush Rt2dBrush;

/*
 * Rt2dBrush
 * structure describing a Brush
 */
#if (!defined(DOXYGEN))
struct Rt2dBrush
{
    rt2dShadeParameters top;
    rt2dShadeParameters dtop;
    rt2dShadeParameters bottom;
    rt2dShadeParameters dbottom;
    RwRGBA              colorCache;
    RwInt32             flag;
    RwTexture          *texture;
    RpMaterial         *material;
    RwReal              halfwidth;
    RwInt32             refCount;
};
#endif /* (!defined(DOXYGEN)) */

/**
 * \ingroup rt2ddatatypes
 * \struct Rt2dPath
 * Path object.
 * This should be considered an opaque type.
 * Use Rt2dPath API functions to access.
 */
typedef struct Rt2dPath Rt2dPath;

/**
 * \ingroup rt2ddatatypes
 * \struct Rt2dFont
 * Font object.
 * This should be considered an opaque type.
 * Use Rt2dFont API functions to access.
 */
typedef struct Rt2dFont Rt2dFont;

/*
 * typedef used for referencing a spot in a font dictionary
 */
typedef struct _rt2dFontDictionaryNode _rt2dFontDictionaryNode;


typedef struct Rt2dBBox Rt2dBBox;
/**
* \ingroup rt2ddatatypes
 * \struct Rt2dBBox
 * structure describing a Bounding Box
 */
struct Rt2dBBox
{
    RwReal              x;  /**< x-coordinate of lower-left corner */
    RwReal              y;  /**< y-coordinate of lower-left corner */
    RwReal              w;  /**< Width */
    RwReal              h;  /**< Height */
};

/**
  * \ingroup rt2ddatatypes
  * \struct Rt2dObject
  * Structure describing a 2d Object
  * This should be considered an opaque type.
  * Use Rt2dObject, Rt2dScene, Rt2dShape, Rt2dPickRegion or Rt2dObjectString
  * API functions to access.
  */
typedef struct Rt2dObject Rt2dObject;

/*
 * typedef for a structure describing a scene of shapes (opaque)
 */
typedef struct _rt2dScene _rt2dScene;

/*
 * typedef for a structure describing the depth of an object
 */
typedef struct _rt2dDepthOfObject _rt2dDepthOfObject;

#if (!defined(DOXYGEN))
/*
 * typedef for a structure describing the depth of an object
 */
struct _rt2dDepthOfObject
{
    Rt2dObject *object;
    RwInt32 depth;
};

/*
 * structure describing a scene of shapes
 */
struct _rt2dScene
{
    RwSList  *objects;       /* collection of objects in scene */
    RwInt32   objectCount;   /* number of objects  */
    RwSList  *depths;        /* depths for depthsort */
    RwBool    isDirtyDepths; /* depthsort needs updating */
};
#endif /* (!defined(DOXYGEN)) */

/*
 * typedef for a structure describing a shape (opaque)
 */
typedef struct _rt2dShape _rt2dShape;

#if (!defined(DOXYGEN))
typedef struct _rt2dShapeRep _rt2dShapeRep;
struct _rt2dShapeRep
{
    RwSList     *nodes;         /* individual stroked/filled regions of the shape */
    RwUInt32     refCount;      /* number of shapes referencing this rep */
    RpGeometry  *geometry;      /* Shareable geometry */
};

extern _rt2dShapeRep *
 _rt2dShapeRepCreate();

extern RwBool
_rt2dShapeRepDestroy(_rt2dShapeRep *);

extern RwUInt32
_rt2dShapeRepAddRef(_rt2dShapeRep *);

typedef struct _rt2dSceneResourcePool _rt2dSceneResourcePool;
struct _rt2dSceneResourcePool
{
    _rt2dShapeRep **shapeReps;
    RwUInt32        numShapeReps;
};

extern RwBool
_rt2dSceneResourcePoolFindShapeRep(const _rt2dSceneResourcePool * pool,
                              const _rt2dShapeRep * rep, RwInt32 * npIndex);

struct _rt2dShape
{
    _rt2dShapeRep *rep;
    RwRGBA        *colorCache;    /* Shape's color cache */
    RpAtomic      *atomic;        /* Atomic repn */
};

/*
 * typedef for a structure describing a pick region that can be tested for point inclusion (opaque)
 */
typedef struct _rt2dPickRegion _rt2dPickRegion;

/*
 * structure describing a pick region that can be tested for point inclusion
 */
struct _rt2dPickRegion
{
    Rt2dPath     *path;    /* path that defines region for testing */
    Rt2dBBox     bbox;     /* bounding box of path */
    RwMatrix    transformation;
    /* ivnert transformation used to place the pick region */
};

/*
 * structure describing a renderable text string
 */

struct _rt2dObjectString
{
    RwChar    *textString; /* Text string to be rendered */
    Rt2dBrush *brush;      /* Brush to be used to draw text */
    RwInt32   maxLength;   /* Maximum string length before reallocation, excluding null */
    RwReal    height;      /* Font rendering Height */
    _rt2dFontDictionaryNode *font; /* Dictionary node identifying font to be used */
};
#endif /* (!defined(DOXYGEN)) */

/*
 * typedef for a renderable string
 */
typedef struct _rt2dObjectString _rt2dObjectString;
/**
 * \ingroup rt2ddatatypes
 * \ref Rt2dObjectTypeEnum
 * enumeration describing types of Rt2dObject
 */
enum Rt2dObjectTypeEnum {
    rt2DOBJECTTYPEOBJECT=0,       /**<An untyped (yet) object */
    rt2DOBJECTTYPESCENE,          /**<Container of objects */
    rt2DOBJECTTYPESHAPE,          /**<Shape object       */
    rt2DOBJECTTYPEPICKREGION,     /**<Pick region object */
    rt2DOBJECTTYPEOBJECTSTRING,   /**<Text string object */
    rt2DOBJECTTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT /* Ensures sizeof(enum) == sizeof(RwInt32)) */
};

typedef union _rt2dObjectdata _rt2dObjectdata;

#if (!defined(DOXYGEN))
union _rt2dObjectdata
{
    _rt2dShape shape;
    _rt2dScene scene;
    _rt2dPickRegion pickRegion;
    _rt2dObjectString objectString;
};

/*
 * A base structure for forming a hierarchy of 2D shapes
 */

#define Rt2dObjectIsLocked          0x00000001
#define Rt2dObjectDirtyLTM          0x00000002
#define Rt2dObjectVisible           0x00000004
#define Rt2dObjectDirtyColor        0x00000008

#define Rt2dObjectStringGotNoFonts  0x01000000

struct Rt2dObject
{
    RwInt32         type;            /* tag identifying type of object */
    RwInt32         depth;           /* z-order of object under parent */
    RwInt32         flag;            /* ... */
    RwMatrix        MTM;             /* local transformation matrix for object */
    RwMatrix        LTM;             /* global transformation matrix for object */
    RwRGBAReal      colorMult;       /* color multiply applied to object  */
    RwRGBAReal      colorOffs;       /* color offset applied to object    */
    _rt2dObjectdata data;
};
#endif /* (!defined(DOXYGEN)) */


/**
 * \ingroup rt2ddatatypes
 * \ref Rt2dObjectCallBack
 * typedef for a callback on an object in a collection
 *
 * \param object is a specific object
 * \param parent is the containing scene
 * \param data is user data
 *
 * \return return value is ignored
 */
typedef Rt2dObject *(* Rt2dObjectCallBack)(Rt2dObject *object, Rt2dObject *parent, void *data);

/**
 * \ingroup rt2ddatatypes
 * \ref Rt2dFontCallBackRead
 * Rt2dFontCallBackRead represents the function used by Rt2dFontRead to read
 * the specified font from a disk file. This function should return a
 * pointer to the font to indicate success. The returned font is owned by
 * the Rt2d internal font dictionary, and is destroyed on calling
 * \ref Rt2dClose
 *
 * \param name is the name of the font to read
 *
 * \return return the font if successful, NULL otherwise
 *
 * \see Rt2dFontSetReadCallBack
 * \see Rt2dFontGetReadCallBack
 */
typedef Rt2dFont*(* Rt2dFontCallBackRead)(const RwChar *name);  

/**
 * \ingroup rt2ddatatypes
 * \ref Rt2dJustificationType
 * enumeration describing Justification
 */
enum Rt2dJustificationType
{
    rt2dJUSTIFYLEFT,   /**<Left-justification */
    rt2dJUSTIFYCENTER, /**<Center-justification */
    rt2dJUSTIFYRIGHT,  /**<Right-justification */
    rt2DJUSTIFICATIONTYPEFORCEENUMSIZEINT = RWFORCEENUMSIZEINT /* Ensures sizeof(enum) == sizeof(RwInt32)) */
};

/*
 * Rt2dObjectEnum
 * typedef for a enumeration describing an object type enclosed by Rt2dObject
 */
typedef enum Rt2dJustificationType Rt2dJustificationType;

/**
 * \ingroup rt2ddatatypes
 * \ref Rt2dShapeNodeFlag
 * Passed to \ref Rt2dShapeAddNode, these flags specify
 * the type and properties of the path.
 */
enum Rt2dShapeNodeFlag
{
    rt2dSHAPENODEFLAGNONE                   = 0x0000,
    rt2dSHAPENODEFLAGSOLID                  = 0x0001,     /**< Shape's node is a solid, not outline */
    rt2dSHAPENODEFLAGFORCEENUMSIZEINT       = RWFORCEENUMSIZEINT /* Ensure sizeof(enum) == sizeof(RwInt32) */
};


#if (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ))

#define Rt2dBrushSetWidth(_brush, _width)                               \
    Rt2dBrushSetWidthMacro(_brush, _width)

#define Rt2dBrushGetWidth(_brush)                                       \
    Rt2dBrushGetWidthMacro(_brush)

#define Rt2dCTMRead(_result)                                            \
   Rt2dCTMReadMacro(_result)

#endif /* (! ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )) */

/****************************************************************************
 Function prototypes
 */
extern void
Rt2dBrushSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern void
Rt2dFontSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern void
Rt2dFontDictNodeSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern void
Rt2dObjectSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern void
Rt2dPathSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

/*
 * INITIALIZE
 */
extern void
Rt2dOpen(RwCamera *cam);

extern void
Rt2dClose(void);

extern void
Rt2dTriVertSetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

extern void
Rt2dTriPolySetFreeListCreateParams( RwInt32 blockSize, RwInt32 numBlocksToPrealloc );

/*
 * PATHS
 */
extern Rt2dPath *
Rt2dPathCreate(void);

extern RwBool
Rt2dPathDestroy(Rt2dPath *path);

extern Rt2dPath *
Rt2dPathLock(Rt2dPath *path);

extern Rt2dPath *
Rt2dPathUnlock(Rt2dPath *path);

extern RwBool
Rt2dPathIsLocked(Rt2dPath *path);

extern RwUInt32
Rt2dPathStreamGetSize(Rt2dPath *path);

extern Rt2dPath *
Rt2dPathStreamWrite(Rt2dPath *path, RwStream *stream);

extern Rt2dPath *
Rt2dPathStreamRead(RwStream *stream);

extern Rt2dPath *
Rt2dPathEmpty(Rt2dPath *path);

extern Rt2dPath *
Rt2dPathCopy(Rt2dPath *dst, const Rt2dPath *src);

extern Rt2dPath *
Rt2dPathInset(Rt2dPath *path, RwReal inset);

extern Rt2dPath *
Rt2dPathMoveto(Rt2dPath *path, RwReal x, RwReal y);

extern Rt2dPath *
Rt2dPathLineto(Rt2dPath *path, RwReal x, RwReal y);

extern Rt2dPath *
Rt2dPathRLineto(Rt2dPath *path, RwReal x, RwReal y);

extern Rt2dPath *
Rt2dPathCurveto(Rt2dPath *path, RwReal x1, RwReal y1, RwReal x2, RwReal y2, RwReal x3, RwReal y3);

extern Rt2dPath *
Rt2dPathRCurveto(Rt2dPath *path, RwReal x1, RwReal y1, RwReal x2, RwReal y2, RwReal x3, RwReal y3);

extern Rt2dPath *
Rt2dPathClose(Rt2dPath *path);

extern Rt2dPath *
Rt2dPathRect(Rt2dPath *path, RwReal x, RwReal y, RwReal w, RwReal h);

extern Rt2dPath *
Rt2dPathRoundRect(Rt2dPath *path, RwReal x, RwReal y, RwReal w, RwReal h, RwReal radius);

extern Rt2dPath *
Rt2dPathOval(Rt2dPath *path, RwReal x, RwReal y, RwReal w, RwReal h);

extern Rt2dPath *
Rt2dPathFlatten(Rt2dPath *path);

extern const Rt2dPath *
Rt2dPathGetBBox(const Rt2dPath *path, Rt2dBBox *bbox);

extern Rt2dPath *
Rt2dPathCreateMorphResultPath(Rt2dPath *path);

extern Rt2dPath *
Rt2dPathMorph(Rt2dPath *result, Rt2dPath *source, Rt2dPath *destination, RwReal alpha);

/*
 * BRUSHES
 */
extern Rt2dBrush *
Rt2dBrushCreate(void);

extern RwBool
Rt2dBrushDestroy(Rt2dBrush * brush);

extern Rt2dBrush *
Rt2dBrushSetRGBA(Rt2dBrush *brush, RwRGBA * col0, RwRGBA * col1, RwRGBA * col2, RwRGBA * col3);

extern Rt2dBrush *
Rt2dBrushSetUV(Rt2dBrush *brush, RwV2d *uv0, RwV2d *uv1, RwV2d *uv2, RwV2d *uv3);

extern Rt2dBrush *
Rt2dBrushSetTexture(Rt2dBrush* brush, RwTexture* texture);

extern RwUInt32
Rt2dBrushStreamGetSize(Rt2dBrush *brush);

extern Rt2dBrush *
Rt2dBrushStreamWrite(Rt2dBrush *brush, RwStream *stream);

extern Rt2dBrush *
Rt2dBrushStreamRead(RwStream *stream);

/*
 * FONTS
 */
extern const RwChar *
Rt2dFontSetPath(const RwChar *path);

extern Rt2dFont *
Rt2dFontRead(const RwChar *name);

extern RwBool
Rt2dFontSetReadCallBack(Rt2dFontCallBackRead fpCallBack);
 
extern Rt2dFontCallBackRead
Rt2dFontGetReadCallBack (void); 

extern RwUInt32
_rt2dFontStreamGetSize(Rt2dFont *font);

extern Rt2dFont *
_rt2dFontStreamWrite(Rt2dFont *font, RwStream *stream);

extern Rt2dFont *
_rt2dFontStreamRead(RwStream *stream);

extern RwBool
Rt2dFontDestroy(Rt2dFont *font);

extern RwReal
Rt2dFontGetHeight(Rt2dFont *font);

extern RwReal
Rt2dFontGetStringWidth(Rt2dFont *font, const RwChar *string, RwReal height);

extern Rt2dFont *
Rt2dFontShow(Rt2dFont *font, const RwChar *string, RwReal height, RwV2d *anchor, Rt2dBrush *brush);

extern Rt2dFont *
Rt2dFontFlow(Rt2dFont* font, RwChar* string, RwReal height, Rt2dBBox* bbox, Rt2dJustificationType format, Rt2dBrush* brush);

extern Rt2dFont *
Rt2dFontSetIntergapSpacing(Rt2dFont *font, RwReal gap);


extern RwBool
Rt2dFontCacheFlush(void);


/*
 * FILLING
 */
extern Rt2dPath *
Rt2dPathFill(Rt2dPath *path, Rt2dBrush *brush);
/*
 * STROKING
 */
extern Rt2dPath *
Rt2dPathStroke(Rt2dPath *path, Rt2dBrush *brush);

/*
 * TRANSFORMS
 */
extern RwBool
Rt2dCTMPush(void);

extern RwBool
Rt2dCTMPop(void);

extern RwBool
Rt2dCTMSetIdentity(void);

extern RwBool
Rt2dCTMScale(RwReal x, RwReal y);

extern RwBool
Rt2dCTMTranslate(RwReal x, RwReal y);

extern RwBool
Rt2dCTMRotate(RwReal theta);

extern RwBool
RwV2dIsInPath(RwV2d *point, Rt2dPath *path);

extern RwV2d *
RwV2dInvertTransform(RwV2d *pointOut, RwV2d *pointIn);


/*
 * DEVICE SETTINGS
 */
extern RwBool
Rt2dDeviceSetCamera(RwCamera *cam);

extern RwCamera *
Rt2dDeviceGetCamera(void);

extern RwBool
Rt2dDeviceGetStep(RwV2d *xstep, RwV2d *ystep, RwV2d *origin);

extern RwBool
Rt2dDeviceSetMetric(RwReal x, RwReal y, RwReal w, RwReal h);

extern RwBool
Rt2dDeviceGetMetric(RwReal *x, RwReal *y, RwReal *w, RwReal *h);

extern RwBool
Rt2dDeviceSetFlat(RwReal r);

extern RwBool
Rt2dDeviceGetClippath(Rt2dPath *path);

extern RwBool
Rt2dVisible(RwReal x, RwReal y, RwReal w, RwReal h);

extern RwBool
Rt2dDeviceSetLayerDepth(RwReal depth);

extern RwBool
Rt2dSetPipelineFlags(RwUInt32 flags);

/*
 * HIERARCHICAL SCENE FUNCTIONS - OBJECT MANIPULATION
 */

extern Rt2dObject *
Rt2dObjectSetVisible(Rt2dObject *object,RwBool visible);

extern RwBool
Rt2dObjectIsVisible(Rt2dObject *object);

extern void
Rt2dObjectMTMChanged(Rt2dObject *object);

extern RwMatrix *
Rt2dObjectGetLTM(Rt2dObject *object);

extern RwMatrix *
Rt2dObjectGetMTM(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectSetMTM(Rt2dObject *object, RwMatrix *mtm);

extern void
Rt2dObjectApplyCTM(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectMTMSetIdentity(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectMTMScale(Rt2dObject *object, RwReal x, RwReal y);

extern Rt2dObject *
Rt2dObjectMTMTranslate(Rt2dObject *object, RwReal x, RwReal y);

extern Rt2dObject *
Rt2dObjectMTMRotate(Rt2dObject *object, RwReal theta);

extern RwRGBAReal *
Rt2dObjectGetColorMultiplier(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectSetColorMultiplier(Rt2dObject *object, RwRGBAReal *multCol);

extern RwRGBAReal *
Rt2dObjectGetColorOffset(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectSetColorOffset(Rt2dObject *object, RwRGBAReal *oofsCol);

extern RwInt32
Rt2dObjectGetObjectType(Rt2dObject *object);

extern RwInt32
Rt2dObjectGetDepth(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectSetDepth(Rt2dObject *object, RwInt32 depth);

extern RwBool
Rt2dObjectIsScene(Rt2dObject *object);

extern RwBool
Rt2dObjectIsShape(Rt2dObject *object);

extern RwBool
Rt2dObjectIsPickRegion(Rt2dObject *object);

extern RwBool
Rt2dObjectIsObjectString(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectCopy(Rt2dObject *dst, Rt2dObject *src);

/* in-place dst version, destruction not req */
extern Rt2dObject *
_rt2dObjectCopy(Rt2dObject *dst, Rt2dObject *src);

/*
 * HIERARCHICAL SCENE FUNCTIONS - SCENE
 */
extern Rt2dObject *
Rt2dSceneCreate(void);

extern RwBool
Rt2dSceneDestroy(Rt2dObject *scene);

extern Rt2dObject *
Rt2dSceneLock(Rt2dObject *object);

extern Rt2dObject *
Rt2dSceneUnlock(Rt2dObject *object);

extern RwInt32
Rt2dSceneGetChildCount(Rt2dObject *scene);

extern Rt2dObject *
Rt2dSceneGetChildByIndex(Rt2dObject *scene, RwInt32 index);

extern RwV2d
Rt2dSceneGetCoordFromScreen(Rt2dObject *scene,RwV2d      screenCoord );

extern Rt2dObject *
Rt2dSceneAddChild(Rt2dObject *scene, Rt2dObject *object);

/* Those are keeped for compatiblity with the present code */
extern Rt2dObject *
Rt2dSceneGetNewChildScene(Rt2dObject *object);

extern Rt2dObject *
Rt2dSceneGetNewChildShape(Rt2dObject *object);

extern Rt2dObject *
Rt2dSceneGetNewChildPickRegion(Rt2dObject *object);

extern Rt2dObject *
Rt2dSceneGetNewChildObjectString(Rt2dObject *object, const RwChar *text,
                                 const RwChar *font);

extern Rt2dObject *
Rt2dSceneStreamWrite(Rt2dObject *shape, RwStream *stream);

extern RwUInt32
Rt2dSceneStreamGetSize(Rt2dObject *scene);

extern Rt2dObject *
Rt2dSceneStreamRead(RwStream *stream);

extern Rt2dObject *
Rt2dSceneRender(Rt2dObject *object);

extern Rt2dObject *
Rt2dSceneForAllChildren(Rt2dObject *scene, Rt2dObjectCallBack callback, void *pData );

extern Rt2dObject *
Rt2dSceneSetDepthDirty(Rt2dObject *scene);

extern Rt2dObject *
Rt2dSceneUpdateLTM(Rt2dObject *scene);

/*
 * HIERARCHICAL SCENE FUNCTIONS - SHAPE
 */
extern Rt2dObject *
Rt2dShapeCreate(void);

extern RwBool
Rt2dShapeDestroy(Rt2dObject * shape);

extern Rt2dObject *
Rt2dShapeAddNode(Rt2dObject *shape, RwUInt32 flag, Rt2dPath *path, Rt2dBrush *brush );

extern RwInt32
Rt2dShapeGetNodeCount(Rt2dObject *shape);

extern Rt2dObject *
Rt2dShapeStreamWrite(Rt2dObject *shape, RwStream *stream);

extern RwUInt32
Rt2dShapeStreamGetSize(Rt2dObject *shape);

extern Rt2dObject *
Rt2dShapeStreamRead(RwStream *stream);

extern Rt2dObject *
Rt2dShapeRender(Rt2dObject *object);

extern Rt2dObject *
Rt2dShapeMorph(Rt2dObject *result,
               Rt2dObject *source,
               Rt2dObject *destination,
               RwReal alpha);

extern Rt2dObject *
Rt2dShapeLock(Rt2dObject * shape);

extern Rt2dObject *
Rt2dShapeUnlock(Rt2dObject * shape);

/*
 * HIERARCHICAL SCENE FUNCTIONS - PICK REGION
 */
extern Rt2dObject *
Rt2dPickRegionCreate(void);

extern RwBool
Rt2dPickRegionDestroy(Rt2dObject *pickRegion);

extern Rt2dPath *
Rt2dPickRegionGetPath(Rt2dObject *pickRegion);

extern RwBool
Rt2dPickRegionIsPointIn(Rt2dObject *pickRegion, RwV2d *point);

extern Rt2dObject *
Rt2dPickRegionStreamWrite(Rt2dObject *pickRegion, RwStream *stream);

extern RwUInt32
Rt2dPickRegionStreamGetSize(Rt2dObject *pickRegion);

extern Rt2dObject *
Rt2dPickRegionStreamRead(RwStream *stream);

/*
 * HIERARCHICAL SCENE FUNCTIONS - TEXT STRINGS
 */
extern Rt2dObject *
Rt2dObjectStringCreate(const RwChar *textString, const RwChar *font);

extern RwBool
Rt2dObjectStringDestroy(Rt2dObject *object);

extern Rt2dBrush *
Rt2dObjectStringGetBrush(Rt2dObject *object);

extern RwChar *
Rt2dObjectStringGetText(Rt2dObject *object);

extern RwChar *
Rt2dObjectStringGetFont(Rt2dObject *object);

extern RwReal
Rt2dObjectStringGetHeight(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectStringSetBrush(Rt2dObject *object, Rt2dBrush *);

extern Rt2dObject *
Rt2dObjectStringSetText(Rt2dObject *object, const RwChar *text);

extern Rt2dObject *
Rt2dObjectStringSetFont(Rt2dObject *object, const RwChar *font);

extern Rt2dObject *
Rt2dObjectStringSetHeight(Rt2dObject *object, const RwReal height);

extern Rt2dObject *
Rt2dObjectStringStreamRead(RwStream *stream);

extern Rt2dObject *
Rt2dObjectStringStreamWrite(Rt2dObject *object, RwStream *stream);

extern RwUInt32
Rt2dObjectStringStreamGetSize(Rt2dObject *object);

extern Rt2dObject *
Rt2dObjectStringRender(Rt2dObject *object);


/*
 * SPI for macros
 */

extern RwBool
_rt2dCTMPush(RwMatrix *matrix);

extern RwBool
_rt2dCTMSet(RwMatrix *matrix);

extern RwMatrix    *
_rt2dCTMGet(void);

extern RwMatrix *
_rt2dCTMGetDirect(void);


#if ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) )

extern Rt2dBrush *
Rt2dBrushSetWidth(Rt2dBrush *brush, RwReal width);
extern RwReal
Rt2dBrushGetWidth(Rt2dBrush * brush);

extern RwMatrix *
Rt2dCTMRead(RwMatrix * result);

#endif       /* ( defined(RWDEBUG) || defined(RWSUPPRESSINLINE) ) */


#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#define   Rt2dFontStreamGetSize(_font) \
        _rt2dFontStreamGetSize(_font)

#define   Rt2dFontStreamWrite(_font,_stream) \
        _rt2dFontStreamWrite(_font,_stream)

#define   Rt2dFontStreamRead(_stream) \
        _rt2dFontStreamRead(_stream)

#endif                          /* RT2D_H */
