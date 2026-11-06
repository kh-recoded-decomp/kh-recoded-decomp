#include "nitro/types.h"

typedef struct SceneEntry {
    int overlayId;
    void *classDesc;
} SceneEntry;

extern u8 gTitleScreenTaskClass[];
extern void *gFieldSessionClassDescriptor[5];
extern u8 gProfilePanelTaskClass[];
extern u8 gScrollTextTaskClass[];

/* AdvancePendingScene loads the overlay before creating its scene object. */
SceneEntry gSceneTable[12] = {
    {-1, NULL},
    { 0, gTitleScreenTaskClass},
    { 1, gFieldSessionClassDescriptor},
    { 2, gProfilePanelTaskClass},
    { 4, gScrollTextTaskClass},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL},
    {-1, NULL}
};
