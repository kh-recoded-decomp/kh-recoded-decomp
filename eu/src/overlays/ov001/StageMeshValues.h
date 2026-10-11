#ifndef EU_STAGE_MESH_VALUES_H
#define EU_STAGE_MESH_VALUES_H

#include "nitro/types.h"

typedef struct NamedMeshValue {
    const char *name;
    u32 value;
} NamedMeshValue;

extern const NamedMeshValue gStageMeshValues[10];

#endif
