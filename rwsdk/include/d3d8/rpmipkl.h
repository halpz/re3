/**
 * PS2 Mipmap K&L plugin for Renderware.
 */

#ifndef RPMIPMAPKLPLUGIN_H
#define RPMIPMAPKLPLUGIN_H

/**
 * \defgroup rpmipkl RpMipmapKL
 * \ingroup mipmapping
 *
 * PlayStation 2 / MipMap KL Value Plugin for RenderWare Graphics.
 */

#include <rwcore.h>

#ifdef __cplusplus
extern              "C"
{
#endif

#if (defined(SKY2_DRVMODEL_H)) || (defined(NULLSKY_DRVMODEL_H))

#define RpMipmapKLTextureSetDefaultK RpSkyTextureSetDefaultMipmapK

#define RpMipmapKLTextureSetDefaultL RpSkyTextureSetDefaultMipmapL

#define RpMipmapKLTextureGetDefaultK RpSkyTextureGetDefaultMipmapK

#define RpMipmapKLTextureGetDefaultL RpSkyTextureGetDefaultMipmapL

#define RpMipmapKLTextureSetK RpSkyTextureSetMipmapK

#define RpMipmapKLTextureSetL RpSkyTextureSetMipmapL

#define RpMipmapKLTextureGetK RpSkyTextureGetMipmapK

#define RpMipmapKLTextureGetL RpSkyTextureGetMipmapL

#define RpMipmapKLPluginAttach() (TRUE)

#else /*  (defined(SKY2_DRVMODEL_H)) || (defined(NULLSKY_DRVMODEL_H)) */

extern RwReal      RpMipmapKLTextureSetDefaultK(RwReal val);
extern RwUInt32    RpMipmapKLTextureSetDefaultL(RwUInt32 val);
extern RwReal      RpMipmapKLTextureGetDefaultK(void);
extern RwUInt32    RpMipmapKLTextureGetDefaultL(void);

extern RwTexture    *RpMipmapKLTextureSetK(RwTexture *tex, RwReal val);
extern RwTexture    *RpMipmapKLTextureSetL(RwTexture *tex, RwUInt32 val);
extern RwReal       RpMipmapKLTextureGetK(RwTexture *tex);
extern RwUInt32     RpMipmapKLTextureGetL(RwTexture *tex);

extern RwBool       RpMipmapKLPluginAttach(void);

#endif /*  (defined(SKY2_DRVMODEL_H)) || (defined(NULLSKY_DRVMODEL_H)) */

#ifdef __cplusplus
}
#endif

#endif                          /* RPMIPMAPKLPLUGIN_H */
