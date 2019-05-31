#ifndef PLATFORM_H
#define PLATFORM_H

#include "rwcore.h"
#include "skeleton.h"

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern RwUInt32 psTimer(void);


extern RwBool psInitialise(void);
extern void   psTerminate(void);

extern void psCameraShowRaster(RwCamera *camera);
extern RwBool psCameraBeginUpdate(RwCamera *camera);

extern void psMouseSetPos(RwV2d *pos);

extern RwBool psSelectDevice(RwBool useDefault);

/* install the platform specific file system */
extern RwBool psInstallFileSystem(void);


/* Handle native texture support */
extern RwBool psNativeTextureSupport(void);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */

#endif /* PLATFORM_H */
