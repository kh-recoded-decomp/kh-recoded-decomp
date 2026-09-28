#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s32 id;
    s32 value;
    u8 pad_10[0x2C];
} FieldEntry;

typedef struct {
    u8 pad_000[0xAC];
    FieldEntry *entries;
    u8 pad_0B0[0x1C];
    s32 entryCount;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

s32 func_ov001_020789b8(s32 id)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    FieldEntry *entry;
    s32 index;

    for (index = 0; index < menu->entryCount; index++) {
        entry = &menu->entries[index];
        if (entry->id == id) {
            break;
        }
    }
    if (index == menu->entryCount) {
        return -1;
    }
    return entry->value;
}
