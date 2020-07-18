/**
 * Anisotropic Texture Sampling Plugin for RenderWare.
 */

#ifndef RPANISOTPLUGIN_H
#define RPANISOTPLUGIN_H

/**
 * \defgroup rpanisot RpAnisot
 * \ingroup mipmapping
 *
 * Anisotropic Texture Sampling Plugin for RenderWare Graphics.
 */

/**
 * \ingroup rpanisot
 * \page rpanisotoverview RpAnisot Plugin Overview
 *
 * \par Requirements
 * \li \b Headers: rwcore.h, rpworld.h, rpanisot.h
 * \li \b Libraries: rwcore, rpworld, rpanisot
 * \li \b Plugin \b attachments: \ref RpWorldPluginAttach, \ref RpAnisotPluginAttach
 *
 * \subsection anisotoverview Overview
 * The RpAnisot plugin is used to extend an \ref RwTexture with a maximum
 * anisotropy value that will be used when a particular texture is drawn.
 * When textured polygons are viewed nearly edge on, for example when looking
 * dowm a road or a football pitch, distant pixels are not sampled very well
 * by trilinear mipmapping and the texture looks smeary.
 * Anisotropic sampling takes additional samples, resulting in sharper looking
 * textures.  Higher numbers of samples will produce better quality results but
 * run slower, so should be used in moderation.
 *
 */

#include <rwcore.h>

#ifdef __cplusplus
extern              "C"
{
#endif

extern RwInt8      RpAnisotGetMaxSupportedMaxAnisotropy(void);

extern RwTexture    *RpAnisotTextureSetMaxAnisotropy(RwTexture *tex, RwInt8 val);
extern RwInt8       RpAnisotTextureGetMaxAnisotropy(RwTexture *tex);

extern RwBool       RpAnisotPluginAttach(void);

#ifdef __cplusplus
}
#endif

#endif                          /* RPANISOTPLUGIN_H */
