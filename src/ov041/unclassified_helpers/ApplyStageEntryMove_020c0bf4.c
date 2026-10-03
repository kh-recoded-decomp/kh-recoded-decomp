#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_006[0x7a];
    u16 tilt;
} StageObject;

typedef struct {
    u8 pad_000[8];
    u32 flags;
    u8 pad_00c[0x160];
    StageObject object;
    u8 pad_1f0[0x24];
    VecFx32 position;
    u8 pad_220[0x294];
} StageEntry;

typedef struct {
    u8 pad_00[8];
    u32 flags;
    u8 pad_0c[8];
    StageEntry *entries;
} StageWork;

extern u8 *data_ov035_020bc4e0;

void ApplyStageEntryMove_020c0bf4(int index, int move) {
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    StageEntry *entry = &work->entries[index];

    switch (move) {
    case 2:
        if (entry->flags & 1) {
            if ((entry->object.flags & 0x20) == 0) {
                entry->object.tilt = 0xc004;
                entry->object.drawFlags |= 0x20;
            }
            entry->flags |= 4;
        } else {
            entry->position.x += 0x5000;
        }
        break;
    case 3:
        if ((entry->flags & 1) == 0) {
            if ((entry->object.flags & 0x20) == 0) {
                entry->object.tilt = 0x3ffc;
                entry->object.drawFlags |= 0x20;
            }
            entry->flags |= 4;
        }
        break;
    case 1:
        if ((entry->flags & 1) == 0) {
            if (work->flags & 0x40) {
                entry->position.x += 0x9000;
            } else {
                entry->position.x += 0x5000;
            }
        }
        break;
    }
}
