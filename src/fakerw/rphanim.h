#pragma once

//struct RpHAnimHierarchy;
typedef rw::HAnimHierarchy RpHAnimHierarchy;
//struct RpHAnimAnimation;
typedef rw::Animation RpHAnimAnimation;

RwBool RpHAnimPluginAttach(void);

RwBool RpHAnimFrameSetHierarchy(RwFrame *frame, RpHAnimHierarchy *hierarchy);
RpHAnimHierarchy *RpHAnimFrameGetHierarchy(RwFrame *frame);

RwBool RpHAnimHierarchySetCurrentAnim(RpHAnimHierarchy *hierarchy, RpHAnimAnimation *anim);
RwBool RpHAnimHierarchySetCurrentAnimTime(RpHAnimHierarchy *hierarchy, RwReal time);
RwBool RpHAnimHierarchySubAnimTime(RpHAnimHierarchy *hierarchy, RwReal time);
RwBool RpHAnimHierarchyAddAnimTime(RpHAnimHierarchy *hierarchy, RwReal time);

RwBool RpHAnimHierarchyUpdateMatrices(RpHAnimHierarchy *hierarchy);

RpHAnimAnimation  *RpHAnimAnimationStreamRead(RwStream *stream);
