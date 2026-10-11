#include "nitro/types.h"

typedef struct SceneEntry {
    int overlayId;
    void *classDesc;
} SceneEntry;

extern u8 data_ov000_02063870[];
extern void *gFieldSessionClassDescriptor[5];
extern u8 data_ov002_0206c2c4[];
extern u8 data_ov004_02064530[];

/* AdvancePendingScene loads the overlay before creating its scene object. */
SceneEntry gSceneTable[12] = {
    {-1, NULL},
    { 0, data_ov000_02063870},
    { 1, gFieldSessionClassDescriptor},
    { 2, data_ov002_0206c2c4},
    { 4, data_ov004_02064530},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL}
};
