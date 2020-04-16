#pragma once

#include <rphanim.h>

RwBool RpSkinPluginAttach(void);

RpAtomic *RpSkinAtomicSetHAnimHierarchy( RpAtomic *atomic, RpHAnimHierarchy *hierarchy );
RpHAnimHierarchy *RpSkinAtomicGetHAnimHierarchy( const RpAtomic *atomic );
