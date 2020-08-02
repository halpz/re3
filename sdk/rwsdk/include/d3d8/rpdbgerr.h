/***************************************************************************
 *                                                                         *
 * Module  : badebug.h                                                     *
 *                                                                         *
 * Purpose : Debug handling                                                *
 *                                                                         *
 **************************************************************************/

#ifndef RWDEBUG_H
#define RWDEBUG_H

#if (defined(RWDEBUG) && defined(RWVERBOSE))
#if (defined(_MSC_VER))
#if (_MSC_VER>=1000)

/* Pick up _ASSERTE macro */
#ifdef _XBOX
#include <xtl.h>
#endif /* _XBOX */
#if (defined(RWMEMDEBUG) && !defined(_CRTDBG_MAP_ALLOC))
#define _CRTDBG_MAP_ALLOC
#endif /* defined(RWMEMDEBUG) && !defined(_CRTDBG_MAP_ALLOC)) */
#include <crtdbg.h>
#undef  RWASSERTE
#define RWASSERTE(_condition) _ASSERTE(_condition)
#endif /* (_MSC_VER>=1000) */
#endif /* (defined(_MSC_VER)) */
#endif /* (defined(RWDEBUG) && defined(RWVERBOSE)) */

#if (!defined(RWASSERTE))
#define RWASSERTE(_condition)  /* No-Op */
#endif /* (!defined(RWASSERTE)) */

#if (!defined(RWPENTER))
#define RWPENTER(_func)        /* No-Op */
#endif /* (!defined(RWPENTER)) */

#if (!defined(RWPEXIT))
#define RWPEXIT(_func)         /* No-Op */
#endif /* (!defined(RWPEXIT)) */

/****************************************************************************
 Includes
 */

#include <rwcore.h>

#include "rpplugin.h"

/****************************************************************************
 Defines
 */

#ifdef RWDEBUG

#if (!(defined(RWDEBUGSTACKDEPTH)))
#define RWDEBUGSTACKDEPTH (RWSRCGLOBAL(debugStackDepth))
#endif /* (!(defined(RWDEBUGSTACKDEPTH))) */

/* Message macros */

#ifdef RWTRACE

/* Note RWTRACE should only be defined for internal builds. It should
 * also only be used rarely. It will cause the generation of Trace
 * messages for all functions. Not just those directly called from
 * the application
 */

#define RWAPIFUNCTION(function)                                         \
static const RwChar __dbFunctionName[] = function;                      \
const RwInt32 startstackdepth = RWDEBUGSTACKDEPTH++;                    \
RWPENTER(__dbFunctionName);                                             \
if (RWSRCGLOBAL(debugTrace))                                            \
{                                                                       \
    RwDebugSendMessage(rwDEBUGTRACE,                                    \
                       __dbFunctionName,                                \
                       _rwdbsprintf("Enter %s [Depth %d]",              \
                                    (startstackdepth)?"SPI":"API",      \
                                    (int)startstackdepth));             \
}

#define RWFUNCTION(function) RWAPIFUNCTION(function)

#define RWRETURN(result)                                                \
do                                                                      \
{                                                                       \
    RwInt32 _validateStackDepth = --RWDEBUGSTACKDEPTH;                  \
    if (_validateStackDepth != startstackdepth)                         \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGERROR,                                \
                             __dbFunctionName,                          \
                             _rwdberrcommon(E_RW_DEBUGSTACK));          \
        RWDEBUGSTACKDEPTH = startstackdepth;                            \
    }                                                                   \
    if (RWSRCGLOBAL(debugTrace))                                        \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGTRACE,                                \
                             __dbFunctionName, RWSTRING("Exit"));       \
    }                                                                   \
    RWASSERTE(_validateStackDepth == startstackdepth);                  \
    RWPEXIT(__dbFunctionName);                                          \
    return (result);                                                    \
}                                                                       \
while (0)

#define RWRETURNVOID()                                                  \
do                                                                      \
{                                                                       \
    RwInt32 _validateStackDepth = --RWDEBUGSTACKDEPTH;                  \
    if (_validateStackDepth != startstackdepth)                         \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGERROR,                                \
                             __dbFunctionName,                          \
                             _rwdberrcommon (E_RW_DEBUGSTACK));         \
        RWDEBUGSTACKDEPTH = startstackdepth;                            \
    }                                                                   \
    if (RWSRCGLOBAL(debugTrace))                                        \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGTRACE,                                \
                             __dbFunctionName, RWSTRING("Exit"));       \
    }                                                                   \
    RWASSERTE(_validateStackDepth == startstackdepth);                  \
    RWPEXIT(__dbFunctionName);                                          \
    return;                                                             \
}                                                                       \
while(0)

#else /* RWTRACE */

#define RWAPIFUNCTION(function)                                         \
static const RwChar __dbFunctionName[] = function;                      \
const RwInt32 startstackdepth = RWDEBUGSTACKDEPTH++;                    \
RWPENTER(__dbFunctionName);                                             \
if (RWSRCGLOBAL(debugTrace) && !startstackdepth)                        \
{                                                                       \
        RwDebugSendMessage(rwDEBUGTRACE,                                \
                             __dbFunctionName, RWSTRING("Enter"));      \
}

#define RWFUNCTION(function) RWAPIFUNCTION(function)

#define RWRETURN(result)                                                \
do                                                                      \
{                                                                       \
    RwInt32 _validateStackDepth = --RWDEBUGSTACKDEPTH;                  \
    if (_validateStackDepth != startstackdepth)                         \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGERROR,                                \
                             __dbFunctionName,                          \
                             _rwdberrcommon(E_RW_DEBUGSTACK));          \
        RWDEBUGSTACKDEPTH = startstackdepth;                            \
    }                                                                   \
    if (RWSRCGLOBAL(debugTrace) && (!startstackdepth))                  \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGTRACE,                                \
                             __dbFunctionName, RWSTRING("Exit"));       \
    }                                                                   \
    RWASSERTE(_validateStackDepth == startstackdepth);                  \
    RWPEXIT(__dbFunctionName);                                          \
    return (result);                                                    \
}                                                                       \
while (0)

#define RWRETURNVOID()                                                  \
do                                                                      \
{                                                                       \
    RwInt32 _validateStackDepth = --RWDEBUGSTACKDEPTH;                  \
    if (_validateStackDepth != startstackdepth)                         \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGERROR,                                \
                             __dbFunctionName,                          \
                             _rwdberrcommon (E_RW_DEBUGSTACK));         \
        RWDEBUGSTACKDEPTH = startstackdepth;                            \
    }                                                                   \
    if (RWSRCGLOBAL(debugTrace) && (!startstackdepth))                  \
    {                                                                   \
        RwDebugSendMessage(rwDEBUGTRACE,                                \
                             __dbFunctionName, RWSTRING("Exit"));       \
    }                                                                   \
    RWASSERTE(_validateStackDepth == startstackdepth);                  \
    RWPEXIT(__dbFunctionName);                                          \
    return;                                                             \
}                                                                       \
while(0)

#endif /* RWTRACE */

#define RWERROR(ecode)                                  \
do                                                      \
{                                                       \
    RwError _rwErrorCode;                               \
                                                        \
    _rwErrorCode.pluginID = rwPLUGIN_ID;                \
    _rwErrorCode.errorCode = _rwerror ecode;            \
                                                        \
    RwErrorSet(&_rwErrorCode);                          \
                                                        \
    if (_rwErrorCode.errorCode & 0x80000000)            \
    {                                                   \
        RwDebugSendMessage(rwDEBUGERROR,                \
                         __dbFunctionName,              \
                         _rwdberrcommon ecode);         \
    }                                                   \
    else                                                \
    {                                                   \
        RwDebugSendMessage(rwDEBUGERROR,                \
                         __dbFunctionName,              \
                         rwPLUGIN_ERRFUNC ecode);       \
    }                                                   \
}                                                       \
while(0);

#define RWMESSAGE(args)                         \
do                                              \
{                                               \
    RwDebugSendMessage(rwDEBUGMESSAGE,          \
                         __dbFunctionName,      \
                       _rwdbsprintf args);      \
}                                               \
while (0)

#define RWASSERT(condition)                             \
do                                                      \
{                                                       \
    if (!(condition))                                   \
    {                                                   \
        RwDebugSendMessage(rwDEBUGASSERT,               \
                             __dbFunctionName,          \
                           RWSTRING(#condition));       \
    }                                                   \
    RWASSERTE(condition);                               \
}                                                       \
while (0)

#define RWASSERTM(condition, messageArgs)               \
do                                                      \
{                                                       \
    if (!(condition))                                   \
    {                                                   \
        RwDebugSendMessage(rwDEBUGASSERT,               \
                             __dbFunctionName,          \
                           RWSTRING(#condition));       \
        RwDebugSendMessage(rwDEBUGMESSAGE,              \
                             __dbFunctionName,          \
                           _rwdbsprintf messageArgs);   \
    }                                                   \
    RWASSERTE(condition);                               \
}                                                       \
while (0)

#else /* RWDEBUG */

#define RWRETURN(value) return(value)
#define RWRETURNVOID() return
#define RWERROR(errorcode)                              \
do                                                      \
{                                                       \
    RwError _rwErrorCode;                               \
                                                        \
    _rwErrorCode.pluginID = rwPLUGIN_ID;                \
    _rwErrorCode.errorCode = _rwerror errorcode;        \
                                                        \
    RwErrorSet(&_rwErrorCode);                          \
}                                                       \
while (0)
#define RWFUNCTION(name)
#define RWAPIFUNCTION(name)
#define RWASSERT(condition)
#define RWASSERTM(condition, messageArgs)
#define RWMESSAGE(args)

#endif

#define RWVALIDATEDEBUGSTACKDEPTH() \
    RWASSERT(1 == (RWDEBUGSTACKDEPTH - startstackdepth))

/****************************************************************************
 Functions
 */

#ifdef    __cplusplus
extern              "C"
{
#endif                          /* __cplusplus */

RwChar             *rwPLUGIN_ERRFUNC(RwInt32 code, ...);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* RWDEBUG_H */
