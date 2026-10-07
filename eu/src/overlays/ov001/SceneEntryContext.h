#ifndef KH_RECODED_EU_OV001_SCENE_ENTRY_CONTEXT_H
#define KH_RECODED_EU_OV001_SCENE_ENTRY_CONTEXT_H

#include "nitro/fx_types.h"
#include "nitro/types.h"

typedef struct SceneEntry {
    u8 pad_00;
    u8 patrolPointCount;
    u16 slotId;
    u8 pad_04[4];
    fx32 cameraHeightLimit;
    fx32 groundHeight;
    u8 pad_10[8];
    u8 primaryDisplayId;
    u8 secondaryDisplayId;
    u8 pad_1a[2];
    u32 resourceId;
} SceneEntry;

typedef struct SceneEntryTable {
    u8 pad_00[4];
    void *resourceHandle;
    SceneEntry *entries[1];
} SceneEntryTable;

typedef struct SceneEntryContext {
    SceneEntryTable *table;
    u8 pad_04[9];
    s8 currentEntry;
} SceneEntryContext;

extern SceneEntryContext *data_ov001_020a048c;
#define gSceneEntryContext data_ov001_020a048c

#endif
