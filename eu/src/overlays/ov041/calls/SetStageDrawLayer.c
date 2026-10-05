#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c4];
    s16 layer;
} LayeredObject;

typedef struct {
    u8 pad_000[0x320];
    s16 layer;
    u8 pad_322[0x12];
    LayeredObject *child;
    u8 pad_338[0x17c];
} StageEntry;

typedef struct {
    u8 pad_000[0x14];
    StageEntry *entries;
    u8 entryCount;
    u8 pad_019[0x333];
    LayeredObject *extras[2];
    u8 pad_354[0x1fd4];
    int layer;
} StageWork;

extern u8 *data_ov035_020bc4e0;

void SetStageDrawLayer(int layer) {
    int i;
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);

    work->layer = layer;
    for (i = 0; i < work->entryCount; i++) {
        StageEntry *entry = &work->entries[i];
        if (entry != NULL) {
            entry->layer = layer;
            if (entry->child != NULL) {
                entry->child->layer = layer;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (work->extras[i] != NULL) {
            work->extras[i]->layer = layer;
        }
    }
}
