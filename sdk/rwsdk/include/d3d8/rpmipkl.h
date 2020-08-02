/**
 * PS2 Mipmap K&L plugin for Renderware.
 */

#ifndef RPMIPMAPKLPLUGIN_H
#define RPMIPMAPKLPLUGIN_H

/**
 * \defgroup rpmipkl RpMipmapKL
 * \ingroup rpplugin
 *
 * PS2/MipMap KL Value Plugin for RenderWare Graphics.
 */

#include <rwcore.h>

#ifdef __cplusplus
extern              "C"
{
#endif

extern RwReal      RpMipmapKLTextureSetDefaultK(RwReal val);
extern RwUInt32    RpMipmapKLTextureSetDefaultL(RwUInt32 val);
extern RwReal      RpMipmapKLTextureGetDefaultK(void);
extern RwUInt32    RpMipmapKLTextureGetDefaultL(void);

extern RwTexture    *RpMipmapKLTextureSetK(RwTexture *tex, RwReal val);
extern RwTexture    *RpMipmapKLTextureSetL(RwTexture *tex, RwUInt32 val);
extern RwReal       RpMipmapKLTextureGetK(RwTexture *tex);
extern RwUInt32     RpMipmapKLTextureGetL(RwTexture *tex);

extern RwBool       RpMipmapKLPluginAttach(void);

#ifdef __cplusplus
}
#endif

#endif                          /* RPMIPMAPKLPLUGIN_H */
