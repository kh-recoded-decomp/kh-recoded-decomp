#ifndef OV067_RESOURCE_PATHS_H
#define OV067_RESOURCE_PATHS_H

#include "nitro/types.h"

typedef struct Ov067ResourcePaths {
    u8 effectDirectory[9];
    char archiveName[7];
    char characterPathFormat[16];
    char commonArchive[32];
} Ov067ResourcePaths;

extern Ov067ResourcePaths data_ov067_020d8560;

#endif
