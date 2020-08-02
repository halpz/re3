
#ifndef RPPRTSTD_H
#define RPPRTSTD_H

/*===========================================================================*
 *--- Include files ---------------------------------------------------------*
 *===========================================================================*/

#include "rwcore.h"
#include "rpworld.h"


/*---- start: ./prtstd.h----*/

#include "rwcore.h"
#include "rpworld.h"
#include "rpptank.h"

#include "rpprtstd.rpe"



/************************************************************************
 *
 *
 *
 ************************************************************************/

/**
 * \defgroup rpprtstd RpPrtStd
 * \ingroup particles
 *
 * Particle Animation Plugin for RenderWare Graphics.
 */

/*
 * Current version stamp
 */
#define rpPRTSTDVERSIONSTAMP                2

/*
 * Random Number Generation Macros
 */
#define PRTSTD_SRAND_MAX                    0xFFFFFFFF
#define PRTSTD_SRAND_IMAX                   ((RwReal) 1.0 / (RwReal) PRTSTD_SRAND_MAX)

#define PRTSTD_SRAND(_seed)                 ((_seed) = ((_seed) * 196314165 + 907633515))

/* Real rand -1.0 .. + 1.0 */
#define PRTSTD_RSRAND(_seed)                (((RwReal)((RwUInt32) (_seed) * PRTSTD_SRAND_IMAX) * \
                                            (RwReal) 2.0) - (RwReal) 1.0)



#define PRTSTD_2RSRAND2(_seed)               (((RwReal)((RwReal) (_seed) * PRTSTD_SRAND_IMAX) * \
                                            (RwReal)1.0))

/**
 * \ingroup rpprtstd
 * \ref RpPrtStdParticleFlags, this type represents the different properties of
 * a particle.
 */
enum RpPrtStdParticleFlags
{
    rpPRTSTDPARTICLEFLAGEMITTER              = 0x00000001, /**<Particle is an emitter. */

    rpPRTSTDPARTICLEFLAGFORCEENUMSIZEINT    = RWFORCEENUMSIZEINT
};

typedef enum RpPrtStdParticleFlags RpPrtStdParticleFlags;

/**
 * \ingroup rpprtstd
 * \ref RpPrtStdEmitterFlags, this type represents the different properties of
 * an emitter.
 */
enum RpPrtStdEmitterFlags
{
    rpPRTSTDEMITTERFLAGALIVE                = 0x00000001, /**< The emitter is alive and should not be removed */
    rpPRTSTDEMITTERFLAGACTIVE               = 0x00000002, /**< This indicates the emitter is active or idle */
    rpPRTSTDEMITTERFLAGPTANK                = 0x00000004, /**< The emitter uses the \ref rpptank */
    rpPRTSTDEMITTERFLAGEMIT                 = 0x00000008, /**< This indicates the emitter can emit new particles */
    rpPRTSTDEMITTERFLAGUPDATE               = 0x00000010, /**< This indicates if the emitter is to be updated. */
    rpPRTSTDEMITTERFLAGUPDATEPARTICLE       = 0x00000020, /**< This indicated if the emitter's particles are updated. */
    rpPRTSTDEMITTERFLAGRENDER               = 0x00000040, /**< This indicates if the emitter is rendered. */
    rpPRTSTDEMITTERFLAGRENDERPARTICLE       = 0x00000080, /**< This indicates if the emitter's particles are rendered. */
    rpPRTSTDEMITTERFLAGNOBUFFERSWAP         = 0x00000100, /**< Internal usage */
    rpPRTSTDEMITTERFLAGSTREAMREAD           = 0x00000200, /**< Internal usage */
    rpPRTSTDEMITTERFLAGFORCEENUMSIZEINT     = RWFORCEENUMSIZEINT
};

typedef enum RpPrtStdEmitterFlags RpPrtStdEmitterFlags;

/************************************************************************
 *
 *
 *
 ************************************************************************/

#define rpPRTSTDPARTICLECALLBACKMAX             7

/**
 * \ingroup rpprtstd
 * \ref RpPrtStdParticleCallBackCode, this type represents the different callbacks for
 * processing a \ref RpPrtStdParticleBatch. These callbacks will be called at various point for
 * processing the particle's custom data.
 */
enum RpPrtStdParticleCallBackCode
{
    rpPRTSTDPARTICLECALLBACKUPDATE              = 0, /**< Particle update callback */
    rpPRTSTDPARTICLECALLBACKRENDER,                  /**< Particle render callback */
    rpPRTSTDPARTICLECALLBACKCREATE,                  /**< Particle create callback */
    rpPRTSTDPARTICLECALLBACKDESTROY,                 /**< Particle destroy callback */
    rpPRTSTDPARTICLECALLBACKFORCEENUMSIZEINT    = RWFORCEENUMSIZEINT
};

typedef enum RpPrtStdParticleCallBackCode RpPrtStdParticleCallBackCode;

#define rpPRTSTDEMITTERCALLBACKMAX              11

/**
 * \ingroup rpprtstd
 * \ref RpPrtStdEmitterCallBackCode, this type represents the different callbacks for
 * processing a \ref RpPrtStdEmitter. These callbacks will be called at various point for
 * processing the emitter's custom data.
 */
enum RpPrtStdEmitterCallBackCode
{
    rpPRTSTDEMITTERCALLBACKEMIT                 = 0, /**< Emitter particle emission callback */
    rpPRTSTDEMITTERCALLBACKBEGINUPDATE,              /**< Emitter begin update call back */
    rpPRTSTDEMITTERCALLBACKENDUPDATE,                /**< Emitter end update callback */
    rpPRTSTDEMITTERCALLBACKBEGINRENDER,              /**< Emitter begin render callback */
    rpPRTSTDEMITTERCALLBACKENDRENDER,                /**< Emitter end render callback */
    rpPRTSTDEMITTERCALLBACKCREATE,                   /**< Emitter create callback */
    rpPRTSTDEMITTERCALLBACKDESTROY,                  /**< Emitter destroy callback */
    rpPRTSTDEMITTERCALLBACKSTREAMREAD,               /**< Emitter stream input callback */
    rpPRTSTDEMITTERCALLBACKSTREAMWRITE,              /**< Emitter stream output callback */
    rpPRTSTDEMITTERCALLBACKSTREAMGETSIZE,            /**< Emitter stream get size callback */
    rpPRTSTDEMITTERCALLBACKCLONE,                    /**< Emitter clone  callback */
    rpPRTSTDEMITTERCALLBACKFORCEENUMSIZEINT     = RWFORCEENUMSIZEINT
};

typedef enum RpPrtStdEmitterCallBackCode RpPrtStdEmitterCallBackCode;

typedef RwInt32 RpPrtStdPropertyCode;

/************************************************************************
 *
 *
 *
 ************************************************************************/

typedef struct RpPrtStdEmitter RWALIGN(RpPrtStdEmitter, rwMATRIXALIGNMENT);

/**
 * \ingroup rpprtstd
 * \ref RpPrtStdEmitterCallBack
 * \ref RpPrtStdEmitterCallBack represents the function called for processing
 * a \ref RpPrtStdEmitter. There can several types of the functions, each performing a
 * specific task defined by \ref RpPrtStdEmitterCallBackCode.
 *
 * \param atomic        A pointer to the emitter's parent atomic.
 * \param emt           A pointer to the emitter.
 * \param data          A pointer to user data.
 *
 * \return A pointer to the emitter on success. NULL otherwise.
 */
typedef RpPrtStdEmitter *
        (*RpPrtStdEmitterCallBack)
            (RpAtomic *atomic, RpPrtStdEmitter *emt, void *data);

typedef struct RpPrtStdParticleBatch RWALIGN(RpPrtStdParticleBatch, rwMATRIXALIGNMENT);
/**
 * \ingroup rpprtstd
 * \ref RpPrtStdParticleCallBack represents the function called for processing
 * a \ref RpPrtStdParticleBatch. There can be several types of the functions, each
 * performing a specific task defined by \ref RpPrtStdParticleCallBackCode.
 *
 * \param emt           A pointer to the particle batch's parent emitter.
 * \param prtBatch      A pointer to the particle batch.
 * \param data          A pointer to user data.
 *
 * \return A pointer to the particle batch on success. NULL otherwise.
 */
typedef RpPrtStdParticleBatch *
        (*RpPrtStdParticleCallBack)
            (RpPrtStdEmitter *emt, RpPrtStdParticleBatch *prtBatch, void *data);

/**
 * \ingroup rpprtstd
 * \ref RpPrtStdEmitterCallBackArray represents a set of callback functions for
 * processing a \ref RpPrtStdEmitter. All the functions are of the type \ref
 * RpPrtStdEmitterCallBack.
 *
 * \see RpPrtStdEmitterCallBackCode
 */
typedef RpPrtStdEmitterCallBack
        RpPrtStdEmitterCallBackArray[rpPRTSTDEMITTERCALLBACKMAX];

/**
 * \ingroup rpprtstd
 * \ref RpPrtStdParticleCallBackArray represents a set of callback functions for
 * processing a \ref RpPrtStdParticleBatch. All the functions are of the type \ref
 * RpPrtStdParticleCallBack.
 *
 * \see RpPrtStdParticleCallBackCode
 */
typedef RpPrtStdParticleCallBack
        RpPrtStdParticleCallBackArray[rpPRTSTDPARTICLECALLBACKMAX];


/************************************************************************
 *
 *
 *
 ************************************************************************/

typedef struct RpPrtStdEmitterClass RpPrtStdEmitterClass;
/**
 * \ingroup rpprtstd
 * \ref RpPrtStdEClassSetupCallBack represents the function called for setting up an
 * emitter class's set of callback function. The callback function is called
 * after an emitter class is streamed in.
 *
 * \param eClass        A pointer to an emitter class.
 *
 * \return A pointer to the emitter class on success. NULL otherwise.
 */
typedef RpPrtStdEmitterClass *
        (*RpPrtStdEClassSetupCallBack)
            (RpPrtStdEmitterClass *eClass);

typedef struct RpPrtStdParticleClass RpPrtStdParticleClass;
/**
 * \ingroup rpprtstd
 * \ref RpPrtStdPClassSetupCallBack represents the function called for setting up an
 * emitter class's set of callback function. The callback function is called
 * after an emitter class is streamed in.
 *
 * \param pClass        A pointer to a particle class.
 *
 * \return A pointer to the particle class on success. NULL otherwise.
 */
typedef RpPrtStdParticleClass *
        (*RpPrtStdPClassSetupCallBack)
            (RpPrtStdParticleClass *pClass);

/************************************************************************
 *
 *
 *
 ************************************************************************/

typedef struct RpPrtStdPropertyTable RpPrtStdPropertyTable;
/**
 * \ingroup rpprtstd
 * \struct RpPrtStdPropertyTable
 * A structure representing properties's data present in an emitter or
 * particle.
 * An emitter, or particle, are treated as a single block of memory. The
 * property table is used to describe the data presents in the memory block.
 * It stores the property's id, offset entry from the start of the memory
 * block and size in bytes.
 */
struct RpPrtStdPropertyTable
{
    RwUInt32                        *propPtr;       /**< Internal usage */
    RpPrtStdPropertyTable           *next;          /**< Internal usage */

    RwInt32                         id;             /**< Property table's id */
    RwInt32                         refCount;       /**< Reference count. Internal usage */

    RwInt32                         numProp;        /**< Number of properties in the table */
    RwInt32                         maxProp;        /**< Internal usage */
    RwInt32                         *propID;        /**< Array of properties's id */
    RwInt32                         *propOffset;    /**< Array of properties's offset */
    RwInt32                         *propSize;      /**< Array of properties's size */
    RwInt32                         *propSizeUA;    /**< Internal usage */
};

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitterClass
 * A structure representing the collection of data and callbacks for an emitter. An emitter
 * class is used to create emitters that share the same properties and callback functions.
 * Once created, an emitter class cannot be altered. An emitter class should also not be
 * destroyed if emitters of the class are still in use.
 */
struct RpPrtStdEmitterClass
{
    RpPrtStdEmitterClass                    *next;          /**< Internal usage */

    RwInt32                                 id;             /**< Emitter class's id */
    RwInt32                                 refCount;       /**< Reference count. Internal usage */

    RwInt32                                 objSize;        /**< Size of the emitter */
    RpPrtStdPropertyTable                   *propTab;       /**< Reference to a table of emitter properties */

    RwInt32                                 numCallback;    /**< Number of callback arrays */
    RpPrtStdEmitterCallBackArray            *callback;      /**< Array of emitter callback functions */
};

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdParticleClass
 * A structure representing the collection of data and callbacks for a particle. A particle
 * class is used to create particle that share the same properties and callback functions.
 * Once created, a particle class cannot be altered. A particle class should also not be
 * destroyed if particles of the class are still in use.
 */
struct RpPrtStdParticleClass
{
    RpPrtStdParticleClass                   *next;          /**< Internal usage */

    RwInt32                                 id;             /**< Particle class's id */
    RwInt32                                 refCount;       /**< Reference count. Internal usage */

    RwInt32                                 objSize;        /**< Size of a particle */
    RpPrtStdPropertyTable                   *propTab;       /**< Reference to a table of particle properties */

    RwInt32                                 numCallback;    /**< Number of callback sets */
    RpPrtStdParticleCallBackArray           *callback;      /**< Array of particle batch callback functions */
};


/************************************************************************
 *
 *
 *
 ************************************************************************/

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdParticleBatch
 * A structure repsenting a group of particles. For efficient, particles are stored
 * in batches rather than individually. All live particles are stored at the head
 * of batch with no gaps of dead particles. A counter is used to record the number of
 * live particles in the batch. Once a batch has 0 live particles, it will removed
 * from the emitter's active particle list to the inactive list.
 * The first particle of the batch is given by an offset from the start of the
 * particle batch.
 */
struct RpPrtStdParticleBatch
{
    RpPrtStdParticleBatch       *next;                      /**< Pointer to the next particle batch */

    RpPrtStdParticleClass       *prtClass;                  /**< Pointer to the particle's class */

    RwInt32                     numPrt;                     /**< Number of particles in the batch */
    RwInt32                     maxPrt;                     /**< Maxium number of particles in batch */
    RwInt32                     newPrt;                     /**< Start of newly emitted particles in the batch */

    RwInt32                     offset;                     /**< Offset to the first particle, from the start of the
                                                             * particle batch */
};

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitter
 * A structure repsenting the mandatory data set for any emitter. Each emitter contains information of
 * itself and its particles, via the emitter class and particle class respectively. It also contains the
 * list of particles, in batches, it had emitted.
 * Optional data are stored immediately after the mandatory set. The contents of the optional data are
 * described in the emitter class's property table. The offset from the property table are from the start
 * of the emitter.
 *
 * The type of particles emitted are given by the particle class. Each emitter may have only emitter class
 * and particle class and these should not be changed during the lifetime of the emitter and its particles.
 * The emitter maintains two lists of particle batches, an acitive list, contain still active particles,
 * and an inactive list. The maximum number of particles in each batch is given by the prtBatchMaxPrt field.
 */
struct RpPrtStdEmitter
{
    RpPrtStdEmitter             *next;                      /**< Pointer to the next emitter */

    RwUInt32                    flag;                       /**< Emitter's property flag */

    RpAtomic                    *atomic;                    /**< Pointer to emitter's parent atomic */

    RpPrtStdEmitterClass        *emtClass;                  /**< Pointer the emitter's class */

    RwInt32                     prtActive;                  /**< Number of particles emitted */
    RwInt32                     prtBatchMaxPrt;             /**< Maximum number of particles per batch */
    RpPrtStdParticleClass       *prtClass;                  /**< Pointer to the particle's class */

    RpPrtStdParticleBatch       *inactiveBatch,             /**< Circular linked list of inactive particle batches */
                                *activeBatch;               /**< Circular linked list of active particle batches */

    RwReal                      boundingSphere;             /**< Emitter's bounding sphere. */
};



/************************************************************************
 *
 *
 *
 ************************************************************************/

#define rpPRTSTDPROPERTYCODEEMITTER                                 0
#define rpPRTSTDPROPERTYCODEEMITTERSTANDARD                         1
#define rpPRTSTDPROPERTYCODEEMITTERPRTCOLOR                         2
#define rpPRTSTDPROPERTYCODEEMITTERPRTTEXCOORDS                     3
#define rpPRTSTDPROPERTYCODEEMITTERPRTSIZE                          5
#define rpPRTSTDPROPERTYCODEEMITTERPTANK                            6
#define rpPRTSTDPROPERTYCODEEMITTERPRTVELOCITY                      7
#define rpPRTSTDPROPERTYCODEEMITTERPRTMATRIX                        8

#define rpPRTSTDEMITTERPROPERTYCOUNT                                9

#define rpPRTSTDEMITTERDATAFLAGSTANDARD                     0x00000001
#define rpPRTSTDEMITTERDATAFLAGPRTCOLOR                     0x00000002
#define rpPRTSTDEMITTERDATAFLAGPRTTEXCOORDS                 0x00000004
#define rpPRTSTDEMITTERDATAFLAGPRTSIZE                      0x00000010
#define rpPRTSTDEMITTERDATAFLAGPTANK                        0x00000020
#define rpPRTSTDEMITTERDATAFLAGPRTMATRIX                    0x00000040


typedef struct RpPrtStdEmitterStandard RpPrtStdEmitterStandard;

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitterStandard
 * A structure represent the set of properties for a basic emitter. The structure is stored as
 * a single optional data in the emitter property table.
 *
 * The basic emitter uses a 'time' variable to control particle emissions. A large time gap between
 * emission can give pulse effects where as a small time gap produces a streaming effects. Particles
 * can be emitted from a single point, line, area or a volume.
 *
 * Particles emitted from an emitter are of the same type. An emitter cannot emit different types of
 * particles. Once an emitter has reached its maximum number of particles, no further particles are
 * emitted until some of the existing particles have died.
 *
 * Most properties have a bias value to vary the property's value. This uses the seed field
 * to give a degreee of randomness.
 */
struct RpPrtStdEmitterStandard
{
    RwInt32                     seed;                           /**< Seed for random number generator */

    RwInt32                     maxPrt;                         /**< Maximum number of active particles */

    RwReal                      currTime,                       /**< Current timestamp for emitter */
                                prevTime;                       /**< Previous timestamp for emitter */
    RwV3d                       force;                          /**< External force applied to particles */

    RwV3d                       emtPos,                         /**< Emitter position */
                                emtSize;                        /**< Emitter size. This is the volume where new particles
                                                                 * are emitted */
    RwReal                      emtEmitGap,                     /**< Time gap between emission */
                                emtEmitGapBias,                 /**< Time gap bias */
                                emtPrevEmitTime,                /**< Previous particle emission time */
                                emtEmitTime;                    /**< Next particle emission time */
    RwInt32                     emtPrtEmit,                     /**< Number of particle emit per emission */
                                emtPrtEmitBias;                 /**< Particle emission bias */

    RwReal                      prtInitVel,                     /**< Particle's initial speed */
                                prtInitVelBias;                 /**< Particle's initial speed bias */
    RwReal                      prtLife,                        /**< Particle's duration */
                                prtLifeBias;                    /**< Particle's duration bias */

    RwV3d                       prtInitDir,                     /**< Particle's initial direction */
                                prtInitDirBias;                 /**< particle's initial direction bias */

    RwV2d                       prtSize;                        /**< Particle's size */

    RwRGBA                      prtColor;                       /**< Particle's color */

    RwTexCoords                 prtUV[4];                       /**< Particle's texture coordindates */
    RwTexture                   *texture;                       /**< Particle's texture */

    RwMatrix                    *ltm;                           /**< LTM to transform particle coordinates from local space
                                                                 * to world space */
};

typedef struct RpPrtStdEmitterPrtColor RpPrtStdEmitterPrtColor;
/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitterPrtColor
 * An optional structure to represent the change in color of a particle from birth to death.
 * The particles will start with the prtStartCol and ends with endPrtColor. The particle's
 * life is used to interpolate the colors.
 *
 * If this structure is not present, then the particles will have a constant color.
 */
struct RpPrtStdEmitterPrtColor
{
    RwRGBAReal                  prtStartCol,                    /**< Particle start color */
                                prtStartColBias;                /**< Particle start color bias */
    RwRGBAReal                  prtEndCol,                      /**< Particle end color */
                                prtEndColBias;                  /**< Particle end color bias */
};

typedef struct RpPrtStdEmitterPrtTexCoords RpPrtStdEmitterPrtTexCoords;

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitterPrtTexCoords
 * An optional structure to represent the change in texcoords of a particle from birth to death.
 * The particles will start with prtStartUV0 and prtStartUV1 and ends with endPrtEndUV0 and endPrtEndUV1.
 * The particle's life is used to interpolate the texcoords.
 *
 * A particle can have two texcoords representing the top left and bottom right respectively. By varying
 * the texcoords can give an animated texture effect on a particle.
 *
 * If this structure is not present, then the particles will have a constant texcoords.
 */
struct RpPrtStdEmitterPrtTexCoords
{
    RwTexCoords                 prtStartUV0,                        /**< Particle start top left texcoords */
                                prtStartUV0Bias;                    /**< Particle start top left texcoords bias */
    RwTexCoords                 prtEndUV0,                          /**< Particle end top left texcoords */
                                prtEndUV0Bias;                      /**< Particle end top left texcoords bias */
    RwTexCoords                 prtStartUV1,                        /**< Particle start bottom right texcoords */
                                prtStartUV1Bias;                    /**< Particle start botton right texcoords bias */
    RwTexCoords                 prtEndUV1,                          /**< Particle end bottom right texcoords */
                                prtEndUV1Bias;                      /**< Particle end bottom right texcoords bias */
};

typedef struct RpPrtStdEmitterPrtSize RpPrtStdEmitterPrtSize;

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitterPrtSize
 * An optional structure to represent the change in size of a particle from birth to death.
 * The particles will start with prtStartSize and ends with prtEndSize. The particle's life
 * is used to interpolate the size.
 *
 * If this structure is not present, then the particles will have a constant size.
 */
struct RpPrtStdEmitterPrtSize
{
    RwV2d                       prtStartSize,                       /**< Particle start size */
                                prtStartSizeBias;                   /**< Particle start size bias */
    RwV2d                       prtEndSize,                         /**< Particle end size */
                                prtEndSizeBias;                     /**< Particle end size bias */
};


/**
 * \ingroup rpprtstd
 * A set of flag settings for use in the \ref RpPrtStdEmitterPrtMatrix flag
 */
enum RpPrtStdEmitterPrtMatrixFlags
{
    rpPRTSTDEMITTERPRTMTXFLAGSCNSMTX = 0x00000001,                  /**< Apply the prtCnsMtx matrix to
                                                                     * each particle if set */
    RPPRTSTDEMITTERPRTMTXFLAGSFORCEENUMSIZEINT = RWFORCEENUMSIZEINT
};

typedef enum RpPrtStdEmitterPrtMatrixFlags RpPrtStdEmitterPrtMatrixFlags;

typedef struct RpPrtStdEmitterPrtMatrix RWALIGN(RpPrtStdEmitterPrtMatrix, rwMATRIXALIGNMENT);

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitterPrtMatrix
 *
 * An optional structure to construct a matrix for each particle during emissions. A particle
 * can be represented as a single matrix. This gives the particles an orientation rather than
 * just a simple position.
 *
 * This allows transformation to be applied to the particles, such as rotation. If
 * \ref rpPRTSTDEMITTERPRTMTXFLAGSCNSMTX is set in the flag, then the prtCnsMatrix is applied to each
 * particle during particle update.
 *
 * If this structure is not present, then it assumes the  particles will have just a position
 * property.
 */
struct RpPrtStdEmitterPrtMatrix
{
    RwMatrix                    prtCnsMtx;       /**< Transformation matrix to be applied to each particle */

    RwV3d                       prtPosMtxAt,     /**< Particle initial look at vector */
                                prtPosMtxAtBias; /**< Particle initial look at vector bias */
    RwV3d                       prtPosMtxUp,     /**< Particle initial up vector. */
                                prtPosMtxUpBias; /**< Particle initial up vector bias */

    RwInt32                     flags;           /**< Particle matrix flag. See \ref RpPrtStdEmitterPrtMatrixFlags */
};

/************************************************************************
 *
 *
 *
 ************************************************************************/



enum RpPrtStdPTankPropertyCode
{
    rpPRTSTDPTANKPROPPARTICLESMAX                   = 0,
    rpPRTSTDPTANKPROPDATAFLAGS,
    rpPRTSTDPTANKPROPPLATFORMFLAGS,
    rpPRTSTDPTANKPROPPTANK,
    rpPRTSTDPTANKPROPFORCEENUMSIZEINT               = RWFORCEENUMSIZEINT
};

typedef enum RpPrtStdPTankPropertyCode RpPrtStdPTankPropertyCode;

typedef struct RpPrtStdEmitterPTank RpPrtStdEmitterPTank;

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdEmitterPTank
 *
 * A structure for storing the data required to create a RpPTank for use
 * with the emitter. The structure allows the user to create a RpPTank
 * manually.
 */
struct RpPrtStdEmitterPTank
{
    RwUInt32                    dataFlags,      /**< Data flag used in RpPTank creation. See
                                                 * \ref RpPTankAtomicCreate  */
                                platFlags,      /**< Platform flag used in RpPTank creation. See
                                                 * \ref RpPTankAtomicCreate */
                                numPrt,         /**< An integer representing the current number of active
                                                 * particles */
                                maxPrt,         /**< An integer representing the maxiumum number of particles
                                                 * stored in the RpPTank */
                                updateFlags,    /**< A flag representing the properties to be updated by
                                                 * the particle emiiter during update. A user may select to
                                                 * update some properties manually by unsetting the relevant
                                                 * bits in the flag.
                                                 * The flag settings are the same as \ref RpPTankDataFlags */
                                emitFlags;      /**< A flag representing the properties to be initialised
                                                 * by the particle emitter during particles emission. A user
                                                 * may select to initialise some properties manually by
                                                 * unsetting the relevant bits in the flag.
                                                 * The flag settings are the same as \ref RpPTankDataFlags */
    RpAtomic                    *pTank;         /**< Pointer to the RpPTank */
    RwChar                      **dataInPtrs,   /**< Internal usage */
                                **dataOutPtrs;  /**< Internal usage */
    RwInt32                     *dataStride;    /**< Internal usage */
    RwUInt32                    strSrcBlend;    /**< Internal usage */
    RwUInt32                    strDstBlend;    /**< Internal usage */
    RwBool                      strVtxABlend;   /**< Internal usage */
};

/************************************************************************
 *
 *
 *
 ************************************************************************/

#define rpPRTSTDPROPERTYCODEPARTICLESTANDARD                0
#define rpPRTSTDPROPERTYCODEPARTICLEPOSITION                1
#define rpPRTSTDPROPERTYCODEPARTICLECOLOR                   2
#define rpPRTSTDPROPERTYCODEPARTICLETEXCOORDS               3
#define rpPRTSTDPROPERTYCODEPARTICLESIZE                    5
#define rpPRTSTDPROPERTYCODEPARTICLEVELOCITY                6
#define rpPRTSTDPROPERTYCODEPARTICLEMATRIX                  7

#define rpPRTSTDPARTICLEPROPERTYCOUNT                       8

#define rpPRTSTDPARTICLEDATAFLAGSTANDARD                    0x00000001
#define rpPRTSTDPARTICLEDATAFLAGPOSITION                    0x00000002
#define rpPRTSTDPARTICLEDATAFLAGCOLOR                       0x00000004
#define rpPRTSTDPARTICLEDATAFLAGTEXCOORDS                   0x00000008
#define rpPRTSTDPARTICLEDATAFLAGSIZE                        0x00000020
#define rpPRTSTDPARTICLEDATAFLAGVELOCITY                    0x00000040
#define rpPRTSTDPARTICLEDATAFLAGMATRIX                      0x00000080


/**
 * \ingroup rpprtstd
 * \struct RpPrtStdParticleStandard
 * A structure represent the set of properties for a basic particle. This structure is mandatory
 * for all particles.
 * The structure contain the life duration of the particle. The particle will be removed when the current
 * time is greater than the end time. The particle timer always starts at zero.
 *
 * The inverted end time is for interpolating optional particle properties.
 */
typedef struct RpPrtStdParticleStandard RpPrtStdParticleStandard;
struct RpPrtStdParticleStandard
{
    RwInt32                     flag;                               /**< Particle's property flag */
    RwReal                      currTime,                           /**< Particle's curr time  */
                                endTime,                            /**< Particle's end time */
                                invEndTime;                         /**< Particle's inv end for interpolation */
};


typedef struct RpPrtStdParticleColor RpPrtStdParticleColor;

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdParticleColor
 * A structure representing the change in a particle's color during its life time. The structure is optional
 * and should not be used if particles have a constant color.
 */
struct RpPrtStdParticleColor
{
    RwRGBAReal                  startCol,                           /**< Particle's end size bias */
                                deltaCol;                           /**< Particle's color rate of change */
};

typedef struct RpPrtStdParticleTexCoords RpPrtStdParticleTexCoords;

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdParticleTexCoords
 * A structure representing the change in a particle's texcoords during its life time. The structure is optional
 * and should not be used if particles have a constant texcoords.
 */
struct RpPrtStdParticleTexCoords
{
    RwTexCoords                 startUV0,                           /**< Particle's starting top left texcoords */
                                startUV1;                           /**< Particle's starting bottom right texcoords */
    RwTexCoords                 deltaUV0,                           /**< Particle's top left texcoords rate of change */
                                deltaUV1;                           /**< Particle's bottom right texcoords rate of change */
};

typedef struct RpPrtStdParticleSize RpPrtStdParticleSize;

/**
 * \ingroup rpprtstd
 * \struct RpPrtStdParticleSize
 * A structure representing the change in a particle's size during its life time. The structure is optional
 * and should not be used if particles have a constant size.
 */
struct RpPrtStdParticleSize
{
    RwV2d                       startSize,                          /**< Particle's starting size */
                                deltaSize;                          /**< Particle's size rate of change */
    RwV2d                       currSize,                           /**< Particle's current size. Internal use only */
                                invCurrSize;                        /**< Particle's inverse current size. Internal use only */
};

/************************************************************************
 *
 *
 *
 ************************************************************************/

#ifdef    __cplusplus
extern "C"
{
#endif         /* __cplusplus */

/************************************************************************/

extern RwBool
RpPrtStdPluginAttach( void );

/************************************************************************/

extern RwBool
RpAtomicIsParticleEmitter(RpAtomic *atomic);

extern RpAtomic *
RpPrtStdAtomicCreate(RpPrtStdEmitterClass *eClass, void *data);

extern RpAtomic *
RpPrtStdAtomicUpdate(RpAtomic *atomic, void *data);

extern RpAtomic *
RpPrtStdAtomicSetEmitter(RpAtomic *atomic, RpPrtStdEmitter *emt);

extern RpPrtStdEmitter *
RpPrtStdAtomicGetEmitter(RpAtomic *atomic);

extern RpAtomic *
RpPrtStdAtomicForAllEmitter(RpAtomic *atomic,
                            RpPrtStdEmitterCallBack callback,
                            void *data);

extern RpAtomic *
RpPrtStdAtomicAddEmitter(RpAtomic *,
                         RpPrtStdEmitter *emt);


/************************************************************************/


extern RpPrtStdEmitter *
RpPrtStdEmitterCreate(RpPrtStdEmitterClass *eClass);

extern RwBool
RpPrtStdEmitterDestroy(RpPrtStdEmitter *emt);

extern RpPrtStdEmitter *
RpPrtStdEmitterClone(RpPrtStdEmitter *emt);

extern RpPrtStdEmitter *
RpPrtStdEmitterForAllParticleBatch(RpPrtStdEmitter *emt,
                                    RpPrtStdParticleCallBack callback,
                                    void * data);


extern RpPrtStdEmitter *
RpPrtStdEmitterAddEmitter(RpPrtStdEmitter *emtHead,
                          RpPrtStdEmitter *emt);

extern RpPrtStdEmitter *
RpPrtStdEmitterLinkPTank(RpPrtStdEmitter *emt,RpAtomic *ptank);


extern RpPrtStdEmitter *
RpPrtStdEmitterDestroyParticleBatch(RpPrtStdEmitter *emt);

extern RpPrtStdParticleBatch *
RpPrtStdEmitterNewParticleBatch(RpPrtStdEmitter *emt);

extern RpPrtStdEmitter *
RpPrtStdEmitterAddParticleBatch(RpPrtStdEmitter *emt,
                                RpPrtStdParticleBatch *prtBatch);


extern RpPrtStdEmitter *
RpPrtStdEmitterSetPClass(RpPrtStdEmitter *emt,
                                 RpPrtStdParticleClass *pClass,
                                 RwInt32 maxPrt);

extern RpPrtStdEmitter *
RpPrtStdEmitterGetPClass(RpPrtStdEmitter *emt,
                                 RpPrtStdParticleClass **pClass,
                                 RwInt32 *maxPrt);


/************************************************************************/

extern RpPrtStdParticleBatch *
RpPrtStdParticleBatchCreate(RpPrtStdParticleClass *pClass, RwInt32 maxPrt);

extern RwBool
RpPrtStdParticleBatchDestroy(RpPrtStdParticleBatch *prtBatch);

extern RpPrtStdParticleBatch *
RpPrtStdParticleBatchAddBatch(RpPrtStdParticleBatch *prtBatchHead,
                              RpPrtStdParticleBatch *prtBatch);

/************************************************************************/

extern RpPrtStdPropertyTable *
RpPrtStdPropTabCreate(RwInt32 numProp,
                            RwInt32 *propID, RwInt32 *propStride);

extern RwBool
RpPrtStdPropTabDestroy(RpPrtStdPropertyTable *propTab);


extern RpPrtStdPropertyTable *
RpPrtStdPropTabGetProperties(RpPrtStdPropertyTable *propTab,
                             RwInt32 *numProp,
                             RwInt32 **propID,
                             RwInt32 **propOffset,
                             RwInt32 **propSize);

extern RwInt32
RpPrtStdPropTabGetPropOffset(RpPrtStdPropertyTable *propTab,
                             RwInt32 propID);

extern RwInt32
RpPrtStdPropTabGetPropIndex(RpPrtStdPropertyTable *propTab,
                            RwInt32 propID);


extern RpPrtStdPropertyTable *
RpPrtStdPropTabGet(RwInt32 id);

extern RpPrtStdPropertyTable *
RpPrtStdPropTabStreamRead(RwStream *stream);

extern RpPrtStdPropertyTable *
RpPrtStdPropTabStreamWrite(RpPrtStdPropertyTable *eClass,
                           RwStream *stream);

extern RwInt32
RpPrtStdPropTabStreamGetSize(RpPrtStdPropertyTable *eClass);
/************************************************************************/

extern RwBool
RpPrtStdEClassDestroy(RpPrtStdEmitterClass *eClass);

extern RpPrtStdEmitterClass *
RpPrtStdEClassCreate( void );

extern RpPrtStdEmitterClass *
RpPrtStdEClassSetCallBack(RpPrtStdEmitterClass *eClass,
                                RwInt32 numCallback,
                                RpPrtStdEmitterCallBackArray *emtCB);

extern RpPrtStdEmitterClass *
RpPrtStdEClassGetCallBack(RpPrtStdEmitterClass *eClass,
                           RwInt32 *numCallback,
                           RpPrtStdEmitterCallBackArray **emtCB);

extern RpPrtStdEmitterClass *
RpPrtStdEClassSetPropTab(RpPrtStdEmitterClass *eClass,
                         RpPrtStdPropertyTable *propTab);

extern RpPrtStdEmitterClass *
RpPrtStdEClassGetPropTab(RpPrtStdEmitterClass *eClass,
                         RpPrtStdPropertyTable **propTab);


extern RpPrtStdEmitterClass *
RpPrtStdEClassGet(RwInt32 id);

extern RpPrtStdEmitterClass *
RpPrtStdEClassStreamRead(RwStream *stream);

extern RpPrtStdEmitterClass *
RpPrtStdEClassStreamWrite(RpPrtStdEmitterClass *eClass,
                                 RwStream *stream);

extern RwInt32
RpPrtStdEClassStreamGetSize(RpPrtStdEmitterClass *eClass);

/************************************************************************/

extern RpPrtStdParticleClass *
RpPrtStdPClassCreate( void );

extern RwBool
RpPrtStdPClassDestroy(RpPrtStdParticleClass *pClass);

extern RpPrtStdParticleClass *
RpPrtStdPClassSetCallBack(RpPrtStdParticleClass *pClass,
                                 RwInt32 numCallback,
                                 RpPrtStdParticleCallBackArray *prtCB);

extern RpPrtStdParticleClass *
RpPrtStdPClassGetCallBack(RpPrtStdParticleClass *pClass,
                                 RwInt32 *numCallback,
                                 RpPrtStdParticleCallBackArray **prtCB);

extern RpPrtStdParticleClass *
RpPrtStdPClassSetPropTab(RpPrtStdParticleClass *pClass,
                                      RpPrtStdPropertyTable *propTab);

extern RpPrtStdParticleClass *
RpPrtStdPClassGetPropTab(RpPrtStdParticleClass *pClass,
                                      RpPrtStdPropertyTable **propTab);

extern RpPrtStdParticleClass *
RpPrtStdPClassGet(RwInt32 id);

extern RpPrtStdParticleClass *
RpPrtStdPClassStreamRead(RwStream *stream);

extern RpPrtStdParticleClass *
RpPrtStdPClassStreamWrite(RpPrtStdParticleClass *pClass,
                                 RwStream *stream);

extern RwInt32
RpPrtStdPClassStreamGetSize(RpPrtStdParticleClass *pClass);

/************************************************************************/

extern RwBool
RpPrtStdSetEClassSetupCallBack(RpPrtStdEClassSetupCallBack emtCB);

extern RwBool
RpPrtStdGetEClassSetupCallBack(RpPrtStdEClassSetupCallBack *emtCB);

extern RwBool
RpPrtStdSetPClassSetupCallBack(RpPrtStdPClassSetupCallBack prtCB);

extern RwBool
RpPrtStdGetPClassSetupCallBack(RpPrtStdPClassSetupCallBack *prtCB);

/************************************************************************/


extern RwStream *
RpPrtStdGlobalDataStreamRead(RwStream *stream);

extern RwStream *
RpPrtStdGlobalDataStreamWrite(RwStream *stream);

extern RwInt32
RpPrtStdGlobalDataStreamGetSize( void );

extern void
RpPrtStdGlobalDataSetStreamEmbedded( RwBool embedded );

extern RwBool
RpPrtStdGlobalDataGetStreamEmbedded( void );

/************************************************************************/

extern RpPrtStdEmitter *
RpPrtStdEmitterDefaultCB(RpAtomic * atomic,
                         RpPrtStdEmitter *prtEmt, void * data);


extern RpPrtStdParticleBatch *
RpPrtStdParticleDefaultCB(RpPrtStdEmitter * prtEmt,
                          RpPrtStdParticleBatch *prtBatch, void * data);

/************************************************************************/

extern RpPrtStdParticleBatch *
RpPrtStdParticleStdUpdateCB(RpPrtStdEmitter *emt,
                                 RpPrtStdParticleBatch *prtBatch, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdEmitCB(RpAtomic *atomic,
                              RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdCloneCB(RpAtomic *atomic,
                                RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdCreateCB(RpAtomic *atomic,
                                RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdDestroyCB(RpAtomic *atomic,
                                RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdBeginUpdateCB(RpAtomic *atomic,
                                     RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdEndUpdateCB(RpAtomic *atomic,
                                   RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdRenderCB(RpAtomic *atomic,
                                RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdStreamReadCB(RpAtomic *atomic,
                                    RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdStreamWriteCB(RpAtomic *atomic,
                                     RpPrtStdEmitter *emt, void *data);

extern RpPrtStdEmitter *
RpPrtStdEmitterStdStreamGetSizeCB(RpAtomic *atomic,
                                       RpPrtStdEmitter *emt, void *data);



extern RpPrtStdEmitterClass *
RpPrtStdEClassStdCreate( RwInt32 dataFlag );

extern RwInt32
RpPrtStdEClassStdCreateID( RwInt32 dataFlag );

extern RpPrtStdParticleClass *
RpPrtStdPClassStdCreate( RwInt32 dataFlag );

extern RwInt32
RpPrtStdPClassStdCreateID( RwInt32 dataFlag );

extern RpPrtStdEmitterClass *
RpPrtStdEClassStdSetupCB(RpPrtStdEmitterClass *eClass);

extern RpPrtStdParticleClass *
RpPrtStdPClassStdSetupCB(RpPrtStdParticleClass *pClass);


#ifdef    __cplusplus
}
#endif         /* __cplusplus */

/*---- end: ./prtstd.h----*/

/*---- start: c:/daily/rwsdk/plugin/prtstd/d3d8/prtstdplatform.h----*/
/*---- end: c:/daily/rwsdk/plugin/prtstd/d3d8/prtstdplatform.h----*/

#endif /* RPPRTSTD_H */


