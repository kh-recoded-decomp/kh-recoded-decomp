#include "nitro/types.h"

typedef struct {
    u32 current;
    u32 limit;
    s32 id;
    s32 value;
    s32 state;
    u8 pad_14[0x28];
} FieldEntry;

typedef struct {
    u8 pad_000[0xAC];
    FieldEntry *entries;
    u8 pad_0B0[0x20];
    s32 activeCount;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

void func_ov001_020786d0(s32 id)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    FieldEntry *entry;
    s32 index;

    for (index = 0; index < menu->activeCount; index++) {
        entry = &menu->entries[index];
        if (entry->id == id) {
            if (entry->state == 3) {
                return;
            }
            entry->current = entry->limit;
            return;
        }
    }
}
